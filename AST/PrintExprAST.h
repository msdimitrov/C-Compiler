//
// Created by milendimitrov on 04.03.16.
//

#ifndef MTPROJECT_PRINTEXPRAST_H
#define MTPROJECT_PRINTEXPRAST_H


#include "ExprAST.h"
#include "IdentifierExprAST.h"

class PrintExprAST : public ExprAST {

    ExprAST *_expr;
public:

    PrintExprAST(ExprAST *expr);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
};


#endif //MTPROJECT_PRINTEXPRAST_H
