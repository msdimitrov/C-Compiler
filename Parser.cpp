

#include <vector>
#include "Parser.h"


Parser::Parser(Scanner *scanner)
{
    _scanner = scanner;
    BinopPrecedence['='] = 0;
    BinopPrecedence['<'] = 10;
    BinopPrecedence['>'] = 10;
    BinopPrecedence['|'] = 10;
    BinopPrecedence['&'] = 10;
    BinopPrecedence['!'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 30;
    BinopPrecedence['/'] = 30;
    BinopPrecedence['%'] = 40;

}

Token Parser::getNextToken() {
    return currentToken = _scanner->Next();
}


ExprAST *Parser::handleNumberExpression() {

    NumberExprAST *result = nullptr;
    if(currentToken.type == TOK_NUMBER){
        result = new NumberExprAST(strtol(currentToken.value.c_str(),0,10));
    }
    getNextToken();

    return result;
}


ExprAST *Parser::handleParenthesesExpression() {

    ExprAST *expr = nullptr;
    getNextToken();
    expr = handleExpression();
    if(currentToken.type!=TOK_CPARENTHESES){
        return Error("missing )", currentToken.line);
    }
    getNextToken();


    return expr;
}


ExprAST *Parser::handleIdentifierExpression() {

    std::string identifier = currentToken.value;
    getNextToken();
    if(currentToken.type != TOK_OPARENTHESES)
    {
        auto var = _variables[identifier];
        return new IdentifierExprAST(var);

    }

    getNextToken();

    std::vector<ExprAST *> Args;
    if(currentToken.type!=TOK_CPARENTHESES){
        while(1){
            if(auto Arg = handleExpression())
                Args.push_back(Arg);
            else
                return nullptr;

            if(currentToken.type==TOK_CPARENTHESES)
                break;

            getNextToken();

        }
    }



    return new CallExprAST(identifier);

}


ExprAST *Parser::handlePrimary() {
    switch (currentToken.type){
        case TOK_IDENT:
            return handleIdentifierExpression();
        case TOK_NUMBER:
            return handleNumberExpression();
        case TOK_OPARENTHESES:
            return handleParenthesesExpression();
        case TOK_TYPE:
            return handleType(currentToken.value);
        case TOK_RETURN:
            return handleReturn();
        case TOK_PRINTF:
            return handlePrintf();
        case TOK_WHILE:
            return handleWhile();
        case TOK_IF:
            return handleIf();
        default:
            return nullptr;
    }
}

ExprAST *Parser::handleExpression() {
    ExprAST *LHS;
    LHS = handlePrimary();
    if(!LHS){
        return nullptr;
    }

    return handleBinaryOpExpression(0,LHS);
}


ExprAST *Parser::handleBinaryOpExpression(int ExprPrec, ExprAST *LHS) {

    while(1){
        int TokPrec = BinopPrecedence[(char)currentToken.type];

        if(TokPrec<ExprPrec || currentToken.type==TOK_SEMICOLON || currentToken.type==TOK_CPARENTHESES)
            return LHS;

        Token BinOp = currentToken;
        getNextToken();

        ExprAST *RHS = handlePrimary();

        if(!RHS)
            return LHS;

        int NextPrec = BinopPrecedence[(char)currentToken.type];
        if(TokPrec<NextPrec){
            RHS = handleBinaryOpExpression(TokPrec+1,RHS);
            if(RHS==0)
                return 0;
        }

        LHS = new BinaryExprAST(BinOp.type,LHS,RHS);
    }
}

PrototypeAST *Parser::handlePrototype(const std::string &identifier, const std::string &type) {

    getNextToken();

    return new PrototypeAST(identifier, type);

}

FunctionAST *Parser::handleFunction(std::string identifier, std::string type)
{

    getNextToken();


    PrototypeAST *prototype = handlePrototype(identifier,type);

    ExprAST *body = nullptr;

    getNextToken();


    body = handleExpression();
    return new FunctionAST(prototype, body);


}

void Parser::parse() {

    getNextToken();

    while(currentToken.type != TOK_EOF){
        switch (currentToken.type){
            case TOK_CBRACES:
                getNextToken();
                break;
            default:
                _expressions.push_back(handleExpression());
                getNextToken();
                break;
        }

    }

}


ExprAST *Parser::handleType(std::string type) {


    if(currentToken.type!=TOK_TYPE){
        return Error("missing type", currentToken.line);
    }
    getNextToken();

    if(currentToken.type != TOK_IDENT){
        return Error("missing identifier", currentToken.line);
    }

    std::string identifier = currentToken.value;

    getNextToken();


    switch (currentToken.type) {
        case TOK_SEMICOLON:
            return handleVariable(identifier,type);
        case TOK_OPARENTHESES:
            return handleFunction(identifier,type);
        default:
            return nullptr;
    }

}


VariableExprAST *Parser::handleVariable(std::string identifier, std::string type) {


    VariableExprAST *declaration = new VariableExprAST(identifier,type);
    addVariable(identifier,declaration);
    return declaration;

}


void Parser::addVariable(const std::string &name, VariableExprAST *value) {
    _variables[name] = value;
}


std::vector<ExprAST *> Parser::getExpressions() {
    return _expressions;
}


ExprAST *Parser::handlePrintf() {

    getNextToken();
    if(currentToken.type==TOK_OPARENTHESES){
        getNextToken();
        return new PrintExprAST(handleExpression());
    }
    return nullptr;
}


ExprAST *Parser::handleReturn() {
    if(currentToken.type == TOK_RETURN)
        getNextToken();

    return new ReturnExprAST(handleExpression());

}


WhileExprAST *Parser::handleWhile() {

    ExprAST *expr, *whileBlock = nullptr;
    int whileLine = currentToken.line;
    getNextToken();

    if (currentToken.type != TOK_OPARENTHESES) {
        return ErrorW("Expecting '(' for 'while' loop", whileLine);
    }
    getNextToken();

    expr = handleExpression();

    if (currentToken.type != TOK_CPARENTHESES) {
        return ErrorW("Expecting ')' for 'while' loop", whileLine);
    }
    getNextToken();



    if(currentToken.type!=TOK_OBRACES) {
        return ErrorW("Expecting '{' for 'while' loop", whileLine);
    }

    getNextToken();
    whileBlock = handleExpression();

    return new WhileExprAST(expr,whileBlock);
}


IfExprAST *Parser::handleIf() {
    ExprAST *Cond, *Then, *Else = nullptr;
    int ifLine = currentToken.line;

    getNextToken();

    if(currentToken.type!=TOK_OPARENTHESES){
        printf("Exp (");
        parsed = false;
    }
    getNextToken();


    Cond = handleExpression();

    if(currentToken.type!=TOK_CPARENTHESES){
        return ErrorI("Expecting ) for 'if' statement", ifLine);
    }

    getNextToken();

    if(currentToken.type!=TOK_OBRACES) {
        return ErrorI("Expecting { for If statement", ifLine);
    }
        getNextToken();

        Then = handleExpression();

    getNextToken();

    if(currentToken.type==TOK_ELSE) {
        getNextToken();
        if (currentToken.type == TOK_OBRACES) {
            getNextToken();
            Else = handleExpression();
        }

        getNextToken();

    }


    return new IfExprAST(Cond,Then,Else);
}

ExprAST *Parser::Error(const char *str , int line) {
    fprintf(stderr, "Error: %s on line %d\n", str, line);
    parsed = false;
    return nullptr;
}


PrototypeAST *Parser::ErrorP(const char *str, int line) {
    Error(str,line);
    return nullptr;
}

IfExprAST *Parser::ErrorI(const char *str, int line) {
    Error(str,line);
    return nullptr;
}

WhileExprAST *Parser::ErrorW(const char *str, int line) {
    Error(str,line);
    return nullptr;
}
