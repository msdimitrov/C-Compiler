
#include "ExprAST.h"

ExprAST::~ExprAST() { }

llvm::Type *ExprAST::getLLVMType(llvm::IRBuilder<> &builder, std::string type) {

    return llvm::StringSwitch<llvm::Type *>(llvm::StringRef(type))
            .Case("int",builder.getInt32Ty())
            .Case("char",builder.getInt8Ty())
            .Case("bool",builder.getInt1Ty());

//    return builder.getInt32Ty();
}

