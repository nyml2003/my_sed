

#ifndef SED_VALUE_HPP
#define SED_VALUE_HPP
#include "ast.hpp"
#include <map>
#include <optional>
#include <string>
namespace SED::AST
{
class Node;
class Constant;
class Value : public Node
{
  private:
    Enumeration::ValueType valueType;

  public:
    explicit Value(Enumeration::NodeClass _nodeClass, Enumeration::ValueType _valueType);
    virtual Enumeration::ValueType getValueType();
    Value *setValueType(Enumeration::ValueType _valueType);
    virtual Constant *_add_(Value *other) = 0;
    virtual Constant *_sub_(Value *other) = 0;
    virtual Constant *_mul_(Value *other) = 0;
    virtual Constant *_div_(Value *other) = 0;
    virtual Constant *_mod_(Value *other) = 0;
    virtual Constant *_and_(Value *other) = 0;
    virtual Constant *_or_(Value *other) = 0;
    virtual Constant *_eq_(Value *other) = 0;
    virtual Constant *_ne_(Value *other) = 0;
    virtual Constant *_lt_(Value *other) = 0;
    virtual Constant *_le_(Value *other) = 0;
    virtual Constant *_gt_(Value *other) = 0;
    virtual Constant *_ge_(Value *other) = 0;
    virtual Constant *_pos_() = 0;
    virtual Constant *_neg_() = 0;
    virtual Constant *_not_() = 0;
    virtual Enumeration::ValueType _add_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _sub_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _mul_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _div_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _mod_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _and_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _or_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _eq_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _ne_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _lt_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _le_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _gt_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _ge_type_(Enumeration::ValueType other) = 0;
    virtual Enumeration::ValueType _pos_type_() = 0;
    virtual Enumeration::ValueType _neg_type_() = 0;
    virtual Enumeration::ValueType _not_type_() = 0;
    virtual Constant *asInt32() = 0;
    virtual Constant *asFloat32() = 0;
    virtual Constant *asBoolean() = 0;
    virtual Constant *asPointer() = 0;
    virtual Constant *asChar() = 0;
    virtual bool isConstant() = 0;
    virtual Constant *constantify() = 0;
    void analyze() override;
};
class Constant : public Value
{
  public:
    explicit Constant(Enumeration::ValueType _valueType);
    Constant *_add_(Value *other) override;
    Constant *_sub_(Value *other) override;
    Constant *_mul_(Value *other) override;
    Constant *_div_(Value *other) override;
    Constant *_mod_(Value *other) override;
    Constant *_and_(Value *other) override;
    Constant *_or_(Value *other) override;
    Constant *_eq_(Value *other) override;
    Constant *_ne_(Value *other) override;
    Constant *_lt_(Value *other) override;
    Constant *_le_(Value *other) override;
    Constant *_gt_(Value *other) override;
    Constant *_ge_(Value *other) override;
    Constant *_pos_() override;
    Constant *_neg_() override;
    Constant *_not_() override;
    Enumeration::ValueType _add_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _sub_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _mul_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _div_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _mod_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _and_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _or_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _eq_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _ne_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _lt_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _le_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _gt_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _ge_type_(Enumeration::ValueType other) override;
    Enumeration::ValueType _pos_type_() override;
    Enumeration::ValueType _neg_type_() override;
    Enumeration::ValueType _not_type_() override;
    virtual bool isConstant() override = 0;
    Constant *constantify() override;
    virtual bool isInt32();
    Constant *asInt32() override;
    Constant *asFloat32() override;
    Constant *asBoolean() override;
    Constant *asPointer() override;
    Constant *asChar() override;
    virtual bool isFloat32();
    virtual bool isBoolean();
    virtual bool isPointer();
    virtual bool isVoid();
    virtual bool isChar();
    virtual std::string toIRString() = 0;
    static Constant *createValue(Enumeration::ValueType type);
};
class Int32 : public Constant
{
    std::optional<int32_t> value{};

  public:
    explicit Int32();
    std::string toIRString() override;
    void toMermaid() override;
    void toIR() override;
    [[nodiscard]] int32_t getValue() const;
    Int32 *setValue(int32_t _value);
    Constant *_add_(Value *other) override;
    Enumeration::ValueType _add_type_(Enumeration::ValueType other) override;
    Constant *_sub_(Value *other) override;
    Enumeration::ValueType _sub_type_(Enumeration::ValueType other) override;
    Constant *_mul_(Value *other) override;
    Enumeration::ValueType _mul_type_(Enumeration::ValueType other) override;
    Constant *_div_(Value *other) override;
    Enumeration::ValueType _div_type_(Enumeration::ValueType other) override;
    Constant *_mod_(Value *other) override;
    Enumeration::ValueType _mod_type_(Enumeration::ValueType other) override;
    Constant *_eq_(Value *other) override;
    Enumeration::ValueType _eq_type_(Enumeration::ValueType other) override;
    Constant *_ne_(Value *other) override;
    Enumeration::ValueType _ne_type_(Enumeration::ValueType other) override;
    Constant *_lt_(Value *other) override;
    Enumeration::ValueType _lt_type_(Enumeration::ValueType other) override;
    Constant *_le_(Value *other) override;
    Enumeration::ValueType _le_type_(Enumeration::ValueType other) override;
    Constant *_gt_(Value *other) override;
    Enumeration::ValueType _gt_type_(Enumeration::ValueType other) override;
    Constant *_ge_(Value *other) override;
    Enumeration::ValueType _ge_type_(Enumeration::ValueType other) override;
    Constant *_pos_() override;
    Enumeration::ValueType _pos_type_() override;
    Constant *_neg_() override;
    Enumeration::ValueType _neg_type_() override;
    Constant *asInt32() override;
    Constant *asFloat32() override;
    Constant *asBoolean() override;
    Constant *asChar() override;
    bool isInt32() override;
    bool isConstant() override;
};
class Float32 : public Constant
{
    std::optional<float> value{};

  public:
    explicit Float32();
    std::string toIRString() override;
    void toMermaid() override;
    void toIR() override;
    [[nodiscard]] float getValue() const;
    Float32 *setValue(float _value);
    Constant *_add_(Value *other) override;
    Enumeration::ValueType _add_type_(Enumeration::ValueType other) override;
    Constant *_sub_(Value *other) override;
    Enumeration::ValueType _sub_type_(Enumeration::ValueType other) override;
    Constant *_mul_(Value *other) override;
    Enumeration::ValueType _mul_type_(Enumeration::ValueType other) override;
    Constant *_div_(Value *other) override;
    Enumeration::ValueType _div_type_(Enumeration::ValueType other) override;
    Constant *_eq_(Value *other) override;
    Enumeration::ValueType _eq_type_(Enumeration::ValueType other) override;
    Constant *_ne_(Value *other) override;
    Enumeration::ValueType _ne_type_(Enumeration::ValueType other) override;
    Constant *_lt_(Value *other) override;
    Enumeration::ValueType _lt_type_(Enumeration::ValueType other) override;
    Constant *_le_(Value *other) override;
    Enumeration::ValueType _le_type_(Enumeration::ValueType other) override;
    Constant *_gt_(Value *other) override;
    Enumeration::ValueType _gt_type_(Enumeration::ValueType other) override;
    Constant *_ge_(Value *other) override;
    Enumeration::ValueType _ge_type_(Enumeration::ValueType other) override;
    Constant *_pos_() override;
    Enumeration::ValueType _pos_type_() override;
    Constant *_neg_() override;
    Enumeration::ValueType _neg_type_() override;
    bool isFloat32() override;
    bool isConstant() override;
    Constant *asInt32() override;
    Constant *asFloat32() override;
    Constant *asBoolean() override;
};
class Boolean : public Constant
{
    std::optional<bool> value;

  public:
    explicit Boolean();
    void toMermaid() override;
    void toIR() override;
    std::string toIRString() override;
    bool isConstant() override;
    [[nodiscard]] bool getValue() const;
    Boolean *setValue(bool _value);
    Constant *_and_(Value *other) override;
    Enumeration::ValueType _and_type_(Enumeration::ValueType other) override;
    Constant *_or_(Value *other) override;
    Enumeration::ValueType _or_type_(Enumeration::ValueType other) override;
    Constant *_eq_(Value *other) override;
    Enumeration::ValueType _eq_type_(Enumeration::ValueType other) override;
    Constant *_ne_(Value *other) override;
    Enumeration::ValueType _ne_type_(Enumeration::ValueType other) override;
    Constant *_not_() override;
    Enumeration::ValueType _not_type_() override;
    bool isBoolean() override;
    Constant *asInt32() override;
    Constant *asBoolean() override;
};
class Pointer : public Constant
{
    void *value{};

  public:
    explicit Pointer();
    std::string toIRString() override;
    void toMermaid() override;
    void toIR() override;
    [[nodiscard]] void *getValue() const;
    Pointer *setValue(void *_value);
    Constant *_add_(Value *other) override;
    Enumeration::ValueType _add_type_(Enumeration::ValueType other) override;
    Constant *_sub_(Value *other) override;
    Enumeration::ValueType _sub_type_(Enumeration::ValueType other) override;
    Constant *_eq_(Value *other) override;
    Enumeration::ValueType _eq_type_(Enumeration::ValueType other) override;
    Constant *_ne_(Value *other) override;
    Enumeration::ValueType _ne_type_(Enumeration::ValueType other) override;
    Constant *_lt_(Value *other) override;
    Enumeration::ValueType _lt_type_(Enumeration::ValueType other) override;
    Constant *_le_(Value *other) override;
    Enumeration::ValueType _le_type_(Enumeration::ValueType other) override;
    Constant *_gt_(Value *other) override;
    Enumeration::ValueType _gt_type_(Enumeration::ValueType other) override;
    Constant *_ge_(Value *other) override;
    Enumeration::ValueType _ge_type_(Enumeration::ValueType other) override;
    bool isPointer() override;
    bool isConstant() override;
};
class Void : public Constant
{
  public:
    explicit Void();
    void toMermaid() override;
    void toIR() override;
    std::string toIRString() override;
    bool isVoid() override;
    bool isConstant() override;
};

class Char : public Constant
{
    std::optional<char> value{};

  public:
    explicit Char();
    std::string toIRString() override;
    void toMermaid() override;
    void toIR() override;
    [[nodiscard]] char getValue() const;
    Char *setValue(char _value);
    Constant *_add_(Value *other) override;
    Enumeration::ValueType _add_type_(Enumeration::ValueType other) override;
    Constant *_sub_(Value *other) override;
    Enumeration::ValueType _sub_type_(Enumeration::ValueType other) override;
    Constant *_eq_(Value *other) override;
    Enumeration::ValueType _eq_type_(Enumeration::ValueType other) override;
    Constant *_ne_(Value *other) override;
    Enumeration::ValueType _ne_type_(Enumeration::ValueType other) override;
    Constant *_lt_(Value *other) override;
    Enumeration::ValueType _lt_type_(Enumeration::ValueType other) override;
    Constant *_le_(Value *other) override;
    Enumeration::ValueType _le_type_(Enumeration::ValueType other) override;
    Constant *_gt_(Value *other) override;
    Enumeration::ValueType _gt_type_(Enumeration::ValueType other) override;
    Constant *_ge_(Value *other) override;
    Enumeration::ValueType _ge_type_(Enumeration::ValueType other) override;
    bool isChar() override;
    Constant *asChar() override;
    Constant *asInt32() override;
    bool isConstant() override;
};

class Mutable : public Value
{
  public:
    explicit Mutable(Enumeration::NodeClass _nodeClass, Enumeration::ValueType _valueType);
    Constant *_add_(Value *other) override;
    Enumeration::ValueType _add_type_(Enumeration::ValueType other) override;
    Constant *_sub_(Value *other) override;
    Enumeration::ValueType _sub_type_(Enumeration::ValueType other) override;
    Constant *_mul_(Value *other) override;
    Enumeration::ValueType _mul_type_(Enumeration::ValueType other) override;
    Constant *_div_(Value *other) override;
    Enumeration::ValueType _div_type_(Enumeration::ValueType other) override;
    Constant *_mod_(Value *other) override;
    Enumeration::ValueType _mod_type_(Enumeration::ValueType other) override;
    Constant *_and_(Value *other) override;
    Enumeration::ValueType _and_type_(Enumeration::ValueType other) override;
    Constant *_or_(Value *other) override;
    Enumeration::ValueType _or_type_(Enumeration::ValueType other) override;
    Constant *_eq_(Value *other) override;
    Enumeration::ValueType _eq_type_(Enumeration::ValueType other) override;
    Constant *_ne_(Value *other) override;
    Enumeration::ValueType _ne_type_(Enumeration::ValueType other) override;
    Constant *_lt_(Value *other) override;
    Enumeration::ValueType _lt_type_(Enumeration::ValueType other) override;
    Constant *_le_(Value *other) override;
    Enumeration::ValueType _le_type_(Enumeration::ValueType other) override;
    Constant *_gt_(Value *other) override;
    Enumeration::ValueType _gt_type_(Enumeration::ValueType other) override;
    Constant *_ge_(Value *other) override;
    Enumeration::ValueType _ge_type_(Enumeration::ValueType other) override;
    Constant *_pos_() override;
    Enumeration::ValueType _pos_type_() override;
    Constant *_neg_() override;
    Enumeration::ValueType _neg_type_() override;
    Constant *_not_() override;
    Enumeration::ValueType _not_type_() override;
    Constant *asInt32() override;
    Constant *asFloat32() override;
    Constant *asBoolean() override;
    Constant *asPointer() override;
    Constant *asChar() override;
    bool isConstant() override = 0;
    Constant *constantify() override = 0;
    void toMermaid() override = 0;
};
class Binary : public Mutable
{
    Value *left{};
    Value *right{};
    Enumeration::Operator op;

  public:
    [[nodiscard]] Value *getLeft() const;
    [[nodiscard]] Value *getRight() const;
    [[nodiscard]] Enumeration::Operator getOp() const;
    Binary *setLeft(Value *_left);
    Binary *setRight(Value *_right);
    Binary *setOp(Enumeration::Operator _op);
    void toMermaid() override;
    void toIR() override;
    bool isConstant() override;
    Constant *constantify() override;
    explicit Binary();
    Enumeration::ValueType getValueType() override;
};
class Unary : public Mutable
{
    Value *expr{};
    Enumeration::Operator op;

  public:
    void toMermaid() override;
    void toIR() override;
    bool isConstant() override;
    Constant *constantify() override;
    explicit Unary();
    [[nodiscard]] Value *getExpr() const;
    [[nodiscard]] Enumeration::Operator getOp() const;
    Unary *setExpr(Value *_expr);
    Unary *setOp(Enumeration::Operator _op);
    Enumeration::ValueType getValueType() override;
};
class Variable : public Mutable
{
    std::string name;
    Enumeration::ValueType valueType;

  public:
    Variable *setName(const std::string &_name);
    Variable *setValueType(Enumeration::ValueType _type);
    [[nodiscard]] const std::string &getName() const;
    void toMermaid() override;
    void toIR() override;
    bool isConstant() override;
    Constant *constantify() override;
    explicit Variable();
    Enumeration::ValueType getValueType() override;
};
class FunctionCall : public Mutable
{
    std::string name;
    std::vector<Value *> arguments;

  public:
    FunctionCall *setName(const std::string &_name);
    [[nodiscard]] const std::string &getName() const;
    FunctionCall *setArguments(const std::vector<Value *> &_arguments);
    [[nodiscard]] const std::vector<Value *> &getArguments() const;
    void toMermaid() override;
    void toIR() override;
    bool isConstant() override;
    Constant *constantify() override;
    explicit FunctionCall();
    Enumeration::ValueType getValueType() override;
};
} // namespace SED::AST
#endif // SED_VALUE_HPP
