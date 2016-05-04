#include <iostream>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/PassManager.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/ExecutionEngine/JIT.h"
#include "Scanner.h"
#include "Parser.h"
#include "Emit.h"

using namespace std;
using namespace llvm;

static Module *module;
static IRBuilder<> builder(getGlobalContext());

static llvm::Function* printf_prototype(llvm::LLVMContext& context, llvm::Module *module)
{
    std::vector<llvm::Type*> printf_arg_types;
    printf_arg_types.push_back(llvm::Type::getInt8PtrTy(context));
    llvm::FunctionType* printf_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), printf_arg_types, true);
    llvm::Function *func = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage, llvm::Twine("printf"), module);
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}


int main(int argc, char *argv[]) {

    llvm::InitializeNativeTarget();
    LLVMContext &Context = getGlobalContext();
    module = new Module(argv[1],Context);


    llvm::Function *printf_func = printf_prototype(Context, module);


    if(argc < 2){
        printf("./MTProject <source file>");
        return EXIT_FAILURE;
    }

//    Scanner scanner("/home/milendimitrov/ClionProjects/MTProject/TestCases/While-If-SimpleNesting.sc");
    Scanner scanner(argv[1]);
    Parser parser(&scanner);

    parser.parse();

    Emit emit(parser.getExpressions());


    if(parser.parsed) {
        emit.start(builder,*module);
        module->dump();
    }

    llvm::ExecutionEngine *engine = llvm::ExecutionEngine::create(module);

    if(engine && parser.parsed) {

        llvm::Function* mainFunction = module->getFunction("main");
        if(!mainFunction)
        {
            printf("No main function");
        }
        else
        {
            std::vector<llvm::GenericValue> args;

            llvm::GenericValue val;
            val.IntVal = llvm::APInt(32, 313);
            args.push_back(val);

            printf("///////////////////////////////\"%s\"///////////////////////////////\n", argv[1]);

            engine->runFunction(mainFunction, args);

            printf("\nexited with code \n");
        }
    }

    delete module;

}
