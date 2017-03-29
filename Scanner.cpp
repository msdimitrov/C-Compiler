

#include "Scanner.h"
#include <llvm/ADT/StringSwitch.h>

Scanner::Scanner(std::string srcFile)
{
    lines = 1;
    sourceFile = new std::ifstream(srcFile.c_str());
}

Scanner::~Scanner()
{
    delete sourceFile;
}

Token Scanner::Next() {


    Token token;
    char current, peek;

    current = sourceFile->get();

    while (1) {

        while (isspace(current)) {
            if (current == '\n') {
                lines++;
                if(sourceFile->peek()=='\r' || sourceFile->peek()=='\t'){
                    sourceFile->get();
                }
            }
            current = sourceFile->get();
        }

        token.line = lines;


        if (!sourceFile->good() || current == EOF) {
            token.type = TOK_EOF;
            return token;
        }

        if(current == '/'){
            if(sourceFile->peek() == '/'){
                while(current != '\n')
                    current = sourceFile->get();
            }
        }


        if (isalpha(current)) {
            while (isalnum(current) || current == '_') {
                token.value += current;
                current = sourceFile->get();
            }

            if (!isalnum(current))
                sourceFile->putback(current);

            token.type = llvm::StringSwitch<Tokens>(llvm::StringRef(token.value))
                    .Case("int", TOK_TYPE)
                    .Case("bool", TOK_TYPE)
                    .Case("char", TOK_TYPE)
                    .Case("pchar", TOK_TYPE)
                    .Case("printf", TOK_PRINTF)
                    .Case("scanf",TOK_SCANF)
                    .Case("abs", TOK_ABS)
                    .Case("sqr", TOK_SQR)
                    .Case("odd", TOK_ODD)
                    .Case("ord", TOK_ORD)
                    .Case("if", TOK_IF)
                    .Case("else", TOK_ELSE)
                    .Case("while", TOK_WHILE)
                    .Case("break", TOK_BREAK)
                    .Case("continue", TOK_CONTINUE)
                    .Case("nop", TOK_NOP)
                    .Case("return", TOK_RETURN)
                    .Default(TOK_IDENT);

            return token;
        }


        if (isdigit(current)) {
            token.value += current;
            token.type = TOK_NUMBER;
            peek = sourceFile->peek();
            while (isdigit(peek)) {
                token.value += sourceFile->get();
                peek = sourceFile->peek();
            }

            return token;
        }


        if (current == '(') {
            token.type = TOK_OPARENTHESES;
            token.value = current;
            return token;
        }
        if (current == ')') {
            token.type = TOK_CPARENTHESES;
            token.value = current;
            return token;
        }


        if (current == '{') {
            token.type = TOK_OBRACES;
            token.value = current;
            return token;
        }
        if (current == '}') {
            token.type = TOK_CBRACES;
            token.value = current;
            return token;
        }

        if (current == ';') {
            token.type = TOK_SEMICOLON;
            token.value += current;
            return token;
        }

        if (current == '=') {
            token.type = TOK_EQUALS;
            return token;
        }

        if (current == '+') {
            if(sourceFile->peek() == '='){
                sourceFile->get();
                token.type = TOK_ADDASS;
            }
            if(sourceFile->peek() == '+'){
                sourceFile->get();
                token.type = TOK_INC;
            }
            token.type = TOK_PLUS;
            return token;
        }

        if(current == '-'){
            if(sourceFile->peek() == '='){
                sourceFile->get();
                token.type = TOK_SUBASS;
            }
            if(sourceFile->peek() == '-'){
                sourceFile->get();
                token.type = TOK_DEC;
            }
            token.type = TOK_MINUS;
            return token;
        }

        if(current == '*'){
            if(sourceFile->peek() == '='){
                sourceFile->get();
                token.type = TOK_MULASS;
            }
            token.type = TOK_ASTERISK;
            return token;
        }

        if(current == '/'){
            if(sourceFile->peek() == '='){
                sourceFile->get();
                token.type = TOK_DIVASS;
            }
            token.type = TOK_DIVIDE;
            return token;
        }

        if(current == '%'){
            if(sourceFile->peek() == '='){
                sourceFile->get();
                token.type = TOK_MODASS;
            }
            token.type = TOK_REMINDER;
            return token;
        }

        if(current == '|'){
            if(sourceFile->peek() == '|'){
                sourceFile->get();
                token.type = TOK_LOG_OR;
            }
            token.type = TOK_BITWISE_OR;
            return token;
        }

        if(current == '&'){
            if(sourceFile->peek() == '&'){
                sourceFile->get();
                token.type = TOK_LOG_AND;
            }
            token.type = TOK_BITWISE_AND;
            return token;
        }

        if(current == '!'){
            token.value = current;
            token.type = TOK_LOG_NOT;
            return token;
        }

        if(current == '<'){
            token.value = current;
            token.type = TOK_LESS_THAN;
            return token;
        }

        if(current == '>'){
            token.value = current;
            token.type = TOK_GREATER_THAN;
            return token;
        }




    }


}