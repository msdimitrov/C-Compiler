
#ifndef MTPROJECT_BINARYEXPRAST_H
#define MTPROJECT_BINARYEXPRAST_H


#include "ExprAST.h"
#include "IdentifierExprAST.h"

class BinaryExprAST : public ExprAST {

    char _op;
    ExprAST *_lhs,*_rhs;
public:
    BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder,llvm::Module &module);
};


#endif //MTPROJECT_BINARYEXPRAST_H
