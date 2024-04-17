#include <stdexcept>
#include "value.hpp"
#include "context.hpp"
#include <iostream>
namespace SED::AST
{
    

    /*RightValue*/

    std::string ValueTypeEnumMapToString(ValueType valueType){
        return ValueTypeEnumMap[valueType];
    }

    std::map<ValueType, std::string> ValueTypeEnumMap = {
        {ValueType::INT_32, "Int32"},
        {ValueType::FLOAT_32, "Float32"},
        {ValueType::BOOLEAN, "Boolean"},
        {ValueType::POINTER, "Pointer"},
        {ValueType::VOID, "Void"}};

    std::string OperatorEnumMapToString(Operator op)
    {
        return OperatorEnumMap[op];
    }

    std::map <Operator, std::string> OperatorEnumMap = {
        {Operator::ADD, "+"},
        {Operator::SUB, "-"},
        {Operator::MUL, "*"},
        {Operator::DIV, "/"},
        {Operator::MOD, "%"},
        {Operator::AND, "&&"},
        {Operator::OR, "||"},
        {Operator::EQ, "=="},
        {Operator::NE, "!="},
        {Operator::LT, "<"},
        {Operator::LE, "<="},
        {Operator::GT, ">"},
        {Operator::GE, ">="},
        {Operator::POS, "+"},
        {Operator::NEG, "-"},
        {Operator::NOT, "!"}};

    RightValue::RightValue(AST::NodeClass _NodeClass) : Node(_NodeClass)
    {
    }

    bool RightValue::isSameValueType(RightValue *other)
    {
        return getNodeClass() == other->getNodeClass();
    }

    /*DirectRightValue*/


    bool DirectRightValue::isDirect()
    {
        return true;
    }

    DirectRightValue *DirectRightValue::directify()
    {
        return this;
    }

    DirectRightValue::DirectRightValue(AST::NodeClass _NodeClass) : RightValue(_NodeClass) {}

    DirectRightValue *DirectRightValue::_add_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::ADD, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_sub_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::SUB, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_mul_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::MUL, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_div_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::DIV, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_mod_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::MOD, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_and_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::AND, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_or_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::OR, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_eq_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::EQ, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_ne_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::NE, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_lt_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::LT, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_le_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::LE, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_gt_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::GT, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_ge_(RightValue *other)
    {
        Error::InvalidOperationError(getValueType(), Operator::GE, other->getValueType()).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_pos_()
    {
        Error::InvalidOperationError(getValueType(), Operator::POS).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_neg_()
    {
        Error::InvalidOperationError(getValueType(), Operator::NEG).error();
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_not_()
    {
        Error::InvalidOperationError(getValueType(), Operator::NOT).error();
        return nullptr;
    }

    ValueType DirectRightValue::_add_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::ADD, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_sub_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::SUB, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_mul_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::MUL, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_div_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::DIV, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_mod_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::MOD, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_and_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::AND, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_or_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::OR, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_eq_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::EQ, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_ne_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::NE, other).error();
        return ValueType::VOID;
    }
    ValueType DirectRightValue::_lt_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::LT, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_le_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::LE, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_gt_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::GT, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_ge_type_(ValueType other)
    {
        Error::InvalidOperationError(getValueType(), Operator::GE, other).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_pos_type_()
    {
        Error::InvalidOperationError(getValueType(), Operator::POS).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_neg_type_()
    {
        Error::InvalidOperationError(getValueType(), Operator::NEG).error();
        return ValueType::VOID;
    }

    ValueType DirectRightValue::_not_type_()
    {
        Error::InvalidOperationError(getValueType(), Operator::NOT).error();
        return ValueType::VOID;
    }

    bool DirectRightValue::isInt32()
    {
        return false;
    }

    bool DirectRightValue::isFloat32()
    {
        return false;
    }

    bool DirectRightValue::isBoolean()
    {
        return false;
    }

    bool DirectRightValue::isPointer()
    {
        return false;
    }

    bool DirectRightValue::isVoid()
    {
        return false;
    }

    DirectRightValue *DirectRightValue::asBoolean()
    {
        throw std::runtime_error("Invalid cast to boolean");
    }

    DirectRightValue *DirectRightValue::asInt32()
    {
        throw std::runtime_error("Invalid cast to int32");
    }

    DirectRightValue *DirectRightValue::asFloat32()
    {
        throw std::runtime_error("Invalid cast to float32");
    }

    DirectRightValue *DirectRightValue::asPointer()
    {
        throw std::runtime_error("Invalid cast to pointer");
    }

    /*Int32*/

    Int32::Int32() : DirectRightValue(NodeClass::INT_32) {}

    bool Int32::isDirect()
    {
        if (value.has_value())
        {
            return true;
        }
        return false;
    }

    DirectRightValue *Int32::asInt32()
    {
        return this;
    }

    DirectRightValue *Int32::asFloat32()
    {
        if (value.has_value())
        {
            return (new Float32())->setValue(value.value());
        }
        else{
            return new Float32();
        }
    }

    DirectRightValue *Int32::asBoolean()
    {
        if (value.has_value())
        {
            return (new Boolean())->setValue(value.value() != 0);
        }
        else{
            return new Boolean();
        }
    }


    int32_t Int32::getValue() const
    {
        return value.has_value() ? value.value() : 0;
    }

    void Int32::toMermaid()
    {
        size_t int32_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        if (value.has_value())
        {
            putLabel(std::to_string(value.value()));
        }
        else
        {
            putLabel("null");
        }
        putEdge(int32_id, value_id, "value");
        count();
    }

    void Int32::toIR()
    {
        nextRegister();
        if (value.has_value()){
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue(std::to_string(value.value())));
        }else{
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("null"));
        }
    }

    Int32 *Int32::setValue(int32_t _value)
    {
        this->value = _value;
        return this;
    }

    bool Int32::isInt32()
    {
        return true;
    }

    ValueType Int32::getValueType()
    {
        return ValueType::INT_32;
    }

    DirectRightValue *Int32::_add_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Int32())->setValue(value.value() + ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_add_(other);
    }

    ValueType Int32::_add_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::INT_32;
        }
        return DirectRightValue::_add_type_(other);
    }

    DirectRightValue *Int32::_sub_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Int32())->setValue(value.value() - ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_sub_(other);
    }

    ValueType Int32::_sub_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::INT_32;
        }
        return DirectRightValue::_sub_type_(other);
    }

    DirectRightValue *Int32::_mul_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Int32())->setValue(value.value() * ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_mul_(other);
    }

    ValueType Int32::_mul_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::INT_32;
        }
        return DirectRightValue::_mul_type_(other);
    }

    DirectRightValue *Int32::_div_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                if (((Int32 *)otherDirect)->getValue() == 0)
                {
                    Error::DivisionByZeroError().error();
                    return nullptr;
                }
                return (new Int32())->setValue(value.value() / ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_div_(other);
    }

    ValueType Int32::_div_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::INT_32;
        }
        return DirectRightValue::_div_type_(other);
    }

    DirectRightValue *Int32::_mod_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                if (((Int32 *)otherDirect)->getValue() == 0)
                {
                    Error::DivisionByZeroError().error();
                    return nullptr;
                }
                return (new Int32())->setValue(value.value() % ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_mod_(other);
    }

    ValueType Int32::_mod_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::INT_32;
        }
        return DirectRightValue::_mod_type_(other);
    }

    DirectRightValue *Int32::_eq_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Boolean())->setValue(value.value() == ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    ValueType Int32::_eq_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_eq_type_(other);
    }

    DirectRightValue *Int32::_ne_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Boolean())->setValue(value.value() != ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    ValueType Int32::_ne_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_ne_type_(other);
    }

    DirectRightValue *Int32::_lt_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Boolean())->setValue(value.value() < ((Int32 *)other)->getValue());
            }
        }
        return DirectRightValue::_lt_(other);
    }

    ValueType Int32::_lt_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_lt_type_(other);
    }

    DirectRightValue *Int32::_le_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Boolean())->setValue(value.value() <= ((Int32 *)other)->getValue());
            }
        }
        return DirectRightValue::_le_(other);
    }

    ValueType Int32::_le_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_le_type_(other);
    }

    DirectRightValue *Int32::_gt_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Boolean())->setValue(value.value() > ((Int32 *)other)->getValue());
            }
        }
        return DirectRightValue::_gt_(other);
    }

    ValueType Int32::_gt_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_gt_type_(other);
    }

    DirectRightValue *Int32::_ge_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Boolean())->setValue(value.value() >= ((Int32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ge_(other);
    }

    ValueType Int32::_ge_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_ge_type_(other);
    }

    DirectRightValue *Int32::_pos_()
    {
        return (new Int32())->setValue(value.value());
    }

    ValueType Int32::_pos_type_()
    {
        return ValueType::INT_32;
    }

    DirectRightValue *Int32::_neg_()
    {
        return (new Int32())->setValue(-value.value());
    }

    ValueType Int32::_neg_type_()
    {
        return ValueType::INT_32;
    }

    /*Float32*/

    Float32::Float32() : DirectRightValue(NodeClass::FLOAT_32) {}

    bool Float32::isDirect()
    {
        if (value.has_value())
        {
            return true;
        }
        return false;
    }

    DirectRightValue *Float32::asFloat32()
    {
        return this;
    }

    DirectRightValue *Float32::asInt32()
    {
        if (value.has_value())
        {
            return (new Int32())->setValue(value.value());
        }
        else{
            return new Int32();
        }
    }

    DirectRightValue *Float32::asBoolean()
    {
        if (value.has_value())
        {
            return (new Boolean())->setValue(value.value() != 0);
        }
        else{
            return new Boolean();
        }
    }
    

    void Float32::toMermaid()
    {
        size_t float32_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        if (value.has_value())
        {
            putLabel(std::to_string(value.value()));
        }
        else
        {
            putLabel("null");
        }
        putEdge(float32_id, value_id, "value");
        count();
    }

    void Float32::toIR()
    {
        nextRegister();
        if (value.has_value()){
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue(std::to_string(value.value())));
        }else{
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("null"));
        }
    }

    Float32 *Float32::setValue(float _value)
    {
        this->value = _value;
        return this;
    }

    bool Float32::isFloat32()
    {
        return true;
    }

    DirectRightValue *Float32::_add_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Float32())->setValue(value.value() + ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_add_(other);
    }
    ValueType Float32::_add_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::FLOAT_32;
        }
        return DirectRightValue::_add_type_(other);
    }
    DirectRightValue *Float32::_sub_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Float32())->setValue(value.value() - ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_sub_(other);
    }

    ValueType Float32::_sub_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::FLOAT_32;
        }
        return DirectRightValue::_sub_type_(other);
    }

    DirectRightValue *Float32::_mul_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Float32())->setValue(value.value() * ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_mul_(other);
    }

    ValueType Float32::_mul_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::FLOAT_32;
        }
        return DirectRightValue::_mul_type_(other);
    }

    DirectRightValue *Float32::_div_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                if (((Float32 *)otherDirect)->getValue() == 0)
                {
                    Error::DivisionByZeroError().error();
                    return nullptr;
                }
                return (new Float32())->setValue(value.value() / ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_div_(other);
    }

    ValueType Float32::_div_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::FLOAT_32;
        }
        return DirectRightValue::_div_type_(other);
    }

    float Float32::getValue() const
    {
        return value.has_value() ? value.value() : 0.0;
    }

    ValueType Float32::getValueType()
    {
        return ValueType::FLOAT_32;
    }

    DirectRightValue *Float32::_eq_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Boolean())->setValue(value == ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    ValueType Float32::_eq_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_eq_type_(other);
    }

    DirectRightValue *Float32::_ne_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Boolean())->setValue(value != ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    ValueType Float32::_ne_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_ne_type_(other);
    }

    DirectRightValue *Float32::_lt_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Boolean())->setValue(value < ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_lt_(other);
    }

    ValueType Float32::_lt_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_lt_type_(other);
    }

    DirectRightValue *Float32::_le_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Boolean())->setValue(value <= ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_le_(other);
    }

    ValueType Float32::_le_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_le_type_(other);
    }

    DirectRightValue *Float32::_gt_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Boolean())->setValue(value > ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_gt_(other);
    }

    ValueType Float32::_gt_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_gt_type_(other);
    }

    DirectRightValue *Float32::_ge_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32())
            {
                return (new Boolean())->setValue(value >= ((Float32 *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ge_(other);
    }

    ValueType Float32::_ge_type_(ValueType other)
    {
        if (other == ValueType::FLOAT_32)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_ge_type_(other);
    }

    DirectRightValue *Float32::_pos_()
    {
        return (new Float32())->setValue(value.value());
    }

    ValueType Float32::_pos_type_()
    {
        return ValueType::FLOAT_32;
    }

    DirectRightValue *Float32::_neg_()
    {
        return (new Float32())->setValue(-value.value());
    }

    ValueType Float32::_neg_type_()
    {
        return ValueType::FLOAT_32;
    }

    /*Boolean*/

    Boolean *Boolean::setValue(bool _value)
    {
        this->value = _value;
        return this;
    }

    DirectRightValue* Boolean::asBoolean()
    {
        return this;
    }

    DirectRightValue *Boolean::asInt32()
    {
        if (value.has_value())
        {
            return (new Int32())->setValue(value.value());
        }
        else{
            return new Int32();
        }
    }

    DirectRightValue *Boolean::asFloat32()
    {
        if (value.has_value())
        {
            return (new Float32())->setValue(value.value());
        }
        else{
            return new Float32();
        }
    }

    bool Boolean::isDirect()
    {
        if (value.has_value())
        {
            return true;
        }
        return false;
    }

    bool Boolean::getValue() const
    {
        if (value.has_value())
        {
            return value.value();
        }
        return false;
    }

    ValueType Boolean::getValueType()
    {
        return ValueType::BOOLEAN;
    }

    Boolean::Boolean() : DirectRightValue(NodeClass::BOOLEAN) {}

    void Boolean::toMermaid()
    {
        size_t boolean_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        putLabel(value ? "true" : "false");
        putEdge(boolean_id, value_id, "value");
        count();
    }

    void Boolean::toIR()
    {
        nextRegister();
        if (value.has_value()){
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue(value.value() ? "true" : "false"));
        }else{
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("null"));
        }
    }


    bool Boolean::isBoolean()
    {
        return true;
    }

    DirectRightValue *Boolean::_and_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean())
            {
                return (new Boolean())->setValue(value && ((Boolean *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_and_(other);
    }

    ValueType Boolean::_and_type_(ValueType other)
    {
        if (other == ValueType::BOOLEAN)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_and_type_(other);
    }

    DirectRightValue *Boolean::_or_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean())
            {
                return (new Boolean())->setValue(value || ((Boolean *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_or_(other);
    }

    ValueType Boolean::_or_type_(ValueType other)
    {
        if (other == ValueType::BOOLEAN)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_or_type_(other);
    }

    DirectRightValue *Boolean::_eq_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean())
            {
                return (new Boolean())->setValue(value == ((Boolean *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    ValueType Boolean::_eq_type_(ValueType other)
    {
        if (other == ValueType::BOOLEAN)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_eq_type_(other);
    }

    DirectRightValue *Boolean::_ne_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean())
            {
                return (new Boolean())->setValue(value != ((Boolean *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    ValueType Boolean::_ne_type_(ValueType other)
    {
        if (other == ValueType::BOOLEAN)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_ne_type_(other);
    }

    DirectRightValue *Boolean::_not_()
    {
        return (new Boolean())->setValue(!value);
    }

    ValueType Boolean::_not_type_()
    {
        return ValueType::BOOLEAN;
    }

    Pointer *Pointer::setValue(void *_value)
    {
        this->value = _value;
        return this;
    }

    void Pointer::toMermaid()
    {
        size_t pointer_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        putLabel(std::to_string((size_t)value));
        putEdge(pointer_id, value_id, "value");
        count();
    }

    void Pointer::toIR()
    {
        nextRegister();
        if (value != nullptr){
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue(std::to_string((size_t)value)));
        }else{
            irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("null"));
        }
    }

    Pointer::Pointer() : DirectRightValue(NodeClass::POINTER) {}

    ValueType Pointer::getValueType()
    {
        return ValueType::POINTER;
    }

    bool Pointer::isPointer()
    {
        return true;
    }

    void *Pointer::getValue() const
    {
        return value;
    }

    DirectRightValue *Pointer::_add_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Pointer())->setValue((void *)((size_t)value + ((Int32 *)otherDirect)->getValue()));
            }
        }
        return DirectRightValue::_add_(other);
    }
    ValueType Pointer::_add_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::POINTER;
        }
        return DirectRightValue::_add_type_(other);
    }

    DirectRightValue *
    Pointer::_sub_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32())
            {
                return (new Pointer())->setValue((void *)((size_t)value - ((Int32 *)otherDirect)->getValue()));
            }
            else if (otherDirect->isPointer())
            {
                return (new Int32())->setValue((int32_t)((size_t)value - (size_t)((Pointer *)otherDirect)->getValue()));
            }
        }
        return DirectRightValue::_sub_(other);
    }

    ValueType Pointer::_sub_type_(ValueType other)
    {
        if (other == ValueType::INT_32)
        {
            return ValueType::POINTER;
        }
        else if (other == ValueType::POINTER)
        {
            return ValueType::INT_32;
        }
        return DirectRightValue::_sub_type_(other);
    }

    DirectRightValue *Pointer::_eq_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer())
            {
                return (new Boolean())->setValue(value == ((Pointer *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    ValueType Pointer::_eq_type_(ValueType other)
    {
        if (other == ValueType::POINTER)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_eq_type_(other);
    }

    DirectRightValue *Pointer::_ne_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer())
            {
                return (new Boolean())->setValue(value != ((Pointer *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    ValueType Pointer::_ne_type_(ValueType other)
    {
        if (other == ValueType::POINTER)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_ne_type_(other);
    }

    DirectRightValue *Pointer::_lt_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer())
            {
                return (new Boolean())->setValue(value < ((Pointer *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_lt_(other);
    }

    ValueType Pointer::_lt_type_(ValueType other)
    {
        if (other == ValueType::POINTER)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_lt_type_(other);
    }

    DirectRightValue *Pointer::_le_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer())
            {
                return (new Boolean())->setValue(value <= ((Pointer *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_le_(other);
    }

    ValueType Pointer::_le_type_(ValueType other)
    {
        if (other == ValueType::POINTER)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_le_type_(other);
    }

    DirectRightValue *Pointer::_gt_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer())
            {
                return (new Boolean())->setValue(value > ((Pointer *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_gt_(other);
    }

    ValueType Pointer::_gt_type_(ValueType other)
    {
        if (other == ValueType::POINTER)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_gt_type_(other);
    }

    DirectRightValue *Pointer::_ge_(RightValue *other)
    {
        if (other->isDirect())
        {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer())
            {
                return (new Boolean())->setValue(value >= ((Pointer *)otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ge_(other);
    }

    ValueType Pointer::_ge_type_(ValueType other)
    {
        if (other == ValueType::POINTER)
        {
            return ValueType::BOOLEAN;
        }
        return DirectRightValue::_ge_type_(other);
    }

    /*IndirectRightValue*/

    IndirectRightValue::IndirectRightValue(AST::NodeClass _NodeClass) : RightValue(_NodeClass) {}

    DirectRightValue *IndirectRightValue::_add_(RightValue *other)
    {
        return this->directify()->_add_(other);
    }

    ValueType IndirectRightValue::_add_type_(ValueType other){
        return createValue(getValueType())->_add_type_(other);
    }

    DirectRightValue *IndirectRightValue::_sub_(RightValue *other)
    {
        return this->directify()->_sub_(other);
    }

    ValueType IndirectRightValue::_sub_type_(ValueType other)
    {
        return createValue(getValueType())->_sub_type_(other);
    }

    DirectRightValue *IndirectRightValue::_mul_(RightValue *other)
    {
        return this->directify()->_mul_(other);
    }

    ValueType IndirectRightValue::_mul_type_(ValueType other)
    {
        return createValue(getValueType())->_mul_type_(other);
    }

    DirectRightValue *IndirectRightValue::_div_(RightValue *other)
    {
        return this->directify()->_div_(other);
    }

    ValueType IndirectRightValue::_div_type_(ValueType other)
    {
        return createValue(getValueType())->_div_type_(other);
    }

    DirectRightValue *IndirectRightValue::_mod_(RightValue *other)
    {
        return this->directify()->_mod_(other);
    }

    ValueType IndirectRightValue::_mod_type_(ValueType other)
    {
        return createValue(getValueType())->_mod_type_(other);
    }

    DirectRightValue *IndirectRightValue::_and_(RightValue *other)
    {
        return this->directify()->_and_(other);
    }

    ValueType IndirectRightValue::_and_type_(ValueType other)
    {
        return createValue(getValueType())->_and_type_(other);
    }

    DirectRightValue *IndirectRightValue::_or_(RightValue *other)
    {
        return this->directify()->_or_(other);
    }

    ValueType IndirectRightValue::_or_type_(ValueType other)
    {
        return createValue(getValueType())->_or_type_(other);
    }

    DirectRightValue *IndirectRightValue::_eq_(RightValue *other)
    {
        return this->directify()->_eq_(other);
    }

    ValueType IndirectRightValue::_eq_type_(ValueType other)
    {
        return createValue(getValueType())->_eq_type_(other);
    }

    DirectRightValue *IndirectRightValue::_ne_(RightValue *other)
    {
        return this->directify()->_ne_(other);
    }

    ValueType IndirectRightValue::_ne_type_(ValueType other)
    {
        return createValue(getValueType())->_ne_type_(other);
    }

    DirectRightValue *IndirectRightValue::_lt_(RightValue *other)
    {
        return this->directify()->_lt_(other);
    }

    ValueType IndirectRightValue::_lt_type_(ValueType other)
    {
        return createValue(getValueType())->_lt_type_(other);
    }

    DirectRightValue *IndirectRightValue::_le_(RightValue *other)
    {
        return this->directify()->_le_(other);
    }

    ValueType IndirectRightValue::_le_type_(ValueType other)
    {
        return createValue(getValueType())->_le_type_(other);
    }

    DirectRightValue *IndirectRightValue::_gt_(RightValue *other)
    {
        return this->directify()->_gt_(other);
    }

    ValueType IndirectRightValue::_gt_type_(ValueType other)
    {
        return createValue(getValueType())->_gt_type_(other);
    }

    DirectRightValue *IndirectRightValue::_ge_(RightValue *other)
    {
        return this->directify()->_ge_(other);
    }

    ValueType IndirectRightValue::_ge_type_(ValueType other)
    {
        return createValue(getValueType())->_ge_type_(other);
    }

    DirectRightValue *IndirectRightValue::_pos_()
    {
        return this->directify()->_pos_();
    }

    ValueType IndirectRightValue::_pos_type_()
    {
        return createValue(getValueType())->_pos_type_();
    }

    DirectRightValue *IndirectRightValue::_neg_()
    {
        return this->directify()->_neg_();
    }

    ValueType IndirectRightValue::_neg_type_()
    {
        return createValue(getValueType())->_neg_type_();
    }

    DirectRightValue *IndirectRightValue::_not_()
    {
        return this->directify()->_not_();
    }

    ValueType IndirectRightValue::_not_type_()
    {
        return createValue(getValueType())->_not_type_();
    }

    ValueType IndirectRightValue::getValueType()
    {
        return this->directify()->getValueType();
    }

    DirectRightValue* IndirectRightValue::asBoolean()
    {
        return this->directify()->asBoolean();
    }

    DirectRightValue* IndirectRightValue::asInt32()
    {
        return this->directify()->asInt32();
    }

    DirectRightValue* IndirectRightValue::asFloat32()
    {
        return this->directify()->asFloat32();
    }

    DirectRightValue* IndirectRightValue::asPointer()
    {
        return this->directify()->asPointer();
    }

    /*Binary*/

    Binary *Binary::setLeft(RightValue *_left)
    {
        left = _left;
        return this;
    }

    Binary *Binary::setRight(RightValue *_right)
    {
        right = _right;
        return this;
    }

    Binary *Binary::setOp(Operator _op)
    {
        op = _op;
        return this;
    }

    RightValue *Binary::getLeft() const
    {
        return left;
    }

    RightValue *Binary::getRight() const
    {
        return right;
    }

    Operator Binary::getOp() const
    {
        return op;
    }

    void Binary::toMermaid()
    {
        size_t binary_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t left_id = getCounter();
        putLabel("left");
        left->toMermaid();
        putEdge(binary_id, left_id, "left");
        count();
        size_t right_id = getCounter();
        putLabel("right");
        right->toMermaid();
        putEdge(binary_id, right_id, "right");
        count();
        size_t op_id = getCounter();
        putLabel(op);
        count();
        putEdge(binary_id, op_id, "op");
    }

    void Binary::toIR()
    {
        
        
        left->toIR();
        size_t left_id = getRegister();
        right->toIR();
        size_t right_id = getRegister();
        nextRegister();
        size_t binary_id = getRegister();
        irs.push_back(
            (new IR::AssignBinary())
                ->setRegisterDestination(binary_id)
                ->setRegisterSource(left_id)
                ->setRegisterTarget(right_id)
                ->setOp(OperatorEnumMapToString(op)));
    }



    DirectRightValue *Binary::directify()
    {
        if (!isDirect())
        {
            throw std::runtime_error("this binary expression is not constant");
        }
        switch (op)
        {
        case Operator::ADD:
            return left->_add_(right);
        case Operator::SUB:
            return left->_sub_(right);
        case Operator::MUL:
            return left->_mul_(right);
        case Operator::DIV:
            return left->_div_(right);
        case Operator::MOD:
            return left->_mod_(right);
        case Operator::AND:
            return left->_and_(right);
        case Operator::OR:
            return left->_or_(right);
        case Operator::EQ:
            return left->_eq_(right);
        case Operator::NE:
            return left->_ne_(right);
        case Operator::LT:
            return left->_lt_(right);
        case Operator::LE:
            return left->_le_(right);
        case Operator::GT:
            return left->_gt_(right);
        case Operator::GE:
            return left->_ge_(right);
        default:
            throw std::runtime_error("Invalid operator");
        }
    }

    ValueType Binary::getValueType()
    {
        switch (op)
        {
        case Operator::ADD:
            return left->_add_type_(right->getValueType());
        case Operator::SUB:
            return left->_sub_type_(right->getValueType());
        case Operator::MUL:
            return left->_mul_type_(right->getValueType());
        case Operator::DIV:
            return left->_div_type_(right->getValueType());
        case Operator::MOD:
            return left->_mod_type_(right->getValueType());
        case Operator::AND:
            return left->_and_type_(right->getValueType());
        case Operator::OR:
            return left->_or_type_(right->getValueType());
        case Operator::EQ:
            return left->_eq_type_(right->getValueType());
        case Operator::NE:
            return left->_ne_type_(right->getValueType());
        case Operator::LT:
            return left->_lt_type_(right->getValueType());
        case Operator::LE:
            return left->_le_type_(right->getValueType());
        case Operator::GT:
            return left->_gt_type_(right->getValueType());
        case Operator::GE:
            return left->_ge_type_(right->getValueType());
        default:
            throw std::runtime_error("Invalid operator");
        }
    }

    Binary::Binary() : IndirectRightValue(NodeClass::BINARY) {}

    bool Binary::isDirect()
    {
        bool isLeftDirect = left->isDirect();
        if (isLeftDirect)
        {
            left = left->directify();
        }
        bool isRightDirect = right->isDirect();
        if (isRightDirect)
        {
            right = right->directify();
        }
        return isLeftDirect && isRightDirect;
    }

    /*---------------------Unary---------------------*/

    bool Unary::isDirect()
    {
        return expr->isDirect();
    }

    Unary *Unary::setExpr(AST::RightValue *_expr)
    {
        expr = _expr;
        return this;
    }

    RightValue *Unary::getExpr() const
    {
        return expr;
    }

    void Unary::toMermaid()
    {
        size_t unary_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t expr_id = getCounter();
        putLabel("expr");
        expr->toMermaid();
        putEdge(unary_id, expr_id, "expr");
        count();
        size_t op_id = getCounter();
        putLabel(op);
        count();
        putEdge(unary_id, op_id, "op");
    }

    void Unary::toIR()
    {
        size_t unary_id = getRegister();
        expr->toIR();
        nextRegister();
        irs.push_back((new IR::AssignUnary())->setRegisterSource(getRegister())->setOp(OperatorEnumMapToString(op))->setRegisterDestination(unary_id));
    }

    

    DirectRightValue *Unary::directify()
    {
        if (!isDirect())
        {
            throw std::runtime_error("this unary expression is not constant");
        }
        switch (op)
        {
        case Operator::POS:
            return expr->_pos_();
        case Operator::NEG:
            return expr->_neg_();
        case Operator::NOT:
            return expr->_not_();
        default:
            throw std::runtime_error("Invalid operator");
        }
    }

    ValueType Unary::getValueType()
    {
        switch (op)
        {
        case Operator::POS:
            return expr->_pos_type_();
        case Operator::NEG:
            return expr->_neg_type_();
        case Operator::NOT:
            return expr->_not_type_();
        default:
            throw std::runtime_error("Invalid operator");
        }
    }

    Unary *Unary::setOp(Operator _op)
    {
        op = _op;
        return this;
    }

    Operator Unary::getOp() const
    {
        return op;
    }

    Unary::Unary() : IndirectRightValue(NodeClass::UNARY) {}

    /*---------------------Variable---------------------*/
    Variable::Variable() : IndirectRightValue(NodeClass::VARIABLE) {}

    Variable *Variable::setName(const std::string &_name)
    {
        name = _name;
        return this;
    }

    const std::string &Variable::getName() const
    {
        return name;
    }

    ValueType Variable::getValueType()
    {
        if (analyzerContext.exists(this))
        {
            return analyzerContext.get(this)->getValueType();
        }
        return ValueType::VOID;
    }

    void Variable::toMermaid()
    {
        size_t variable_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t name_id = getCounter();
        putLabel(name);
        putEdge(variable_id, name_id, "name");
    }

    void Variable::toIR()
    {
        nextRegister();
        irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue(name));
    }
    

    bool Variable::isDirect()
    {
        if (analyzerContext.exists(this) && analyzerContext.get(this)->isDirect())
        {
            return true;
        }
        Error::UndeclaredVariableError(name).error();
        return false;
    }

    DirectRightValue *Variable::directify()
    {
        return analyzerContext.get(this);
    }

    Variable *Variable::setValueType(ValueType _type)
    {
        valueType = _type;
        return this;
    }

    ValueType Variable::getValueType() const
    {
        return valueType;
    }

    /*---------------------Void---------------------*/

    Void::Void() : DirectRightValue(NodeClass::VOID) {}

    void Void::toMermaid()
    {
        size_t void_id = getCounter();
        putLabel(getNodeClass());
        count();
        putEdge(void_id, getCounter(), "void");
    }

    void Void::toIR()
    {
        nextRegister();
        irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("void"));
    }


    ValueType Void::getValueType()
    {
        return ValueType::VOID;
    }

    bool Void::isVoid()
    {
        return true;
    }

    /*---------------------FunctionCall--------*/

    FunctionCall::FunctionCall() : IndirectRightValue(NodeClass::FUNCTION_CALL) {}

    FunctionCall *FunctionCall::setName(const std::string &_name)
    {
        name = _name;
        return this;
    }

    const std::string &FunctionCall::getName() const
    {
        return name;
    }


    void FunctionCall::toMermaid()
    {
        size_t functionCall_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t name_id = getCounter();
        putLabel(name);
        putEdge(functionCall_id, name_id, "name");
    }

    void FunctionCall::toIR()
    {
        ; // TODO
    }


    bool FunctionCall::isDirect()
    {
        return false;
    }

    ValueType FunctionCall::getValueType()
    {
        if (analyzerContext.exists(this->name))
        {
            return analyzerContext.get(this->name);
        }
        return ValueType::VOID;
    }

    DirectRightValue *FunctionCall::directify()
    {
        switch (getValueType())
        {
        case ValueType::INT_32:
            return new Int32();
        case ValueType::FLOAT_32:
            return new Float32();
        case ValueType::BOOLEAN:
            return new Boolean();
        case ValueType::POINTER:
            return new Pointer();
        case ValueType::VOID:
            return new Void();
        default:
            throw std::runtime_error("Invalid return type");
        }

    }

    DirectRightValue* createValue(ValueType type)
    {
        switch (type)
        {
        case ValueType::INT_32:
            return new Int32();
        case ValueType::FLOAT_32:
            return new Float32();
        case ValueType::BOOLEAN:
            return new Boolean();
        default:
            throw std::runtime_error("Invalid value type");
        }
    }
}