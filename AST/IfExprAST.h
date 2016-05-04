//
// Created by milendimitrov on 09.03.16.
//

#ifndef MTPROJECT_IFEXPRAST_H
#define MTPROJECT_IFEXPRAST_H


#include "ExprAST.h"

class IfExprAST : public ExprAST {

    ExprAST *_cond,*_then, *_else;



public:
    IfExprAST(ExprAST *cond, ExprAST *ifblock, ExprAST *elseblock);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
};


#endif //MTPROJECT_IFEXPRAST_H
