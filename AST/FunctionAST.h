
#ifndef MTPROJECT_FUNCTIONAST_H
#define MTPROJECT_FUNCTIONAST_H


#include "PrototypeAST.h"
#include "ExprAST.h"
#include "ReturnExprAST.h"


class FunctionAST : public ExprAST {

    PrototypeAST *_prototype;
    ExprAST *_body;
    ReturnExprAST *_return;



public:
    FunctionAST(PrototypeAST *prototype, ExprAST *Body);
//    FunctionAST(PrototypeAST *prototype, BlockExprAST *Body, ExprAST *ReturnValue);
    virtual llvm::Value* emit(llvm::IRBuilder<> &builder, llvm::Module &module);

};


#endif //MTPROJECT_FUNCTIONAST_H
