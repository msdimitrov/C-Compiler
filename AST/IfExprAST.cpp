//
// Created by milendimitrov on 09.03.16.
//

#include "IfExprAST.h"

IfExprAST::IfExprAST(ExprAST *cond, ExprAST *ifblock, ExprAST *elseblock) : _cond(cond), _then(ifblock), _else(elseblock) { }

