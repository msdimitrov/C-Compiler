

#ifndef MTPROJECT_IDENTIFIEREXPRAST_H
#define MTPROJECT_IDENTIFIEREXPRAST_H

#include "VariableExprAST.h"

class IdentifierExprAST : public ExprAST {

    VariableExprAST *_var;
public:
    IdentifierExprAST(VariableExprAST *var);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
    llvm::Value *getValue();
};


#endif //MTPROJECT_IDENTIFIEREXPRAST_H
