

#ifndef MTPROJECT_PROTOTYPEAST_H
#define MTPROJECT_PROTOTYPEAST_H

#include <string>
#include <vector>
#include <llvm/IR/IRBuilder.h>
#include "ExprAST.h"


class PrototypeAST : public ExprAST {
    std::string _name;
    std::string _type;
public:
    PrototypeAST(const std::string &name, const std::string &type);
    virtual llvm::Function *emit(llvm::IRBuilder<> &builder, llvm::Module &module);
};


#endif //MTPROJECT_PROTOTYPEAST_H
