
#ifndef MTPROJECT_VARIABLEEXPRAST_H
#define MTPROJECT_VARIABLEEXPRAST_H


#include "ExprAST.h"
#include <string>

class VariableExprAST : public ExprAST {
protected:
    std::string _name;
    std::string _type;
    llvm::Value *_value;
public:
    VariableExprAST(const std::string &name, const std::string &type);
    virtual llvm::Value *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
    llvm::Value *getValue();
    std::string getName();
    std::string getType();
};


#endif //MTPROJECT_VARIABLEEXPRAST_H
