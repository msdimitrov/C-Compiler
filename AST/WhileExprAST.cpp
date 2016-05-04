//
// Created by milendimitrov on 09.03.16.
//

#include "WhileExprAST.h"

WhileExprAST::WhileExprAST(ExprAST *cond, ExprAST *block) : _cond(cond), _block(block) { }

