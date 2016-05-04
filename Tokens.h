

#ifndef MTPROJECT_TOKENS_H
#define MTPROJECT_TOKENS_H

#include <string>

enum Tokens
{
    TOK_EOF = 'E',
    TOK_IDENT = 'I',
    TOK_NUMBER = 'N',
    TOK_TYPE = 'T',
    TOK_OPARENTHESES = '(',
    TOK_CPARENTHESES = ')',
    TOK_OBRACES = '{',
    TOK_CBRACES = '}',
    TOK_CHAR = 'C',
    TOK_SEMICOLON = ';',
    TOK_EQUALS = '=',
    TOK_PLUS = '+',
    TOK_MINUS = '-',
    TOK_ASTERISK = '*',
    TOK_REMINDER = '%',
    TOK_BITWISE_OR = '|',
    TOK_BITWISE_AND = '&',
    TOK_DIVIDE = '/',
    TOK_INC = 'i',
    TOK_DEC = 'd',
    TOK_IF = 'f',
    TOK_ELSE = 'e',
    TOK_WHILE = 'w',
    TOK_BREAK = 'b',
    TOK_CONTINUE = 'o',
    TOK_LESS_THAN = '<',
    TOK_GREATER_THAN = '>',
    TOK_RETURN = 'r',
    TOK_PRINTF = 'p',
    TOK_ABS = 'c',
    TOK_SQR = 'Q',
    TOK_ODD = 'D',
    TOK_ORD = 'R',
    TOK_SCANF = 's',
    TOK_ADDASS = '@',
    TOK_SUBASS = '#',
    TOK_MULASS = '$',
    TOK_DIVASS = '^',
    TOK_MODASS = '.',
    TOK_LOG_OR = '~',
    TOK_LOG_AND = '"',
    TOK_LOG_NOT = '!',


};

struct Token
{
    Tokens type;
    std::string value;
    int line;
};

#endif //MTPROJECT_TOKENS_H
