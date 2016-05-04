//
// Created by milendimitrov on 09.03.16.
//

#ifndef MTPROJECT_WHILEEXPRAST_H
#define MTPROJECT_WHILEEXPRAST_H


#include "ExprAST.h"


class WhileExprAST : public ExprAST {

    ExprAST *_cond;
    ExprAST *_block;
public:
    WhileExprAST(ExprAST *cond, ExprAST *block);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
};


#endif //MTPROJECT_WHILEEXPRAST_H
