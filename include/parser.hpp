#ifndef PARSER_HPP
#define PARSER_HPP

#include "../include/lexer.hpp"
#include "../include/AST.hpp"
#include <vector>

class Parser
{
public:
    explicit Parser(const std::vector<Token>& tokens);
    ~Parser();

    Block* parse();

private:
    std::vector<Token> tokens;
    size_t pos;

    Token currentToken() const;
    Token peek() const;
    Token consume();
    bool match(Token::Type type);
    bool check(Token::Type type) const;

    Block* parseBlock();
    Statement* parseStatement();
    Assignment* parseAssignment();
    LetStatement* parseLetStatement();
    ReadStatement* parseReadStatement();
    PrintStatement* parsePrintStatement();
    IfStatement* parseIfStatement();
    WhileStatement* parseWhileStatement();
    LabelStatement* parseLabelStatement();
    GotoStatement* parseGotoStatement();
    Expression* parseExpression();
    Expression* parseTerm();
    Expression* parseFactor();
};

#endif