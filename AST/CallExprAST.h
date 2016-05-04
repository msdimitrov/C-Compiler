
#ifndef MTPROJECT_CALLEXPRAST_H
#define MTPROJECT_CALLEXPRAST_H


#include "ExprAST.h"
#include <string>
#include <vector>

class CallExprAST : public ExprAST {

    std::string _callee;

public:
    CallExprAST(const std::string &callee);
    virtual llvm::Value *emit(llvm::IRBuilder<> &buidler, llvm::Module &module);
};


#endif //MTPROJECT_CALLEXPRAST_H
