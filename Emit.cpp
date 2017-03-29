

#include "Emit.h"
#include "AST/NopExprAST.h"


Emit::Emit(std::vector<ExprAST *> expressions) : _expressions(expressions) {

}


void Emit::start(llvm::IRBuilder<> &builder, llvm::Module &module) {

    for(int i=0;i<_expressions.size();i++){
        ExprAST *E = _expressions[i];
        if(E!= nullptr)
            _expressions[i]->emit(builder,module);
    }
}



llvm::Value *BinaryExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module)
{
    llvm::Value *L, *R;
    if(_op=='='){
        IdentifierExprAST *identifier = dynamic_cast<IdentifierExprAST *>(_lhs);
        L = identifier->getValue();
        R = _rhs->emit(builder,module);
        if(L==0 || R==0)
            return 0;

        return builder.CreateStore(R,L);
    }

    L = _lhs->emit(builder,module);
    R = _rhs->emit(builder,module);


    if(L== nullptr || R== nullptr)
        return nullptr;

    switch (_op){
        case '+':
            return builder.CreateAdd(L,R,"addtmp");
        case '-':
            return builder.CreateSub(L,R,"subtmp");
        case '*':
            return builder.CreateMul(L,R,"multmp");
        case '/':
            return builder.CreateSDiv(L,R,"divtmp");
        case '%':
            return builder.CreateSRem(L,R, "remptmp");
        case '|':
            return builder.CreateOr(L,R,"bitortmp");
        case '&':
            return builder.CreateAnd(L,R,"bitandtmp");
        case '<':
            L = builder.CreateFCmpULT(L,R,"cmptmp");
            return builder.CreateUIToFP(L,llvm::Type::getDoubleTy(module.getContext()),"booltmp");
        case '>':
            L = builder.CreateFCmpULT(R,L,"cmptmp");
            return builder.CreateUIToFP(L,llvm::Type::getDoubleTy(module.getContext()),"booltmp");
        default:
            return nullptr;
    }
}


llvm::Value *CallExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module) {

    llvm::Function *proto = module.getFunction(_callee);

    if(!proto)
        return nullptr;

    llvm::CallInst *call = builder.CreateCall(proto,"calltmp");
    call->setTailCall(false);

    return call;
}



llvm::Value *FunctionAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module) {

    llvm::Function *function = _prototype->emit(builder,module);

    llvm::BasicBlock *block = llvm::BasicBlock::Create(module.getContext(),"entrypoint",function);
    builder.SetInsertPoint(block);

    _body->emit(builder,module);

    if(_return!= nullptr){
        _return->emit(builder,module);
    }
    return function;

}



llvm::Value *IdentifierExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module) {


    return builder.CreateLoad(_var->getValue(),_var->getName());

}



llvm::Value *NumberExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module) {

    return llvm::ConstantInt::get(module.getContext(),llvm::APInt(32,_value));
}



llvm::Function *PrototypeAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module) {

    llvm::Type *type = getLLVMType(builder,_type);
    llvm::FunctionType *functionType = llvm::FunctionType::get(type,false);
    llvm::Function *F = llvm::Function::Create(functionType,llvm::Function::ExternalLinkage,_name,&module);

    return F;
}

llvm::Value *VariableExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module) {

    llvm::Type *type = getLLVMType(builder,_type);
    return _value = builder.CreateAlloca(type,0,_name.c_str());
}

llvm::Value *PrintExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module)
{
    llvm::Function *printf_prototype = module.getFunction("printf");

    llvm::Constant *format_const = llvm::ConstantDataArray::getString(builder.getContext(),"%d\n");
    llvm::GlobalVariable *var = new llvm::GlobalVariable(module, llvm::ArrayType::get(llvm::IntegerType::get(builder.getContext(), 8), 4),
                                                         true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");
    llvm::Constant *zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(builder.getContext()));

    std::vector<llvm::Constant*> indices = {zero,zero};

    llvm::Constant *var_ref = llvm::ConstantExpr::getGetElementPtr(var, indices);

    llvm::CallInst *call = builder.CreateCall2(printf_prototype, var_ref, _expr->emit(builder, module));
    call->setTailCall(false);

    return call;
}



llvm::Value *ReturnExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module)
{
    return builder.CreateRet(_identifier->emit(builder,module));

}

llvm::Value *NopExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module)
{
    llvm::Constant *nop = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(builder.getContext()));
    return builder.CreateRet(nop);
}

llvm::Value *IfExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module)
{
    llvm::Value *ElseV = NULL;
    llvm::Value *CondV = _cond->emit(builder, module);
    if (CondV == 0) {
        return 0;
    }

    CondV = builder.CreateFCmpONE(CondV, llvm::ConstantFP::get(builder.getContext(), llvm::APFloat(0.0)), "ifcond");


    llvm::Function *parent = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(builder.getContext(),"then",parent);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(builder.getContext(),"else");
    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(builder.getContext(),"ifcont");

    builder.CreateCondBr(CondV,ThenBB,ElseBB);

    builder.SetInsertPoint(ThenBB);

    llvm::Value *ThenV = _then->emit(builder,module);

    builder.CreateBr(MergeBB);

    ThenBB = builder.GetInsertBlock();

    parent->getBasicBlockList().push_back(ElseBB);

    builder.SetInsertPoint(ElseBB);

    if(_else){
        ElseV = _else->emit(builder,module);
    }

    builder.CreateBr(MergeBB);

    ElseBB = builder.GetInsertBlock();

    parent->getBasicBlockList().push_back(MergeBB);

    builder.SetInsertPoint(MergeBB);
    llvm::PHINode *PN = builder.CreatePHI(builder.getDoubleTy(),2,"iftmp");

    PN->addIncoming(ThenV,ThenBB);

    if(_else){
        PN->addIncoming(ElseV, ElseBB);
    }
    else{
        PN->addIncoming(ThenV,ElseBB);
    }
    return PN;
}



llvm::Value *WhileExprAST::emit(llvm::IRBuilder<> &builder, llvm::Module &module)
{
    llvm::Value *pCondV = _cond->emit(builder,module);

    llvm::Value *CondV = builder.CreateFCmpONE(pCondV, llvm::ConstantFP::get(builder.getContext(),llvm::APFloat(0.0)),"whilecond");

    llvm::Function *parent = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(builder.getContext(),"loop", parent);
    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(builder.getContext(),"whilecont");

    builder.CreateCondBr(CondV,LoopBB,MergeBB);

    builder.SetInsertPoint(LoopBB);
    llvm::Value *loopV = _block->emit(builder,module);

    CondV = builder.CreateFCmpONE(_cond->emit(builder,module),llvm::ConstantFP::get(builder.getContext(),
                                                                                    llvm::APFloat(0.0)),"whilecond");
    builder.CreateCondBr(CondV,LoopBB,MergeBB);
    LoopBB = builder.GetInsertBlock();

    parent->getBasicBlockList().push_back(MergeBB);
    builder.SetInsertPoint(MergeBB);
    llvm::PHINode *PN = builder.CreatePHI(builder.getDoubleTy(),2,"whiletmp");

    PN->addIncoming(loopV, LoopBB);
    PN->addIncoming(loopV, LoopBB);

    return PN;

}

