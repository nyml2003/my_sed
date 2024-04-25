
#ifndef SED_AST_HPP
#define SED_AST_HPP
#include "analyzer.hpp"
#include "error.hpp"
#include "generator.hpp"
#include "ir.hpp"
#include "location.hh"
#include <array>
#include <string>
#include <vector>
namespace SED::AST
{
class Value;
class Variable;
enum class ValueType;

extern std::map<NodeClass, std::string> NodeClassEnumMap;
extern std::string NodeClassEnumMapToString(NodeClass nodeClass);

class Node : public Generator::MermaidGenerator, public Generator::IRGenerator, public Analyzer::Analyzable
{
  public:
    enum class NodeClass
    {
        // Unknown, 如果是这个类型，说明有错误
        UNKNOWN,
        // Constant
        INT_32,
        FLOAT_32,
        BOOLEAN,
        POINTER,
        CHAR,
        VOID,
        // Mutable
        UNARY,
        BINARY,
        VARIABLE,
        FUNCTION_CALL,
        // Statement
        RETURN_STATEMENT,
        WHILE_STATEMENT,
        IF_STATEMENT,
        CONTINUE_STATEMENT,
        EXPRESSION_STATEMENT,
        BREAK_STATEMENT,
        ASSIGNMENT,
        // others
        VARIABLE_DECLARATION,
        FUNCTION_DECLARATION,
        FUNCTION_DEFINITION,
        COMPILATION_UNIT,
        BLOCK,
    } nodeClass;
    static std::map<NodeClass, std::string> NodeClassEnumMap;
    static std::string NodeClassEnumMapToString(NodeClass nodeClass);
    yy::position begin;
    yy::position end;
    Node(NodeClass _nodeClass);
    NodeClass getNodeClass() const;
    virtual void toMermaid() = 0;
    virtual void toIR() = 0;
    virtual void analyze() = 0;
};
/**
 * @brief 变量声明
 * (const) int a = 1;
 * TODO: 1. 支持const
 * TODO: 2. 语义分析不完整, 需要继续考虑
 */
class VariableDeclaration : public Node
{
  private:
    ValueType type;
    Variable *variable;
    Value *value;
    bool canReassign;

  public:
    explicit VariableDeclaration();

    /*set, get*/

    VariableDeclaration *setVariable(Variable *_variable);

    VariableDeclaration *setValue(Value *_value);

    VariableDeclaration *setType(ValueType _type);

    VariableDeclaration *setCanReassign(bool _canReassign);

    Variable *getVariable() const;

    Value *getValue() const;

    ValueType getType() const;

    bool getCanReassign() const;

    /* 对于generator接口的实现 */

    void toMermaid() override;

    void toIR() override;

    /* 对于analyzer接口的实现 */

    void analyze() override;
};

class Assignment : public Node
{
    Variable *variable;
    Value *value;

  public:
    explicit Assignment();

    Assignment *setVariable(Variable *_variable);

    Assignment *setValue(Value *_value);

    void toMermaid() override;

    void toIR() override;

    Variable *getVariable() const;

    Value *getValue() const;

    void analyze() override;
};

class BreakStatement : public Node
{
  public:
    explicit BreakStatement();
    void toMermaid() override;

    void toIR() override;
    void analyze() override;
};

class FunctionDeclaration : public Node
{
    ValueType returnType;
    std::string name;

  public:
    explicit FunctionDeclaration();
    FunctionDeclaration *setReturnType(ValueType _returnType);
    FunctionDeclaration *setName(const std::string &_name);
    ValueType getReturnType() const;
    std::string getName() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class ExpressionStatement : public Node
{
    Value *value;

  public:
    explicit ExpressionStatement();
    ExpressionStatement *setValue(Value *_value);
    Value *getValue() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class CompilationUnit : public Node
{
    std::vector<Node *> nodes;

  public:
    explicit CompilationUnit();
    CompilationUnit *setNodes(const std::vector<Node *> &_nodes);
    std::vector<Node *> getNodes() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class Block : public Node
{
    std::vector<Node *> nodes;

  public:
    explicit Block();
    Block *setNodes(const std::vector<Node *> &_nodes);
    std::vector<Node *> getNodes() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class FunctionDefinition : public Node
{
    FunctionDeclaration *declaration;
    Block *block;

  public:
    explicit FunctionDefinition();
    FunctionDefinition *setDeclaration(FunctionDeclaration *_declaration);
    FunctionDefinition *setBlock(Block *_block);
    FunctionDeclaration *getDeclaration() const;
    Block *getBlock() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class ReturnStatement : public Node
{
    Value *value;

  public:
    explicit ReturnStatement();
    ReturnStatement *setValue(Value *_value);
    Value *getValue() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class WhileStatement : public Node
{
    Value *condition;
    Node *body;

  public:
    explicit WhileStatement();
    WhileStatement *setCondition(Value *_condition);
    WhileStatement *setBody(Node *_body);
    Value *getCondition() const;
    Node *getBody() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class IfStatement : public Node
{
    Value *condition;
    Node *thenBody;
    Node *elseBody;

  public:
    explicit IfStatement();
    IfStatement *setCondition(Value *_condition);
    IfStatement *setThenBody(Node *_thenBody);
    IfStatement *setElseBody(Node *_elseBody);
    Value *getCondition() const;
    Node *getThenBody() const;
    Node *getElseBody() const;
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};

class ContinueStatement : public Node
{
  public:
    explicit ContinueStatement();
    void toMermaid() override;
    void toIR() override;
    void analyze() override;
};
}; // namespace SED::AST

#endif // SED_AST_HPP
