
#ifndef MTPROJECT_PARSER_H
#define MTPROJECT_PARSER_H

#include <map>
#include "Tokens.h"
#include "Scanner.h"
#include "AST/ExprAST.h"
#include "AST/PrototypeAST.h"
#include "AST/FunctionAST.h"
#include "AST/VariableExprAST.h"
#include "AST/NumberExprAST.h"
#include "AST/CallExprAST.h"
#include "AST/BinaryExprAST.h"
#include "AST/PrintExprAST.h"
#include "AST/ReturnExprAST.h"
#include "AST/WhileExprAST.h"
#include "AST/IfExprAST.h"


class Parser {
    Scanner *_scanner;
    Token currentToken;
    std::vector<ExprAST *> _expressions;
    std::map<char, int> BinopPrecedence;
    std::map<std::string, VariableExprAST*> _variables;
    void addVariable(const std::string &name, VariableExprAST *value);
    Token getNextToken();
    ExprAST *Error(const char *str, int line);
    PrototypeAST *ErrorP(const char *str, int line);
    IfExprAST *ErrorI(const char *str, int line);
    WhileExprAST *ErrorW(const char *str, int line);
    ExprAST *handleType(std::string type);
    ExprAST *handleNumberExpression();
    ExprAST *handleIdentifierExpression();
    ExprAST *handleParenthesesExpression();
    ExprAST *handlePrimary();
    ExprAST *handleExpression();
    ExprAST *handleBinaryOpExpression(int ExprPrec, ExprAST *LHS);
    ExprAST *handlePrintf();
    ExprAST *handleReturn();
    WhileExprAST *handleWhile();
    IfExprAST *handleIf();
    VariableExprAST *handleVariable(std::string identifier, std::string type);
    FunctionAST *handleFunction(std::string identifier, std::string type);
    PrototypeAST *handlePrototype(const std::string &identifier, const std::string &type);


public:
    Parser(Scanner *scanner);
    void parse();
    bool parsed = true;
    std::vector<ExprAST *> getExpressions();

};


#endif //MTPROJECT_PARSER_H
