#include "../include/AST.hpp"
#include "AST.hpp"

IntegerLiteral::IntegerLiteral(int v) : value(v) {}

BinaryExpression::BinaryExpression(Expression *l, const std::string &op, Expression *r)
    : left(l), op(op), right(r) {}

BinaryExpression::~BinaryExpression()
{
    delete left;
    delete right;
}

Variable::Variable(const std::string &n) : name(n) {}

LetStatement::LetStatement(const std::string &variableName, Expression *v)
    : variableName(variableName), value(v) {}

LetStatement::~LetStatement()
{
    delete value;
}

Assignment::Assignment(const std::string &variableName, Expression *v)
    : variableName(variableName), value(v) {}

Assignment::~Assignment()
{
    delete value;
}

ReadStatement::ReadStatement(const std::string &variableName) : variableName(variableName) {}

PrintStatement::PrintStatement(Expression *v) : value(v) {}

PrintStatement::~PrintStatement()
{
    delete value;
}

Block::~Block()
{
    for (Statement *stmt : statements)
    {
        delete stmt;
    }
}

IfStatement::IfStatement(Expression *c, Block *t, Block *e) 
            : condition(c), thenBlock(t), elseBlock(e) {}

IfStatement::~IfStatement()
{
    delete condition;
    delete thenBlock;
    delete elseBlock;
}

WhileStatement::WhileStatement(Expression *c, Block *b) 
                : condition(c), block(b) {}

WhileStatement::~WhileStatement()
{
    delete condition;
    delete block;
}

LabelStatement::LabelStatement(const std::string &l) : labelName(l) {}

GotoStatement::GotoStatement(const std::string &l) : labelName(l) {}
