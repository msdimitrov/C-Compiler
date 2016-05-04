
#ifndef MTPROJECT_EMMITER_H
#define MTPROJECT_EMMITER_H

#include "AST/BinaryExprAST.h"
#include "AST/CallExprAST.h"
#include "AST/FunctionAST.h"
#include "AST/IdentifierExprAST.h"
#include "AST/NumberExprAST.h"
#include "AST/PrototypeAST.h"
#include "AST/VariableExprAST.h"
#include "AST/PrintExprAST.h"
#include "AST/ReturnExprAST.h"
#include "AST/IfExprAST.h"
#include "AST/WhileExprAST.h"

class Emit {

    std::vector<ExprAST *> _expressions;

public:
    Emit(std::vector<ExprAST *> expressions);
    void start(llvm::IRBuilder<> &builder, llvm::Module &module);

};


#endif //MTPROJECT_EMMITER_H
