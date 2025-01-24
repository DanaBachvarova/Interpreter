#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() const = 0;
};

class Expression : public ASTNode {};

class IntegerLiteral : public Expression {
public:
    int value;
    explicit IntegerLiteral(int v);

    void print() const override;
};

class BinaryExpression : public Expression {
public:
    Expression* left;
    std::string op;
    Expression* right;

    BinaryExpression(Expression* l, const std::string& op, Expression* r);
    ~BinaryExpression();
    void print() const override;
};

class Variable : public Expression {
public:
    std::string name;
    explicit Variable(const std::string& n);
    void print() const override;
};

class Statement : public ASTNode {};

class LetStatement : public Statement {
public:
    std::string variableName;
    Expression* value;

    LetStatement(const std::string& variableName, Expression* v);
    LetStatement(const std::string& variableName);
    ~LetStatement();
    void print() const override;
};

class Assignment : public Statement {
public:
    std::string variableName;
    Expression* value;

    Assignment(const std::string& variableName, Expression* v);
    ~Assignment();
    void print() const override;
};

class ReadStatement : public Statement {
public:
    std::string variableName;
    explicit ReadStatement(const std::string& variableName);
    void print() const override;
};

class PrintStatement : public Statement {
public:
    Expression* value;

    explicit PrintStatement(Expression* v);
    ~PrintStatement();
    void print() const override;
};

class Block : public Statement {
public:
    std::vector<Statement*> statements;

    ~Block();
    void print() const override;
    int size() const { return statements.size(); }
};

class IfStatement : public Statement {
public:
    Expression* condition;
    Block* thenBlock;
    Block* elseBlock;

    IfStatement(Expression* c, Block* t, Block* e);
    ~IfStatement();
    void print() const override;
};

class WhileStatement : public Statement {
public:
    Expression* condition;
    Block* block;

    WhileStatement(Expression* c, Block* b);
    ~WhileStatement();
    void print() const override;
};

class LabelStatement : public Statement {
public:
    std::string labelName;

    explicit LabelStatement(const std::string& l);
    void print() const override;
};

class GotoStatement : public Statement {
public:
    std::string labelName;

    explicit GotoStatement(const std::string& l);
    void print() const override;
};

#endif