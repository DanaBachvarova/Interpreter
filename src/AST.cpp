#include "../include/ast.hpp"
#include <iostream>

IntegerLiteral::IntegerLiteral(int v) : value(v) {}

void IntegerLiteral::print() const 
{
    std::cout << value;
}

BinaryExpression::BinaryExpression(Expression *l, const std::string &op, Expression *r)
    : left(l), op(op), right(r) {}

BinaryExpression::~BinaryExpression()
{
    delete left;
    delete right;
}

void BinaryExpression::print() const
{
    left->print();
    std::cout << " " << op << " ";
    right->print();
}

Variable::Variable(const std::string &n) : name(n) {}

void Variable::print() const
{
    std::cout << name << " ";
}

LetStatement::LetStatement(const std::string &variableName, Expression *v)
    : variableName(variableName), value(v) {}

LetStatement::LetStatement(const std::string &variableName) : variableName(variableName) {}

LetStatement::~LetStatement()
{
    delete value;
}

void LetStatement::print() const
{
    std::cout << "LET " << variableName;
    if (value)
    {
        std::cout << " = ";
        value->print();
    }
}

Assignment::Assignment(const std::string &variableName, Expression *v)
    : variableName(variableName), value(v) {}

Assignment::~Assignment()
{
    delete value;
}

void Assignment::print() const
{
    std::cout << variableName << " = ";
    value->print();
}

ReadStatement::ReadStatement(const std::string &variableName) : variableName(variableName) {}

void ReadStatement::print() const
{
    std::cout << "READ " << variableName;
}

PrintStatement::PrintStatement(Expression *v) : value(v) {}

PrintStatement::~PrintStatement()
{
    delete value;
}

void PrintStatement::print() const
{
    std::cout << "PRINT ";
    value->print();
}

Block::~Block()
{
    for (Statement *stmt : statements)
    {
        delete stmt;
    }
}

void Block::print() const
{
    for (const auto* stmt : statements)
    {
        stmt->print();
        std::cout << std::endl;
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

void IfStatement::print() const
{
    std::cout << "IF ";
    condition->print();
    std::cout << std::endl;
    thenBlock->print();
    if (elseBlock)
    {
        std::cout << "ELSE" << std::endl;
        elseBlock->print();
    }
    std::cout << "ENDIF" << std::endl;
}

WhileStatement::WhileStatement(Expression *c, Block *b) 
                : condition(c), block(b) {}

WhileStatement::~WhileStatement()
{
    delete condition;
    delete block;
}

void WhileStatement::print() const
{
    std::cout << "WHILE ";
    condition->print();
    std::cout << std::endl;
    block->print();
    std::cout << "DONE" << std::endl;
}

LabelStatement::LabelStatement(const std::string &l) : labelName(l) {}

void LabelStatement::print() const
{
    std::cout << "LABEL " << labelName << std::endl;
}

GotoStatement::GotoStatement(const std::string &l) : labelName(l) {}

void GotoStatement::print() const
{
    std::cout << "GOTO " << labelName << std::endl;
}
