//
// Created by milendimitrov on 05.03.16.
//

#ifndef MTPROJECT_RETURNEXPRAST_H
#define MTPROJECT_RETURNEXPRAST_H


#include "ExprAST.h"

class ReturnExprAST : public ExprAST {

ExprAST *_identifier;

public:
    ReturnExprAST(ExprAST *identifier);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
};


#endif //MTPROJECT_RETURNEXPRAST_H
