

#include "VariableExprAST.h"

VariableExprAST::VariableExprAST(const std::string &name, const std::string &type) : _name(name), _type(type) { }

llvm::Value *VariableExprAST::getValue() {
 return _value;
}

std::string VariableExprAST::getName() {
 return _name;
}

std::string VariableExprAST::getType() {
 return _type;
}

