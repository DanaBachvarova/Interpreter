#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class Expression : public ASTNode {};

class IntegerLiteral : public Expression {
public:
    int value;
    explicit IntegerLiteral(int v);
};

class BinaryExpression : public Expression {
public:
    Expression* left;
    std::string op;
    Expression* right;

    BinaryExpression(Expression* l, const std::string& op, Expression* r);
    ~BinaryExpression();
};

class Variable : public Expression {
public:
    std::string name;
    explicit Variable(const std::string& n);
};

class Statement : public ASTNode {};

class LetStatement : public Statement {
public:
    std::string variableName;
    Expression* value;

    LetStatement(const std::string& variableName, Expression* v);
    LetStatement(const std::string& variableName);
    ~LetStatement();
};

class Assignment : public Statement {
public:
    std::string variableName;
    Expression* value;

    Assignment(const std::string& variableName, Expression* v);
    ~Assignment();
};

class ReadStatement : public Statement {
public:
    std::string variableName;
    explicit ReadStatement(const std::string& variableName);
};

class PrintStatement : public Statement {
public:
    Expression* value;

    explicit PrintStatement(Expression* v);
    ~PrintStatement();
};

class Block : public Statement {
public:
    std::vector<Statement*> statements;

    ~Block();
};

class IfStatement : public Statement {
public:
    Expression* condition;
    Block* thenBlock;
    Block* elseBlock;

    IfStatement(Expression* c, Block* t, Block* e);
    ~IfStatement();
};

class WhileStatement : public Statement {
public:
    Expression* condition;
    Block* block;

    WhileStatement(Expression* c, Block* b);
    ~WhileStatement();
};

class LabelStatement : public Statement {
public:
    std::string labelName;

    explicit LabelStatement(const std::string& l);
};

class GotoStatement : public Statement {
public:
    std::string labelName;

    explicit GotoStatement(const std::string& l);
};

#endif