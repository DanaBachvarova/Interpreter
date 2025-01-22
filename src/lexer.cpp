#include "lexer.hpp"
#include <iostream>
#include <cctype>
#include <unordered_set>

Lexer::Lexer(const std::string& source) : input(source), pos(0) {}

char Lexer::currentChar() const
{
    if (pos < input.size())
    {
        return input[pos];
    }

    return '\0';
}

char Lexer::peek() const
{
    if (pos + 1 < input.size())
    {
        return input[pos + 1];
    }

    return '\0';
}

bool Lexer::isOperatorStart(char c) const
{
    return c == '=' || c == '!' || c == '<' || 
            c == '>' || c == '+' || c == '-' || 
            c == '*' || c == '/' || c == '%' ||
            c == '&' || c == '|';
}

bool Lexer::isKeyword(const std::string &word) const
{
    static const std::unordered_set<std::string> keywords = {
        "LABEL", "GOTO", "LET", "READ", "PRINT", "IF", "ENDIF", "ELSE", "WHILE", "DONE"
    };

    return keywords.count(word) > 0;
}

void Lexer::advance()
{
    if (pos < input.size())
    {
        ++pos;
    }
}

Token Lexer::nextToken()
{
    while (std::isspace(currentChar()))
    {
        advance();
    }

    if (currentChar() == '\0')
    {
        return Token(Token::Type::END, "");
    }

    if (std::isalpha(currentChar()))
    {
        return parseKeywordOrIdentifier();
    }

    if (std::isdigit(currentChar()))
    {
        return parseNumber();
    }

    if (isOperatorStart(currentChar()))
    {
        return parseOperator();
    }

    if (currentChar() == '(' || currentChar() == ')')
    {
        char symbol = currentChar();
        advance();
        return Token(Token::Type::PAREN, std::string(1, symbol));
    }

    std::cerr << "Unexpected character: " << currentChar() << std::endl;
    advance();
    return Token(Token::Type::UNKNOWN, "");
}

Token Lexer::parseOperator()
{
    char first = currentChar();
    char second = peek();

    if ((first == '=' && second == '=') ||
        (first == '!' && second == '=') ||
        (first == '<' && second == '=') ||
        (first == '>' && second == '=') ||
        (first == '&' && second == '&') ||
        (first == '|' && second == '|'))
    {
        advance();
        advance();
        return Token(Token::Type::OPERATOR, std::string(1, first) + second);
    }

    if (first == '=' || first == '!' || first == '<' || first == '>' 
        || first == '+' || first == '-' || first == '*' || first == '/' ||
        first == '%')
    {
        advance();
        return Token(Token::Type::OPERATOR, std::string(1, first));
    }

    std::cerr << "Unexpected operator: " << first << std::endl;
    advance();
    return Token(Token::Type::UNKNOWN, "");
}

Token Lexer::parseKeywordOrIdentifier()
{
    std::string word;
    while (std::isalnum(currentChar()))
    {
        word += currentChar();
        advance();
    }

    if (isKeyword(word))
    {
        return Token(Token::Type::KEYWORD, word);
    }

    return Token(Token::Type::IDENTIFIER, word);
}

Token Lexer::parseNumber()
{
    std::string number;
    while (std::isdigit(currentChar()))
    {
        number += currentChar();
        advance();
    }

    return Token(Token::Type::NUMBER, number);
}