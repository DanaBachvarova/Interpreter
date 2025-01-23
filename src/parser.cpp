#include "../include/parser.hpp"
#include <iostream>
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

Parser::~Parser() {}

Token Parser::currentToken() const
{
    if (pos < tokens.size())
    {
        return tokens[pos];
    }

    return Token(Token::Type::END, "");
}

Token Parser::peek() const
{
    if (pos + 1 < tokens.size())
    {
        return tokens[pos + 1];
    }

    return Token(Token::Type::END, "");
}

Token Parser::consume()
{
    Token token = currentToken();
    if (pos < tokens.size())
    {
        ++pos;
    }

    return token;
}

bool Parser::match(Token::Type type)
{
    if (currentToken().type == type)
    {
        consume();
        return true;
    }

    return false;
}

bool Parser::check(Token::Type type) const
{
    return currentToken().type == type;
}

Block* Parser::parse()
{
    return parseBlock();
}

Block* Parser::parseBlock()
{
    Block* block = new Block();
    while (currentToken().type != Token::Type::END)
    {
        Statement* stmt = parseStatement();
        if (stmt)
        {
            block->statements.push_back(stmt);
        }
    }

    return block;
}

Statement* Parser::parseStatement()
{
    if (match(Token::Type::KEYWORD))
    {
        if (currentToken().value == "LET")
        {
            return parseLetStatement();
        }
        else if (currentToken().value == "READ")
        {
            return parseReadStatement();
        }
        else if (currentToken().value == "PRINT")
        {
            return parsePrintStatement();
        }
        else if (currentToken().value == "IF")
        {
            return parseIfStatement();
        }
        else if (currentToken().value == "WHILE")
        {
            return parseWhileStatement();
        }
        else if (currentToken().value == "LABEL")
        {
            return parseLabelStatement();
        }
        else if (currentToken().value == "GOTO")
        {
            return parseGotoStatement();
        }
    }

    return nullptr;
}

LetStatement* Parser::parseLetStatement()
{
    consume(); 
    if (check(Token::Type::IDENTIFIER))
    {
        std::string variableName = currentToken().value;
        consume();
        if (match(Token::Type::OPERATOR) && currentToken().value == "=")
        {
            Expression* value = parseExpression();
            return new LetStatement(variableName, value);
        }
    }

    throw std::runtime_error("Invalid LET statement");
}

ReadStatement* Parser::parseReadStatement()
{
    consume();
    if (check(Token::Type::IDENTIFIER))
    {
        std::string variableName = currentToken().value;
        consume();
        return new ReadStatement(variableName);
    }

    throw std::runtime_error("Invalid READ statement");
}

PrintStatement* Parser::parsePrintStatement()
{
    consume();
    Expression* value = parseExpression();
    return new PrintStatement(value);
}

// тук трябва да дооправя, защото не е задължително да има Else
IfStatement* Parser::parseIfStatement()
{
    consume();
    Expression* condition = parseExpression();
    Block* thenBlock = parseBlock();
    Block* elseBlock = nullptr;
    if (match(Token::Type::KEYWORD) && currentToken().value == "ELSE")
    {
        elseBlock = parseBlock();
        return new IfStatement(condition, thenBlock, elseBlock);
    }

    throw std::runtime_error("Invalid IF statement");
}

WhileStatement* Parser::parseWhileStatement()
{
    consume();
    Expression* condition = parseExpression();
    Block* block = parseBlock();
    return new WhileStatement(condition, block);
}

LabelStatement* Parser::parseLabelStatement()
{
    consume();
    if (check(Token::Type::IDENTIFIER))
    {
        std::string labelName = currentToken().value;
        consume();
        return new LabelStatement(labelName);
    }

    throw std::runtime_error("Invalid LABEL statement");
}

GotoStatement* Parser::parseGotoStatement()
{
    consume();
    if (check(Token::Type::IDENTIFIER))
    {
        std::string labelName = currentToken().value;
        consume();
        return new GotoStatement(labelName);
    }

    throw std::runtime_error("Invalid GOTO statement");
}