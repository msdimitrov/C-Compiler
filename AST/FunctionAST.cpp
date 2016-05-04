
#include "FunctionAST.h"

FunctionAST::FunctionAST(PrototypeAST *prototype, ExprAST *Body) : _prototype(prototype), _body(Body) { }

//FunctionAST::FunctionAST(PrototypeAST *prototype, BlockExprAST * body, ExprAST *ReturnValue) : _prototype(prototype), _body(body),
//                                                                                               _returnValue(ReturnValue) { }



