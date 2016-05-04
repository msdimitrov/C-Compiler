

#ifndef MTPROJECT_NUMBEREXPRAST_H
#define MTPROJECT_NUMBEREXPRAST_H

#include "ExprAST.h"

class NumberExprAST : public ExprAST {

    long _value;

public:
    NumberExprAST(long val);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
};


#endif //MTPROJECT_NUMBEREXPRAST_H
