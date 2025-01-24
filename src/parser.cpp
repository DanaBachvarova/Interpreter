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
    ++pos;
    return currentToken();
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

        consume();
    }

    return block;
}

Block *Parser::parseWhileBlock()
{
    Block* block = new Block();
    while (currentToken().value != "DONE")
    {
        Statement* stmt = parseStatement();
        if (stmt)
        {
            block->statements.push_back(stmt);
        }

        consume();
    }

    return block;
}

Block *Parser::parseIfBlock()
{
    Block* block = new Block();
    while (currentToken().value != "ENDIF" && currentToken().value != "ELSE")	
    {
        Statement* stmt = parseStatement();
        if (stmt)
        {
            block->statements.push_back(stmt);
        }

        consume();
    }

    return block;
}

Statement* Parser::parseStatement()
{
    if (check(Token::Type::KEYWORD))
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
        if (peek().value == "=")
        {
            consume();
            Expression* value = parseExpression();
            return new LetStatement(variableName, value);
        }
        else 
        {
            return new LetStatement(variableName);
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
        return new ReadStatement(variableName);
    }

    throw std::runtime_error("Invalid READ statement");
}

PrintStatement* Parser::parsePrintStatement()
{
    Expression* value = parseExpression();
    return new PrintStatement(value);
}

IfStatement* Parser::parseIfStatement()
{
    Expression* condition = parseExpression();
    Block* thenBlock = parseIfBlock();
    Block* elseBlock = nullptr;
    if (check(Token::Type::KEYWORD) && currentToken().value == "ELSE")
    {
        consume();
        elseBlock = parseIfBlock();
        return new IfStatement(condition, thenBlock, elseBlock);
    }

    throw std::runtime_error("Invalid IF statement");
}

WhileStatement* Parser::parseWhileStatement()
{
    Expression* condition = parseExpression();
    Block* block = parseWhileBlock();
    return new WhileStatement(condition, block);
}

LabelStatement* Parser::parseLabelStatement()
{
    consume();
    if (check(Token::Type::IDENTIFIER))
    {
        std::string labelName = currentToken().value;
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
        return new GotoStatement(labelName);
    }

    throw std::runtime_error("Invalid GOTO statement");
}

Expression* Parser::parseExpression()
{
    consume();
    if (check(Token::Type::NUMBER))
    {
        return new IntegerLiteral(std::stoi(currentToken().value));
    }
    else if (check(Token::Type::IDENTIFIER))
    {
        return new Variable(currentToken().value);
    }

    throw std::runtime_error("Invalid expression");
}