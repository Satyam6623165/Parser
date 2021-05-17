#ifndef __TOKEN_H_INCLUDED__
#define __TOKEN_H_INCLUDED__

#include<bits/stdc++.h>

using namespace std;

enum Token {
    VOID,
    MAIN,
    INT,
    FLOAT,
    STRING,
    STRUCT,
    UNION,
    FOR,
    RETURN,
    ADD,
    SUB,
    MUL,
    DIV,
    LT,
    GT,
    EQUALS,
    BRACE_OPEN,
    BRACE_CLOSE,
    PARAN_OPEN,
    PARAN_CLOSE,
    SEMICOLON,
    IDENTIFIER,
    LITERAL,
    INTEGER_CONST,
    FLOAT_CONST,
    PERIOD,
    COMMA,
    END
};

unordered_map<string, Token> strToEnum = {
    {"VOID", Token::VOID},
    {"MAIN", Token::MAIN},
    {"INT", Token::INT},
    {"FLOAT", Token::FLOAT},
    {"STRING", Token::STRING},
    {"STRUCT", Token::STRUCT},
    {"UNION", Token::UNION},
    {"FOR", Token::FOR},
    {"RETURN", Token::RETURN},
    {"ADD", Token::ADD},
    {"SUB", Token::SUB},
    {"MUL", Token::MUL},
    {"DIV", Token::DIV},
    {"LT", Token::LT},
    {"GT", Token::GT},
    {"EQUALS", Token::EQUALS},
    {"BRACE_OPEN", Token::BRACE_OPEN},
    {"BRACE_CLOSE", Token::BRACE_CLOSE},
    {"PARAN_OPEN", Token::PARAN_OPEN},
    {"PARAN_CLOSE", Token::PARAN_CLOSE},
    {"SEMICOLON", Token::SEMICOLON},
    {"IDENTIFIER", Token::IDENTIFIER},
    {"LITERAL", Token::LITERAL},
    {"INTEGER_CONST", Token::INTEGER_CONST},
    {"FLOAT_CONST", Token::FLOAT_CONST},
    {"PERIOD", Token::PERIOD},
    {"COMMA", Token::COMMA},
    {"$", Token::END}
};

unordered_map<Token, string> enumToStr = {
    {Token::VOID, "VOID"},
    {Token::MAIN, "MAIN"},
    {Token::INT, "INT"},
    {Token::FLOAT, "FLOAT"},
    {Token::STRING, "STRING"},
    {Token::STRUCT, "STRUCT"},
    {Token::UNION, "UNION"},
    {Token::FOR, "FOR"},
    {Token::RETURN, "RETURN"},
    {Token::ADD, "ADD"},
    {Token::SUB, "SUB"},
    {Token::MUL, "MUL"},
    {Token::DIV, "DIV"},
    {Token::LT, "LT"},
    {Token::GT, "GT"},
    {Token::EQUALS, "EQUALS"},
    {Token::BRACE_OPEN, "BRACE_OPEN"},
    {Token::BRACE_CLOSE, "BRACE_CLOSE"},
    {Token::PARAN_OPEN, "PARAN_OPEN"},
    {Token::PARAN_CLOSE, "PARAN_CLOSE"},
    {Token::SEMICOLON, "SEMICOLON"},
    {Token::IDENTIFIER, "IDENTIFIER"},
    {Token::LITERAL, "LITERAL"},
    {Token::INTEGER_CONST, "INTEGER_CONST"},
    {Token::FLOAT_CONST, "FLOAT_CONST"},
    {Token::PERIOD, "PERIOD"},
    {Token::COMMA, "COMMA"},
    {Token::END, "$"}
};

#endif