

#include "IdentifierExprAST.h"

IdentifierExprAST::IdentifierExprAST(VariableExprAST *var) : _var(var) { }


llvm::Value *IdentifierExprAST::getValue() {
    return _var->getValue();
}
