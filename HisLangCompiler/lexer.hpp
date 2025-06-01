// lexer.hpp - MyLang lexer interface
#pragma once
#include <vector>
#include <string>
#include <sstream>


enum class TokenType {
    Keyword,
    Identifier,
    StringLiteral,
    Symbol,
    Indent,
    Dedent,
    Newline,
    EOFToken,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

std::vector<Token> lex(const std::vector<std::string>& lines);
