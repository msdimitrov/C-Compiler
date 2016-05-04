
#include "BinaryExprAST.h"

BinaryExprAST::BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs) : _op(op), _lhs(lhs), _rhs(rhs) { }

