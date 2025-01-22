#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cctype>

struct Token
{
    enum class Type {
        KEYWORD, IDENTIFIER, NUMBER, OPERATOR, SYMBOL, END
    };

    Type type;
    std::string value;

    Token(Type t, std::string& v) : type(t), value(v) {}
};

class Lexer
{
public:
    explicit Lexer(const std::string& source) {}
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;

    char currentChar() const;
    void advance();

    Token nextToken();

    Token parseKeywordOrIdentifier();
    Token parseNumber();
    Token parseOperator();
    Token parseSymbol();
};

#endif 
