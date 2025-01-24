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
        KEYWORD, IDENTIFIER, NUMBER, OPERATOR, SYMBOL, END, PAREN, UNKNOWN
    };

    Type type;
    std::string value;

    Token(Type t, const std::string& v) : type(t), value(v) {}

    std::string printType () {
        switch (type) {
            case Type::KEYWORD:
                return "KEYWORD";
            case Type::IDENTIFIER:
                return "IDENTIFIER";
            case Type::NUMBER:
                return "NUMBER";
            case Type::OPERATOR:
                return "OPERATOR";
            case Type::SYMBOL:
                return "SYMBOL";
            case Type::END:
                return "END";
            case Type::PAREN:
                return "PAREN";
            case Type::UNKNOWN:
                return "UNKNOWN";
        }

        return "";
    }
};

class Lexer
{
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;

    char currentChar() const;
    char peek() const;
    bool isOperatorStart(char c) const;
    bool isKeyword(const std::string& word) const;
    void advance();

    Token nextToken();

    Token parseKeywordOrIdentifier();
    Token parseNumber();
    Token parseOperator();
};

#endif 
