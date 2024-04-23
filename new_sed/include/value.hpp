

#ifndef SED_VALUE_HPP
#define SED_VALUE_HPP
#include "ast.hpp"
#include <map>
#include <optional>
#include <string>
namespace SED::AST
{
class Node;
enum class Operator
{
    UNKNOWN,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    AND,
    OR,
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE,
    POS,
    NEG,
    NOT
};
extern std::map<Operator, std::string> OperatorEnumMap;
extern std::string OperatorEnumMapToString(Operator op);
enum class ValueType
{
    INT_32,
    FLOAT_32,
    BOOLEAN,
    POINTER,
    CHAR,
    VOID,
};
extern std::map<ValueType, std::string> ValueTypeEnumMap;
extern std::string ValueTypeEnumMapToString(ValueType valueType);
class Constant;
class Value : public Node
{
  protected:
  public:
    explicit Value(NodeClass _nodeClass);
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
    virtual ValueType _add_type_(ValueType other) = 0;
    virtual ValueType _sub_type_(ValueType other) = 0;
    virtual ValueType _mul_type_(ValueType other) = 0;
    virtual ValueType _div_type_(ValueType other) = 0;
    virtual ValueType _mod_type_(ValueType other) = 0;
    virtual ValueType _and_type_(ValueType other) = 0;
    virtual ValueType _or_type_(ValueType other) = 0;
    virtual ValueType _eq_type_(ValueType other) = 0;
    virtual ValueType _ne_type_(ValueType other) = 0;
    virtual ValueType _lt_type_(ValueType other) = 0;
    virtual ValueType _le_type_(ValueType other) = 0;
    virtual ValueType _gt_type_(ValueType other) = 0;
    virtual ValueType _ge_type_(ValueType other) = 0;
    virtual ValueType _pos_type_() = 0;
    virtual ValueType _neg_type_() = 0;
    virtual ValueType _not_type_() = 0;
    virtual Constant *asInt32() = 0;
    virtual Constant *asFloat32() = 0;
    virtual Constant *asBoolean() = 0;
    virtual Constant *asPointer() = 0;
    virtual ValueType getValueType() = 0;
    virtual bool isDirect() = 0;
    virtual Constant *directify() = 0;
    void analyze() override;
};
class Constant : public Value
{
  public:
    explicit Constant(NodeClass _NodeClass);
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
    ValueType _add_type_(ValueType other) override;
    ValueType _sub_type_(ValueType other) override;
    ValueType _mul_type_(ValueType other) override;
    ValueType _div_type_(ValueType other) override;
    ValueType _mod_type_(ValueType other) override;
    ValueType _and_type_(ValueType other) override;
    ValueType _or_type_(ValueType other) override;
    ValueType _eq_type_(ValueType other) override;
    ValueType _ne_type_(ValueType other) override;
    ValueType _lt_type_(ValueType other) override;
    ValueType _le_type_(ValueType other) override;
    ValueType _gt_type_(ValueType other) override;
    ValueType _ge_type_(ValueType other) override;
    ValueType _pos_type_() override;
    ValueType _neg_type_() override;
    ValueType _not_type_() override;
    bool isDirect() override;
    Constant *directify() override;
    virtual bool isInt32();
    Constant *asInt32() override;
    Constant *asFloat32() override;
    Constant *asBoolean() override;
    Constant *asPointer() override;
    virtual bool isFloat32();
    virtual bool isBoolean();
    virtual bool isPointer();
    virtual bool isVoid();
    virtual std::string toIRString() = 0;
    static Constant *createValue(ValueType type);
};
class Int32 : public Constant
{
    std::optional<int32_t> value{};

  public:
    explicit Int32();
    std::string toIRString() override;
    void toMermaid() override;
    void toIR() override;
    ValueType getValueType() override;
    [[nodiscard]] int32_t getValue() const;
    Int32 *setValue(int32_t _value);
    Constant *_add_(Value *other) override;
    ValueType _add_type_(ValueType other) override;
    Constant *_sub_(Value *other) override;
    ValueType _sub_type_(ValueType other) override;
    Constant *_mul_(Value *other) override;
    ValueType _mul_type_(ValueType other) override;
    Constant *_div_(Value *other) override;
    ValueType _div_type_(ValueType other) override;
    Constant *_mod_(Value *other) override;
    ValueType _mod_type_(ValueType other) override;
    Constant *_eq_(Value *other) override;
    ValueType _eq_type_(ValueType other) override;
    Constant *_ne_(Value *other) override;
    ValueType _ne_type_(ValueType other) override;
    Constant *_lt_(Value *other) override;
    ValueType _lt_type_(ValueType other) override;
    Constant *_le_(Value *other) override;
    ValueType _le_type_(ValueType other) override;
    Constant *_gt_(Value *other) override;
    ValueType _gt_type_(ValueType other) override;
    Constant *_ge_(Value *other) override;
    ValueType _ge_type_(ValueType other) override;
    Constant *_pos_() override;
    ValueType _pos_type_() override;
    Constant *_neg_() override;
    ValueType _neg_type_() override;
    Constant *asInt32() override;
    Constant *asFloat32() override;
    Constant *asBoolean() override;
    bool isInt32() override;
    bool isDirect() override;
};
class Float32 : public Constant
{
    std::optional<float> value{};

  public:
    explicit Float32();
    std::string toIRString() override;
    void toMermaid() override;
    void toIR() override;
    ValueType getValueType() override;
    [[nodiscard]] float getValue() const;
    Float32 *setValue(float _value);
    Constant *_add_(Value *other) override;
    ValueType _add_type_(ValueType other) override;
    Constant *_sub_(Value *other) override;
    ValueType _sub_type_(ValueType other) override;
    Constant *_mul_(Value *other) override;
    ValueType _mul_type_(ValueType other) override;
    Constant *_div_(Value *other) override;
    ValueType _div_type_(ValueType other) override;
    Constant *_eq_(Value *other) override;
    ValueType _eq_type_(ValueType other) override;
    Constant *_ne_(Value *other) override;
    ValueType _ne_type_(ValueType other) override;
    Constant *_lt_(Value *other) override;
    ValueType _lt_type_(ValueType other) override;
    Constant *_le_(Value *other) override;
    ValueType _le_type_(ValueType other) override;
    Constant *_gt_(Value *other) override;
    ValueType _gt_type_(ValueType other) override;
    Constant *_ge_(Value *other) override;
    ValueType _ge_type_(ValueType other) override;
    Constant *_pos_() override;
    ValueType _pos_type_() override;
    Constant *_neg_() override;
    ValueType _neg_type_() override;
    bool isFloat32() override;
    bool isDirect() override;
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
    bool isDirect() override;
    ValueType getValueType() override;
    [[nodiscard]] bool getValue() const;
    Boolean *setValue(bool _value);
    Constant *_and_(Value *other) override;
    ValueType _and_type_(ValueType other) override;
    Constant *_or_(Value *other) override;
    ValueType _or_type_(ValueType other) override;
    Constant *_eq_(Value *other) override;
    ValueType _eq_type_(ValueType other) override;
    Constant *_ne_(Value *other) override;
    ValueType _ne_type_(ValueType other) override;
    Constant *_not_() override;
    ValueType _not_type_() override;
    bool isBoolean() override;
    Constant *asInt32() override;
    Constant *asFloat32() override;
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
    ValueType getValueType() override;
    [[nodiscard]] void *getValue() const;
    Pointer *setValue(void *_value);
    Constant *_add_(Value *other) override;
    ValueType _add_type_(ValueType other) override;
    Constant *_sub_(Value *other) override;
    ValueType _sub_type_(ValueType other) override;
    Constant *_eq_(Value *other) override;
    ValueType _eq_type_(ValueType other) override;
    Constant *_ne_(Value *other) override;
    ValueType _ne_type_(ValueType other) override;
    Constant *_lt_(Value *other) override;
    ValueType _lt_type_(ValueType other) override;
    Constant *_le_(Value *other) override;
    ValueType _le_type_(ValueType other) override;
    Constant *_gt_(Value *other) override;
    ValueType _gt_type_(ValueType other) override;
    Constant *_ge_(Value *other) override;
    ValueType _ge_type_(ValueType other) override;
    bool isPointer() override;
};
class Void : public Constant
{
  public:
    explicit Void();
    void toMermaid() override;
    void toIR() override;
    std::string toIRString() override;
    ValueType getValueType() override;
    bool isVoid() override;
};
class Mutable : public Value
{
  public:
    explicit Mutable(NodeClass _NodeClass);
    Constant *_add_(Value *other) override;
    ValueType _add_type_(ValueType other) override;
    Constant *_sub_(Value *other) override;
    ValueType _sub_type_(ValueType other) override;
    Constant *_mul_(Value *other) override;
    ValueType _mul_type_(ValueType other) override;
    Constant *_div_(Value *other) override;
    ValueType _div_type_(ValueType other) override;
    Constant *_mod_(Value *other) override;
    ValueType _mod_type_(ValueType other) override;
    Constant *_and_(Value *other) override;
    ValueType _and_type_(ValueType other) override;
    Constant *_or_(Value *other) override;
    ValueType _or_type_(ValueType other) override;
    Constant *_eq_(Value *other) override;
    ValueType _eq_type_(ValueType other) override;
    Constant *_ne_(Value *other) override;
    ValueType _ne_type_(ValueType other) override;
    Constant *_lt_(Value *other) override;
    ValueType _lt_type_(ValueType other) override;
    Constant *_le_(Value *other) override;
    ValueType _le_type_(ValueType other) override;
    Constant *_gt_(Value *other) override;
    ValueType _gt_type_(ValueType other) override;
    Constant *_ge_(Value *other) override;
    ValueType _ge_type_(ValueType other) override;
    Constant *_pos_() override;
    ValueType _pos_type_() override;
    Constant *_neg_() override;
    ValueType _neg_type_() override;
    Constant *_not_() override;
    ValueType _not_type_() override;
    Constant *asInt32() override;
    Constant *asFloat32() override;
    Constant *asBoolean() override;
    Constant *asPointer() override;
    bool isDirect() override = 0;
    Constant *directify() override = 0;
    ValueType getValueType() override = 0;
    void toMermaid() override = 0;
};
class Binary : public Mutable
{
    Value *left{};
    Value *right{};
    Operator op = Operator::UNKNOWN;

  public:
    Binary *setLeft(Value *_left);
    Binary *setRight(Value *_right);
    Binary *setOp(Operator _op);
    [[nodiscard]] Value *getLeft() const;
    [[nodiscard]] Value *getRight() const;
    [[nodiscard]] Operator getOp() const;
    void toMermaid() override;
    void toIR() override;
    bool isDirect() override;
    Constant *directify() override;
    explicit Binary();
    ValueType getValueType() override;
};
class Unary : public Mutable
{
    Value *expr{};
    Operator op = Operator::UNKNOWN;

  public:
    Unary *setExpr(Value *_expr);
    [[nodiscard]] Value *getExpr() const;
    Unary *setOp(Operator _op);
    [[nodiscard]] Operator getOp() const;
    void toMermaid() override;
    void toIR() override;
    bool isDirect() override;
    Constant *directify() override;
    explicit Unary();
    ValueType getValueType() override;
};
class Variable : public Mutable
{
    std::string name;
    ValueType valueType = ValueType::VOID;

  public:
    Variable *setName(const std::string &_name);
    Variable *setValueType(ValueType _type);
    [[nodiscard]] ValueType getValueType() const;
    [[nodiscard]] const std::string &getName() const;
    void toMermaid() override;
    void toIR() override;
    bool isDirect() override;
    Constant *directify() override;
    explicit Variable();
    virtual ValueType getValueType() override;
};
class FunctionCall : public Mutable
{
    std::string name;

  public:
    FunctionCall *setName(const std::string &_name);
    [[nodiscard]] const std::string &getName() const;
    void toMermaid() override;
    void toIR() override;
    bool isDirect() override;
    Constant *directify() override;
    explicit FunctionCall();
    ValueType getValueType() override;
};
} // namespace SED::AST
#endif // SED_VALUE_HPP
