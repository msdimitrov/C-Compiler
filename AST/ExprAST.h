

#ifndef MTPROJECT_EXPRAST_H
#define MTPROJECT_EXPRAST_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/StringSwitch.h"

class ExprAST {

public:
    virtual ~ExprAST();
    llvm::Type *getLLVMType(llvm::IRBuilder<> &builder, std::string type);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module)=0;
};


#endif //MTPROJECT_EXPRAST_H
