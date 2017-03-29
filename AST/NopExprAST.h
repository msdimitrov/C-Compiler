//
// Created by milendimitrov on 3/29/17.
//

#ifndef MTPROJECT_NOPEXPRAST_H
#define MTPROJECT_NOPEXPRAST_H

#include "ExprAST.h"

class NopExprAST : public ExprAST {

public:
    NopExprAST();
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
};


#endif //MTPROJECT_NOPEXPRAST_H
