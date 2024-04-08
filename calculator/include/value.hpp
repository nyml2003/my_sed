#ifndef SED_VALUE_HPP
#define SED_VALUE_HPP

#include <cstdint>
#include "ast.hpp"

namespace SED::AST
{
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

    enum class ValueType
    {
        INT_32,
        FLOAT_32,
        BOOLEAN,
        POINTER,
        VOID
    };

    class DirectRightValue;

    class RightValue : public Node
    {
    public:
        explicit RightValue(NodeClass _nodeClass);

        virtual DirectRightValue *_add_(RightValue *other) = 0;

        virtual DirectRightValue *_sub_(RightValue *other) = 0;

        virtual DirectRightValue *_mul_(RightValue *other) = 0;

        virtual DirectRightValue *_div_(RightValue *other) = 0;

        virtual DirectRightValue *_mod_(RightValue *other) = 0;

        virtual DirectRightValue *_and_(RightValue *other) = 0;

        virtual DirectRightValue *_or_(RightValue *other) = 0;

        virtual DirectRightValue *_eq_(RightValue *other) = 0;

        virtual DirectRightValue *_ne_(RightValue *other) = 0;

        virtual DirectRightValue *_lt_(RightValue *other) = 0;

        virtual DirectRightValue *_le_(RightValue *other) = 0;

        virtual DirectRightValue *_gt_(RightValue *other) = 0;

        virtual DirectRightValue *_ge_(RightValue *other) = 0;

        virtual DirectRightValue *_pos_() = 0;

        virtual DirectRightValue *_neg_() = 0;

        virtual DirectRightValue *_not_() = 0;

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

        virtual bool isSameValueType(RightValue *other);

        virtual void interpret() override = 0;

        virtual ValueType
        getValueType() = 0;

        virtual bool isDirect() = 0;

        virtual DirectRightValue *directify() = 0;
    };

    class DirectRightValue : public RightValue
    {
        static void
        throwTypeMismatchError(const std::string &operation, NodeClass left, NodeClass right);

        static void
        throwTypeMismatchError(const std::string &operation, NodeClass expr);

        static void throwTypeMismatchError(const std::string &operation, ValueType left, ValueType right);

        static void throwTypeMismatchError(const std::string &operation, ValueType expr);

    public:
        explicit DirectRightValue(NodeClass _NodeClass);

        DirectRightValue *_add_(RightValue *other) override;

        DirectRightValue *_sub_(RightValue *other) override;

        DirectRightValue *_mul_(RightValue *other) override;

        DirectRightValue *_div_(RightValue *other) override;

        DirectRightValue *_mod_(RightValue *other) override;

        DirectRightValue *_and_(RightValue *other) override;

        DirectRightValue *_or_(RightValue *other) override;

        DirectRightValue *_eq_(RightValue *other) override;

        DirectRightValue *_ne_(RightValue *other) override;

        DirectRightValue *_lt_(RightValue *other) override;

        DirectRightValue *_le_(RightValue *other) override;

        DirectRightValue *_gt_(RightValue *other) override;

        DirectRightValue *_ge_(RightValue *other) override;

        DirectRightValue *_pos_() override;

        DirectRightValue *_neg_() override;

        DirectRightValue *_not_() override;

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

        DirectRightValue *directify() override;

        virtual bool isInt32();

        virtual bool isFloat32();

        virtual bool isBoolean();

        virtual bool isPointer();

        virtual bool isVoid();
    };

    class Int32 : public DirectRightValue
    {
        int32_t value{};

    public:
        explicit Int32();

        void toMermaid() override;

        void interpret() override;

        ValueType getValueType() override;

        [[nodiscard]] int32_t getValue() const;

        Int32 *setValue(int32_t _value);

        DirectRightValue *_add_(RightValue *other) override;

        ValueType _add_type_(ValueType other) override;

        DirectRightValue *_sub_(RightValue *other) override;

        ValueType _sub_type_(ValueType other) override;

        DirectRightValue *_mul_(RightValue *other) override;

        ValueType _mul_type_(ValueType other) override;

        DirectRightValue *_div_(RightValue *other) override;

        ValueType _div_type_(ValueType other) override;

        DirectRightValue *_mod_(RightValue *other) override;

        ValueType _mod_type_(ValueType other) override;

        DirectRightValue *_eq_(RightValue *other) override;

        ValueType _eq_type_(ValueType other) override;

        DirectRightValue *_ne_(RightValue *other) override;

        ValueType _ne_type_(ValueType other) override;

        DirectRightValue *_lt_(RightValue *other) override;

        ValueType _lt_type_(ValueType other) override;

        DirectRightValue *_le_(RightValue *other) override;

        ValueType _le_type_(ValueType other) override;

        DirectRightValue *_gt_(RightValue *other) override;

        ValueType _gt_type_(ValueType other) override;

        DirectRightValue *_ge_(RightValue *other) override;

        ValueType _ge_type_(ValueType other) override;

        DirectRightValue *_pos_() override;

        ValueType _pos_type_() override;

        DirectRightValue *_neg_() override;

        ValueType _neg_type_() override;

        bool isInt32() override;
    };

    class Float32 : public DirectRightValue
    {
        float value{};

    public:
        explicit Float32();

        void toMermaid() override;

        void interpret() override;

        ValueType getValueType() override;

        [[nodiscard]] float getValue() const;

        Float32 *setValue(float _value);

        DirectRightValue *_add_(RightValue *other) override;

        ValueType _add_type_(ValueType other) override;

        DirectRightValue *_sub_(RightValue *other) override;

        ValueType _sub_type_(ValueType other) override;

        DirectRightValue *_mul_(RightValue *other) override;

        ValueType _mul_type_(ValueType other) override;

        DirectRightValue *_div_(RightValue *other) override;

        ValueType _div_type_(ValueType other) override;

        DirectRightValue *_eq_(RightValue *other) override;

        ValueType _eq_type_(ValueType other) override;

        DirectRightValue *_ne_(RightValue *other) override;

        ValueType _ne_type_(ValueType other) override;

        DirectRightValue *_lt_(RightValue *other) override;

        ValueType _lt_type_(ValueType other) override;

        DirectRightValue *_le_(RightValue *other) override;

        ValueType _le_type_(ValueType other) override;

        DirectRightValue *_gt_(RightValue *other) override;

        ValueType _gt_type_(ValueType other) override;

        DirectRightValue *_ge_(RightValue *other) override;

        ValueType _ge_type_(ValueType other) override;

        DirectRightValue *_pos_() override;

        ValueType _pos_type_() override;

        DirectRightValue *_neg_() override;

        ValueType _neg_type_() override;

        bool isFloat32() override;
    };

    class Boolean : public DirectRightValue
    {
        bool value{};

    public:
        explicit Boolean();

        void toMermaid() override;

        void interpret() override;

        ValueType getValueType() override;

        [[nodiscard]] bool getValue() const;

        Boolean *setValue(bool _value);

        DirectRightValue *_and_(RightValue *other) override;

        ValueType _and_type_(ValueType other) override;

        DirectRightValue *_or_(RightValue *other) override;

        ValueType _or_type_(ValueType other) override;

        DirectRightValue *_eq_(RightValue *other) override;

        ValueType _eq_type_(ValueType other) override;

        DirectRightValue *_ne_(RightValue *other) override;

        ValueType _ne_type_(ValueType other) override;

        DirectRightValue *_not_() override;

        ValueType _not_type_() override;

        bool isBoolean() override;
    };

    class Pointer : public DirectRightValue
    {
        void *value{};

    public:
        explicit Pointer();

        void interpret() override;

        void toMermaid() override;

        ValueType getValueType() override;

        [[nodiscard]] void *getValue() const;

        Pointer *setValue(void *_value);

        DirectRightValue *_add_(RightValue *other) override;

        ValueType _add_type_(ValueType other) override;

        DirectRightValue *_sub_(RightValue *other) override;

        ValueType _sub_type_(ValueType other) override;

        DirectRightValue *_eq_(RightValue *other) override;

        ValueType _eq_type_(ValueType other) override;

        DirectRightValue *_ne_(RightValue *other) override;

        ValueType _ne_type_(ValueType other) override;

        DirectRightValue *_lt_(RightValue *other) override;

        ValueType _lt_type_(ValueType other) override;

        DirectRightValue *_le_(RightValue *other) override;

        ValueType _le_type_(ValueType other) override;

        DirectRightValue *_gt_(RightValue *other) override;

        ValueType _gt_type_(ValueType other) override;

        DirectRightValue *_ge_(RightValue *other) override;

        ValueType _ge_type_(ValueType other) override;

        bool isPointer() override;
    };

    class Void : public DirectRightValue
    {
    public:
        explicit Void();

        void toMermaid() override;

        void interpret() override;

        ValueType getValueType() override;

        bool isVoid() override;
    };

    class IndirectRightValue : public RightValue
    {
    public:
        explicit IndirectRightValue(NodeClass _NodeClass);

        DirectRightValue *_add_(RightValue *other) override;

        ValueType _add_type_(ValueType other) override;

        DirectRightValue *_sub_(RightValue *other) override;

        ValueType _sub_type_(ValueType other) override;

        DirectRightValue *_mul_(RightValue *other) override;

        ValueType _mul_type_(ValueType other) override;

        DirectRightValue *_div_(RightValue *other) override;

        ValueType _div_type_(ValueType other) override;

        DirectRightValue *_mod_(RightValue *other) override;

        ValueType _mod_type_(ValueType other) override;

        DirectRightValue *_and_(RightValue *other) override;

        ValueType _and_type_(ValueType other) override;

        DirectRightValue *_or_(RightValue *other) override;

        ValueType _or_type_(ValueType other) override;

        DirectRightValue *_eq_(RightValue *other) override;

        ValueType _eq_type_(ValueType other) override;

        DirectRightValue *_ne_(RightValue *other) override;

        ValueType _ne_type_(ValueType other) override;

        DirectRightValue *_lt_(RightValue *other) override;

        ValueType _lt_type_(ValueType other) override;

        DirectRightValue *_le_(RightValue *other) override;

        ValueType _le_type_(ValueType other) override;

        DirectRightValue *_gt_(RightValue *other) override;

        ValueType _gt_type_(ValueType other) override;

        DirectRightValue *_ge_(RightValue *other) override;

        ValueType _ge_type_(ValueType other) override;

        DirectRightValue *_pos_() override;

        ValueType _pos_type_() override;

        DirectRightValue *_neg_() override;

        ValueType _neg_type_() override;

        DirectRightValue *_not_() override;

        ValueType _not_type_() override;

        bool isDirect() override = 0;

        DirectRightValue *directify() override = 0;

        ValueType getValueType() override = 0;

        void toMermaid() override = 0;
    };

    class Binary : public IndirectRightValue
    {
        RightValue *left{};
        RightValue *right{};
        Operator op = Operator::UNKNOWN;

    public:
        Binary *setLeft(RightValue *_left);

        Binary *setRight(RightValue *_right);

        Binary *setOp(Operator _op);

        void interpret() override;

        [[nodiscard]] RightValue *getLeft() const;

        [[nodiscard]] RightValue *getRight() const;

        [[nodiscard]] Operator getOp() const;

        void toMermaid() override;

        bool isDirect() override;

        DirectRightValue *directify() override;

        explicit Binary();

        ValueType getValueType() override;
    };

    class Unary : public IndirectRightValue
    {
        RightValue *expr{};
        Operator op = Operator::UNKNOWN;

    public:
        Unary *setExpr(RightValue *_expr);

        [[nodiscard]] RightValue *getExpr() const;

        Unary *setOp(Operator _op);

        void interpret() override;

        [[nodiscard]] Operator getOp() const;

        void toMermaid() override;

        bool isDirect() override;

        DirectRightValue *directify() override;

        explicit Unary();

        ValueType getValueType() override;
    };

    class Variable : public IndirectRightValue
    {
        std::string name;
        ValueType valueType = ValueType::VOID;

    public:
        Variable *setName(const std::string &_name);

        Variable *setValueType(ValueType _type);

        void interpret() override;

        [[nodiscard]] ValueType getValueType() const;

        [[nodiscard]] const std::string &getName() const;

        void toMermaid() override;

        bool isDirect() override;

        DirectRightValue *directify() override;

        explicit Variable();

        virtual ValueType getValueType() override;
    };

    class DirectRightValueInitializer
    {
        static std::map<ValueType, DirectRightValue *> values;

    public:
        static DirectRightValue *get(ValueType type);
    };

}

#endif // SED_VALUE_HPP
