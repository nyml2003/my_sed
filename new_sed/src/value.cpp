#include "value.hpp"
#include "context.hpp"
#include "enumeration.hpp"
#include <iostream>
#include <stdexcept>
namespace SED::AST
{

/*Value*/

Value::Value(Enumeration::NodeClass _nodeClass, Enumeration::ValueType _valueType)
    : Node(_nodeClass), valueType(_valueType)
{
}

Enumeration::ValueType Value::getValueType()
{
    return valueType;
}

Value *Value::setValueType(Enumeration::ValueType _valueType)
{
    valueType = _valueType;
    return this;
}

void Value::analyze()
{
    // do nothing
    throw std::runtime_error("Not implemented");
}
/*Constant*/

Constant *Constant::constantify()
{
    return this;
}

Constant::Constant(Enumeration::ValueType _valueType) : Value(Enumeration::NodeClass::CONSTANT, _valueType)
{
}

Constant *Constant::_add_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::ADD, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_sub_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::SUB, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_mul_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::MUL, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_div_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::DIV, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_mod_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::MOD, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_and_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::AND, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_or_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::OR, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_eq_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::EQ, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_ne_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::NE, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_lt_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::LT, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_le_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::LE, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_gt_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::GT, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_ge_(Value *other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::GE, other->getValueType()).error();
    return nullptr;
}

Constant *Constant::_pos_()
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::POS).error();
    return nullptr;
}

Constant *Constant::_neg_()
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::NEG).error();
    return nullptr;
}

Constant *Constant::_not_()
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::NOT).error();
    return nullptr;
}

Enumeration::ValueType Constant::_add_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::ADD, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_sub_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::SUB, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_mul_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::MUL, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_div_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::DIV, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_mod_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::MOD, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_and_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::AND, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_or_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::OR, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_eq_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::EQ, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_ne_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::NE, other).error();
    return Enumeration::ValueType::VOID;
}
Enumeration::ValueType Constant::_lt_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::LT, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_le_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::LE, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_gt_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::GT, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_ge_type_(Enumeration::ValueType other)
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::GE, other).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_pos_type_()
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::POS).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_neg_type_()
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::NEG).error();
    return Enumeration::ValueType::VOID;
}

Enumeration::ValueType Constant::_not_type_()
{
    Error::InvalidOperationError(getValueType(), Enumeration::Operator::NOT).error();
    return Enumeration::ValueType::VOID;
}

bool Constant::isInt32()
{
    return false;
}

bool Constant::isFloat32()
{
    return false;
}

bool Constant::isBoolean()
{
    return false;
}

bool Constant::isPointer()
{
    return false;
}

bool Constant::isVoid()
{
    return false;
}

Constant *Constant::asBoolean()
{
    throw std::runtime_error("Invalid cast to boolean");
}

Constant *Constant::asInt32()
{
    throw std::runtime_error("Invalid cast to int32");
}

Constant *Constant::asFloat32()
{
    throw std::runtime_error("Invalid cast to float32");
}

Constant *Constant::asPointer()
{
    throw std::runtime_error("Invalid cast to pointer");
}

Constant *Constant::asChar()
{
    throw std::runtime_error("Invalid cast to char");
}

bool Constant::isChar()
{
    return false;
}

/*Int32*/

Int32::Int32() : Constant(Enumeration::ValueType::INT_32)
{
}

bool Int32::isConstant()
{
    if (value.has_value())
    {
        return true;
    }
    return false;
}

Constant *Int32::asInt32()
{
    return this;
}

Constant *Int32::asFloat32()
{
    if (value.has_value())
    {
        return (new Float32())->setValue(value.value());
    }
    else
    {
        return new Float32();
    }
}

Constant *Int32::asChar()
{
    if (value.has_value())
    {
        return (new Char())->setValue(value.value());
    }
    else
    {
        return new Char();
    }
}

Constant *Int32::asBoolean()
{
    if (value.has_value())
    {
        return (new Boolean())->setValue(value.value() != 0);
    }
    else
    {
        return new Boolean();
    }
}

int32_t Int32::getValue() const
{
    return value.has_value() ? value.value() : 0;
}

std::string Int32::toIRString()
{
    return std::to_string(value.value());
}

void Int32::toMermaid()
{
    size_t int32_id = getCounter();
    putLabel(getValueType());
    nextCounter();
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
    nextCounter();
}

void Int32::toIR()
{
    nextRegister();
    if (value.has_value())
    {
        irs.push_back((new IR::Assign())
                          ->setLeftValue(registerWrapper(getRegister()))
                          ->setRightValue(std::to_string(value.value())));
    }
    else
    {
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

Constant *Int32::_add_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Int32())->setValue(value.value() + ((Int32 *)otherDirect)->getValue());
        }
        else if (otherDirect->isChar())
        {
            return (new Char())->setValue(value.value() + ((Char *)otherDirect)->getValue());
        }
    }
    return Constant::_add_(other);
}

Enumeration::ValueType Int32::_add_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::INT_32;
    }
    else if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::CHAR;
    }
    return Constant::_add_type_(other);
}

Constant *Int32::_sub_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Int32())->setValue(value.value() - ((Int32 *)otherDirect)->getValue());
        }
    }
    return Constant::_sub_(other);
}

Enumeration::ValueType Int32::_sub_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::INT_32;
    }
    return Constant::_sub_type_(other);
}

Constant *Int32::_mul_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Int32())->setValue(value.value() * ((Int32 *)otherDirect)->getValue());
        }
    }
    return Constant::_mul_(other);
}

Enumeration::ValueType Int32::_mul_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::INT_32;
    }
    return Constant::_mul_type_(other);
}

Constant *Int32::_div_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
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
    return Constant::_div_(other);
}

Enumeration::ValueType Int32::_div_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::INT_32;
    }
    return Constant::_div_type_(other);
}

Constant *Int32::_mod_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
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
    return Constant::_mod_(other);
}

Enumeration::ValueType Int32::_mod_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::INT_32;
    }
    return Constant::_mod_type_(other);
}

Constant *Int32::_eq_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Boolean())->setValue(value.value() == ((Int32 *)otherDirect)->getValue());
        }
    }
    return Constant::_eq_(other);
}

Enumeration::ValueType Int32::_eq_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_eq_type_(other);
}

Constant *Int32::_ne_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Boolean())->setValue(value.value() != ((Int32 *)otherDirect)->getValue());
        }
    }
    return Constant::_ne_(other);
}

Enumeration::ValueType Int32::_ne_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ne_type_(other);
}

Constant *Int32::_lt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Boolean())->setValue(value.value() < ((Int32 *)other)->getValue());
        }
    }
    return Constant::_lt_(other);
}

Enumeration::ValueType Int32::_lt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_lt_type_(other);
}

Constant *Int32::_le_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Boolean())->setValue(value.value() <= ((Int32 *)other)->getValue());
        }
    }
    return Constant::_le_(other);
}

Enumeration::ValueType Int32::_le_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_le_type_(other);
}

Constant *Int32::_gt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Boolean())->setValue(value.value() > ((Int32 *)other)->getValue());
        }
    }
    return Constant::_gt_(other);
}

Enumeration::ValueType Int32::_gt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_gt_type_(other);
}

Constant *Int32::_ge_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Boolean())->setValue(value.value() >= ((Int32 *)otherDirect)->getValue());
        }
    }
    return Constant::_ge_(other);
}

Enumeration::ValueType Int32::_ge_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ge_type_(other);
}

Constant *Int32::_pos_()
{
    return (new Int32())->setValue(value.value());
}

Enumeration::ValueType Int32::_pos_type_()
{
    return Enumeration::ValueType::INT_32;
}

Constant *Int32::_neg_()
{
    return (new Int32())->setValue(-value.value());
}

Enumeration::ValueType Int32::_neg_type_()
{
    return Enumeration::ValueType::INT_32;
}

/*Float32*/

Float32::Float32() : Constant(Enumeration::ValueType::FLOAT_32)
{
}

std::string Float32::toIRString()
{
    return std::to_string(value.value());
}

bool Float32::isConstant()
{
    if (value.has_value())
    {
        return true;
    }
    return false;
}

Constant *Float32::asFloat32()
{
    return this;
}

Constant *Float32::asInt32()
{
    if (value.has_value())
    {
        return (new Int32())->setValue(value.value());
    }
    else
    {
        return new Int32();
    }
}

Constant *Float32::asBoolean()
{
    if (value.has_value())
    {
        return (new Boolean())->setValue(value.value() != 0);
    }
    else
    {
        return new Boolean();
    }
}

void Float32::toMermaid()
{
    size_t float32_id = getCounter();
    putLabel(getValueType());
    nextCounter();
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
    nextCounter();
}

void Float32::toIR()
{
    nextRegister();
    if (value.has_value())
    {
        irs.push_back((new IR::Assign())
                          ->setLeftValue(registerWrapper(getRegister()))
                          ->setRightValue(std::to_string(value.value())));
    }
    else
    {
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

Constant *Float32::_add_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Float32())->setValue(value.value() + ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_add_(other);
}
Enumeration::ValueType Float32::_add_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::FLOAT_32;
    }
    return Constant::_add_type_(other);
}
Constant *Float32::_sub_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Float32())->setValue(value.value() - ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_sub_(other);
}

Enumeration::ValueType Float32::_sub_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::FLOAT_32;
    }
    return Constant::_sub_type_(other);
}

Constant *Float32::_mul_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Float32())->setValue(value.value() * ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_mul_(other);
}

Enumeration::ValueType Float32::_mul_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::FLOAT_32;
    }
    return Constant::_mul_type_(other);
}

Constant *Float32::_div_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
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
    return Constant::_div_(other);
}

Enumeration::ValueType Float32::_div_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::FLOAT_32;
    }
    return Constant::_div_type_(other);
}

float Float32::getValue() const
{
    return value.has_value() ? value.value() : 0.0;
}

Constant *Float32::_eq_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Boolean())->setValue(value == ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_eq_(other);
}

Enumeration::ValueType Float32::_eq_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_eq_type_(other);
}

Constant *Float32::_ne_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Boolean())->setValue(value != ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_ne_(other);
}

Enumeration::ValueType Float32::_ne_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ne_type_(other);
}

Constant *Float32::_lt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Boolean())->setValue(value < ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_lt_(other);
}

Enumeration::ValueType Float32::_lt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_lt_type_(other);
}

Constant *Float32::_le_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Boolean())->setValue(value <= ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_le_(other);
}

Enumeration::ValueType Float32::_le_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_le_type_(other);
}

Constant *Float32::_gt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Boolean())->setValue(value > ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_gt_(other);
}

Enumeration::ValueType Float32::_gt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_gt_type_(other);
}

Constant *Float32::_ge_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isFloat32())
        {
            return (new Boolean())->setValue(value >= ((Float32 *)otherDirect)->getValue());
        }
    }
    return Constant::_ge_(other);
}

Enumeration::ValueType Float32::_ge_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::FLOAT_32)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ge_type_(other);
}

Constant *Float32::_pos_()
{
    return (new Float32())->setValue(value.value());
}

Enumeration::ValueType Float32::_pos_type_()
{
    return Enumeration::ValueType::FLOAT_32;
}

Constant *Float32::_neg_()
{
    return (new Float32())->setValue(-value.value());
}

Enumeration::ValueType Float32::_neg_type_()
{
    return Enumeration::ValueType::FLOAT_32;
}

/*Boolean*/

Boolean *Boolean::setValue(bool _value)
{
    this->value = _value;
    return this;
}

std::string Boolean::toIRString()
{
    if (value.has_value())
    {
        return value.value() ? "true" : "false";
    }
    return "null";
}

Constant *Boolean::asBoolean()
{
    return this;
}

Constant *Boolean::asInt32()
{
    if (value.has_value())
    {
        return (new Int32())->setValue(value.value());
    }
    else
    {
        return new Int32();
    }
}

bool Boolean::isConstant()
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

Boolean::Boolean() : Constant(Enumeration::ValueType::BOOLEAN)
{
}

void Boolean::toMermaid()
{
    size_t boolean_id = getCounter();
    putLabel(getValueType());
    nextCounter();
    size_t value_id = getCounter();
    putLabel(value ? "true" : "false");
    putEdge(boolean_id, value_id, "value");
    nextCounter();
}

void Boolean::toIR()
{
    nextRegister();
    if (value.has_value())
    {
        irs.push_back((new IR::Assign())
                          ->setLeftValue(registerWrapper(getRegister()))
                          ->setRightValue(value.value() ? "true" : "false"));
    }
    else
    {
        irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("null"));
    }
}

bool Boolean::isBoolean()
{
    return true;
}

Constant *Boolean::_and_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isBoolean())
        {
            return (new Boolean())->setValue(value && ((Boolean *)otherDirect)->getValue());
        }
    }
    return Constant::_and_(other);
}

Enumeration::ValueType Boolean::_and_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::BOOLEAN)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_and_type_(other);
}

Constant *Boolean::_or_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isBoolean())
        {
            return (new Boolean())->setValue(value || ((Boolean *)otherDirect)->getValue());
        }
    }
    return Constant::_or_(other);
}

Enumeration::ValueType Boolean::_or_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::BOOLEAN)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_or_type_(other);
}

Constant *Boolean::_eq_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isBoolean())
        {
            return (new Boolean())->setValue(value == ((Boolean *)otherDirect)->getValue());
        }
    }
    return Constant::_eq_(other);
}

Enumeration::ValueType Boolean::_eq_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::BOOLEAN)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_eq_type_(other);
}

Constant *Boolean::_ne_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isBoolean())
        {
            return (new Boolean())->setValue(value != ((Boolean *)otherDirect)->getValue());
        }
    }
    return Constant::_ne_(other);
}

Enumeration::ValueType Boolean::_ne_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::BOOLEAN)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ne_type_(other);
}

Constant *Boolean::_not_()
{
    return (new Boolean())->setValue(!value);
}

Enumeration::ValueType Boolean::_not_type_()
{
    return Enumeration::ValueType::BOOLEAN;
}

/*Char*/

Char::Char() : Constant(Enumeration::ValueType::CHAR)
{
}

bool Char::isConstant()
{
    if (value.has_value())
    {
        return true;
    }
    return false;
}

Char *Char::setValue(char _value)
{
    this->value = _value;
    return this;
}

std::string Char::toIRString()
{
    return std::string(1, '\'') + value.value() + std::string(1, '\'');
}

char Char::getValue() const
{
    return value.has_value() ? value.value() : 0;
}

void Char::toMermaid()
{
    size_t char_id = getCounter();
    putLabel(getValueType());
    nextCounter();
    size_t value_id = getCounter();
    if (value.has_value())
    {
        putLabel(std::string(1, '\'') + value.value() + std::string(1, '\''));
    }
    else
    {
        putLabel("null");
    }
    putEdge(char_id, value_id, "value");
    nextCounter();
}

void Char::toIR()
{
    nextRegister();
    if (value.has_value())
    {
        irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue(toIRString()));
    }
    else
    {
        irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("null"));
    }
}

bool Char::isChar()
{
    return true;
}

Constant *Char::_eq_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isChar())
        {
            return (new Boolean())->setValue(value == ((Char *)otherDirect)->getValue());
        }
    }
    return Constant::_eq_(other);
}

Enumeration::ValueType Char::_eq_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_eq_type_(other);
}

Constant *Char::_ne_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isChar())
        {
            return (new Boolean())->setValue(value != ((Char *)otherDirect)->getValue());
        }
    }
    return Constant::_ne_(other);
}

Enumeration::ValueType Char::_ne_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ne_type_(other);
}

Constant *Char::_lt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isChar())
        {
            return (new Boolean())->setValue(value < ((Char *)other)->getValue());
        }
    }
    return Constant::_lt_(other);
}

Enumeration::ValueType Char::_lt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_lt_type_(other);
}

Constant *Char::_le_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isChar())
        {
            return (new Boolean())->setValue(value <= ((Char *)other)->getValue());
        }
    }
    return Constant::_le_(other);
}

Enumeration::ValueType Char::_le_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_le_type_(other);
}

Constant *Char::_gt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isChar())
        {
            return (new Boolean())->setValue(value > ((Char *)other)->getValue());
        }
    }
    return Constant::_gt_(other);
}

Enumeration::ValueType Char::_gt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_gt_type_(other);
}

Constant *Char::_ge_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isChar())
        {
            return (new Boolean())->setValue(value >= ((Char *)other)->getValue());
        }
    }
    return Constant::_ge_(other);
}

Enumeration::ValueType Char::_ge_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ge_type_(other);
}

Constant *Char::_add_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Char())->setValue(value.value() + ((Int32 *)otherDirect)->getValue());
        }
    }
    return Constant::_add_(other);
}

Enumeration::ValueType Char::_add_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::CHAR;
    }
    return Constant::_add_type_(other);
}

Constant *Char::_sub_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Char())->setValue(value.value() - ((Int32 *)otherDirect)->getValue());
        }
        else if (otherDirect->isChar())
        {
            return (new Int32())->setValue(value.value() - ((Char *)otherDirect)->getValue());
        }
    }
    return Constant::_sub_(other);
}

Enumeration::ValueType Char::_sub_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::CHAR;
    }
    else if (other == Enumeration::ValueType::CHAR)
    {
        return Enumeration::ValueType::INT_32;
    }
    return Constant::_sub_type_(other);
}

Constant *Char::asChar()
{
    return this;
}

Constant *Char::asInt32()
{
    if (value.has_value())
    {
        return (new Int32())->setValue(value.value());
    }
    else
    {
        return new Int32();
    }
}

/*Pointer*/

Pointer *Pointer::setValue(void *_value)
{
    this->value = _value;
    return this;
}

bool Pointer::isConstant()
{
    if (value != nullptr)
    {
        return true;
    }
    return false;
}

void Pointer::toMermaid()
{
    size_t pointer_id = getCounter();
    putLabel(getValueType());
    nextCounter();
    size_t value_id = getCounter();
    putLabel(std::to_string((size_t)value));
    putEdge(pointer_id, value_id, "value");
    nextCounter();
}

void Pointer::toIR()
{
    nextRegister();
    if (value != nullptr)
    {
        irs.push_back((new IR::Assign())
                          ->setLeftValue(registerWrapper(getRegister()))
                          ->setRightValue(std::to_string((size_t)value)));
    }
    else
    {
        irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("null"));
    }
}

Pointer::Pointer() : Constant(Enumeration::ValueType::POINTER)
{
}

std::string Pointer::toIRString()
{
    return std::to_string((size_t)value);
}

bool Pointer::isPointer()
{
    return true;
}

void *Pointer::getValue() const
{
    return value;
}

Constant *Pointer::_add_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Pointer())->setValue((void *)((size_t)value + ((Int32 *)otherDirect)->getValue()));
        }
    }
    return Constant::_add_(other);
}
Enumeration::ValueType Pointer::_add_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::POINTER;
    }
    return Constant::_add_type_(other);
}

Constant *Pointer::_sub_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isInt32())
        {
            return (new Pointer())->setValue((void *)((size_t)value - ((Int32 *)otherDirect)->getValue()));
        }
        else if (otherDirect->isPointer())
        {
            return (new Int32())->setValue((int32_t)((size_t)value - (size_t)((Pointer *)otherDirect)->getValue()));
        }
    }
    return Constant::_sub_(other);
}

Enumeration::ValueType Pointer::_sub_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::INT_32)
    {
        return Enumeration::ValueType::POINTER;
    }
    else if (other == Enumeration::ValueType::POINTER)
    {
        return Enumeration::ValueType::INT_32;
    }
    return Constant::_sub_type_(other);
}

Constant *Pointer::_eq_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isPointer())
        {
            return (new Boolean())->setValue(value == ((Pointer *)otherDirect)->getValue());
        }
    }
    return Constant::_eq_(other);
}

Enumeration::ValueType Pointer::_eq_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::POINTER)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_eq_type_(other);
}

Constant *Pointer::_ne_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isPointer())
        {
            return (new Boolean())->setValue(value != ((Pointer *)otherDirect)->getValue());
        }
    }
    return Constant::_ne_(other);
}

Enumeration::ValueType Pointer::_ne_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::POINTER)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ne_type_(other);
}

Constant *Pointer::_lt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isPointer())
        {
            return (new Boolean())->setValue(value < ((Pointer *)otherDirect)->getValue());
        }
    }
    return Constant::_lt_(other);
}

Enumeration::ValueType Pointer::_lt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::POINTER)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_lt_type_(other);
}

Constant *Pointer::_le_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isPointer())
        {
            return (new Boolean())->setValue(value <= ((Pointer *)otherDirect)->getValue());
        }
    }
    return Constant::_le_(other);
}

Enumeration::ValueType Pointer::_le_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::POINTER)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_le_type_(other);
}

Constant *Pointer::_gt_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isPointer())
        {
            return (new Boolean())->setValue(value > ((Pointer *)otherDirect)->getValue());
        }
    }
    return Constant::_gt_(other);
}

Enumeration::ValueType Pointer::_gt_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::POINTER)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_gt_type_(other);
}

Constant *Pointer::_ge_(Value *other)
{
    if (other->isConstant())
    {
        auto otherDirect = other->constantify();
        if (otherDirect->isPointer())
        {
            return (new Boolean())->setValue(value >= ((Pointer *)otherDirect)->getValue());
        }
    }
    return Constant::_ge_(other);
}

Enumeration::ValueType Pointer::_ge_type_(Enumeration::ValueType other)
{
    if (other == Enumeration::ValueType::POINTER)
    {
        return Enumeration::ValueType::BOOLEAN;
    }
    return Constant::_ge_type_(other);
}

/*Mutable*/

Mutable::Mutable(Enumeration::NodeClass _nodeClass, Enumeration::ValueType _valueType) : Value(_nodeClass, _valueType)
{
}

Constant *Mutable::_add_(Value *other)
{
    return this->constantify()->_add_(other);
}

Enumeration::ValueType Mutable::_add_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_add_type_(other);
}

Constant *Mutable::_sub_(Value *other)
{
    return this->constantify()->_sub_(other);
}

Enumeration::ValueType Mutable::_sub_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_sub_type_(other);
}

Constant *Mutable::_mul_(Value *other)
{
    return this->constantify()->_mul_(other);
}

Enumeration::ValueType Mutable::_mul_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_mul_type_(other);
}

Constant *Mutable::_div_(Value *other)
{
    return this->constantify()->_div_(other);
}

Enumeration::ValueType Mutable::_div_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_div_type_(other);
}

Constant *Mutable::_mod_(Value *other)
{
    return this->constantify()->_mod_(other);
}

Enumeration::ValueType Mutable::_mod_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_mod_type_(other);
}

Constant *Mutable::_and_(Value *other)
{
    return this->constantify()->_and_(other);
}

Enumeration::ValueType Mutable::_and_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_and_type_(other);
}

Constant *Mutable::_or_(Value *other)
{
    return this->constantify()->_or_(other);
}

Enumeration::ValueType Mutable::_or_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_or_type_(other);
}

Constant *Mutable::_eq_(Value *other)
{
    return this->constantify()->_eq_(other);
}

Enumeration::ValueType Mutable::_eq_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_eq_type_(other);
}

Constant *Mutable::_ne_(Value *other)
{
    return this->constantify()->_ne_(other);
}

Enumeration::ValueType Mutable::_ne_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_ne_type_(other);
}

Constant *Mutable::_lt_(Value *other)
{
    return this->constantify()->_lt_(other);
}

Enumeration::ValueType Mutable::_lt_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_lt_type_(other);
}

Constant *Mutable::_le_(Value *other)
{
    return this->constantify()->_le_(other);
}

Enumeration::ValueType Mutable::_le_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_le_type_(other);
}

Constant *Mutable::_gt_(Value *other)
{
    return this->constantify()->_gt_(other);
}

Enumeration::ValueType Mutable::_gt_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_gt_type_(other);
}

Constant *Mutable::_ge_(Value *other)
{
    return this->constantify()->_ge_(other);
}

Enumeration::ValueType Mutable::_ge_type_(Enumeration::ValueType other)
{
    return Constant::createValue(getValueType())->_ge_type_(other);
}

Constant *Mutable::_pos_()
{
    return this->constantify()->_pos_();
}

Enumeration::ValueType Mutable::_pos_type_()
{
    return Constant::createValue(getValueType())->_pos_type_();
}

Constant *Mutable::_neg_()
{
    return this->constantify()->_neg_();
}

Enumeration::ValueType Mutable::_neg_type_()
{
    return Constant::createValue(getValueType())->_neg_type_();
}

Constant *Mutable::_not_()
{
    return this->constantify()->_not_();
}

Enumeration::ValueType Mutable::_not_type_()
{
    return Constant::createValue(getValueType())->_not_type_();
}

Constant *Mutable::asBoolean()
{
    return this->constantify()->asBoolean();
}

Constant *Mutable::asInt32()
{
    return this->constantify()->asInt32();
}

Constant *Mutable::asFloat32()
{
    return this->constantify()->asFloat32();
}

Constant *Mutable::asPointer()
{
    return this->constantify()->asPointer();
}

Constant *Mutable::asChar()
{
    return this->constantify()->asChar();
}

/*Binary*/

Enumeration::ValueType Binary::getValueType()
{
    Enumeration::ValueType type = Enumeration::ValueType::VOID;
    left->setValueType(left->getValueType());
    right->setValueType(right->getValueType());
    switch (op)
    {
    case Enumeration::Operator::ADD:
        type = left->_add_type_(right->getValueType());
        break;
    case Enumeration::Operator::SUB:
        type = left->_sub_type_(right->getValueType());
        break;
    case Enumeration::Operator::MUL:
        type = left->_mul_type_(right->getValueType());
        break;
    case Enumeration::Operator::DIV:
        type = left->_div_type_(right->getValueType());
        break;
    case Enumeration::Operator::MOD:
        type = left->_mod_type_(right->getValueType());
        break;
    case Enumeration::Operator::AND:
        type = left->_and_type_(right->getValueType());
        break;
    case Enumeration::Operator::OR:
        type = left->_or_type_(right->getValueType());
        break;
    case Enumeration::Operator::EQ:
        type = left->_eq_type_(right->getValueType());
        break;
    case Enumeration::Operator::NE:
        type = left->_ne_type_(right->getValueType());
        break;
    case Enumeration::Operator::LT:
        type = left->_lt_type_(right->getValueType());
        break;
    case Enumeration::Operator::LE:
        type = left->_le_type_(right->getValueType());
        break;
    case Enumeration::Operator::GT:
        type = left->_gt_type_(right->getValueType());
        break;
    case Enumeration::Operator::GE:
        type = left->_ge_type_(right->getValueType());
        break;
    default:
        throw std::runtime_error("Invalid operator");
    }
    setValueType(type);
    return type;
}

Binary::Binary() : Mutable(Enumeration::NodeClass::BINARY, Enumeration::ValueType::VOID)
{
}

Binary *Binary::setLeft(Value *_left)
{
    left = _left;
    return this;
}

Binary *Binary::setRight(Value *_right)
{
    right = _right;
    return this;
}

Binary *Binary::setOp(Enumeration::Operator _op)
{
    op = _op;
    return this;
}

Value *Binary::getLeft() const
{
    return left;
}

Value *Binary::getRight() const
{
    return right;
}

Enumeration::Operator Binary::getOp() const
{
    return op;
}

void Binary::toMermaid()
{
    size_t binary_id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    size_t left_id = getCounter();
    putLabel("left");
    left->toMermaid();
    putEdge(binary_id, left_id, "left");
    nextCounter();
    size_t right_id = getCounter();
    putLabel("right");
    right->toMermaid();
    putEdge(binary_id, right_id, "right");
    nextCounter();
    size_t op_id = getCounter();
    putLabel(op);
    nextCounter();
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
    irs.push_back((new IR::AssignBinary())
                      ->setRegisterDestination(binary_id)
                      ->setRegisterSource(left_id)
                      ->setRegisterTarget(right_id)
                      ->setOp(Generator::irOperatorWrapper(op)));
}

Constant *Binary::constantify()
{
    if (!isConstant())
    {
        throw std::runtime_error("this binary expression is not constant");
    }
    switch (op)
    {
    case Enumeration::Operator::ADD:
        return left->_add_(right);
    case Enumeration::Operator::SUB:
        return left->_sub_(right);
    case Enumeration::Operator::MUL:
        return left->_mul_(right);
    case Enumeration::Operator::DIV:
        return left->_div_(right);
    case Enumeration::Operator::MOD:
        return left->_mod_(right);
    case Enumeration::Operator::AND:
        return left->_and_(right);
    case Enumeration::Operator::OR:
        return left->_or_(right);
    case Enumeration::Operator::EQ:
        return left->_eq_(right);
    case Enumeration::Operator::NE:
        return left->_ne_(right);
    case Enumeration::Operator::LT:
        return left->_lt_(right);
    case Enumeration::Operator::LE:
        return left->_le_(right);
    case Enumeration::Operator::GT:
        return left->_gt_(right);
    case Enumeration::Operator::GE:
        return left->_ge_(right);
    default:
        throw std::runtime_error("Invalid operator");
    }
}

bool Binary::isConstant()
{
    bool isLeftDirect = left->isConstant();
    if (isLeftDirect)
    {
        left = left->constantify();
    }
    bool isRightDirect = right->isConstant();
    if (isRightDirect)
    {
        right = right->constantify();
    }
    return isLeftDirect && isRightDirect;
}

/*---------------------Unary---------------------*/
Unary::Unary() : Mutable(Enumeration::NodeClass::UNARY, Enumeration::ValueType::VOID)
{
}

Unary *Unary::setExpr(Value *_expr)
{
    expr = _expr;
    return this;
}

Unary *Unary::setOp(Enumeration::Operator _op)
{
    op = _op;
    return this;
}

Enumeration::ValueType Unary::getValueType()
{
    expr->setValueType(expr->getValueType());
    switch (op)
    {
    case Enumeration::Operator::POS:
        return expr->_pos_type_();
    case Enumeration::Operator::NEG:
        return expr->_neg_type_();
    case Enumeration::Operator::NOT:
        return expr->_not_type_();
    default:
        throw std::runtime_error("Invalid operator");
    }
}
bool Unary::isConstant()
{
    return expr->isConstant();
}

Value *Unary::getExpr() const
{
    return expr;
}

void Unary::toMermaid()
{
    size_t unary_id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    size_t expr_id = getCounter();
    putLabel("expr");
    expr->toMermaid();
    putEdge(unary_id, expr_id, "expr");
    nextCounter();
    size_t op_id = getCounter();
    putLabel(op);
    nextCounter();
    putEdge(unary_id, op_id, "op");
}

void Unary::toIR()
{
    expr->toIR();
    size_t expr_id = getRegister();
    nextRegister();
    size_t unary_id = getRegister();
    irs.push_back((new IR::AssignUnary())
                      ->setRegisterDestination(unary_id)
                      ->setRegisterSource(expr_id)
                      ->setOp(Generator::irOperatorWrapper(op)));
}

Constant *Unary::constantify()
{
    if (!isConstant())
    {
        throw std::runtime_error("this unary expression is not constant");
    }
    switch (op)
    {
    case Enumeration::Operator::POS:
        return expr->_pos_();
    case Enumeration::Operator::NEG:
        return expr->_neg_();
    case Enumeration::Operator::NOT:
        return expr->_not_();
    default:
        throw std::runtime_error("Invalid operator");
    }
}

Enumeration::Operator Unary::getOp() const
{
    return op;
}

/*---------------------Variable---------------------*/
Variable::Variable() : Mutable(Enumeration::NodeClass::VARIABLE, Enumeration::ValueType::VOID)
{
}

Variable *Variable::setName(const std::string &_name)
{
    name = _name;
    return this;
}

const std::string &Variable::getName() const
{
    return name;
}

Enumeration::ValueType Variable::getValueType()
{
    if (analyzerContext.exists(this))
    {
        return analyzerContext.get(this)->getValueType();
    }
    return valueType;
}

void Variable::toMermaid()
{
    size_t variable_id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    size_t name_id = getCounter();
    putLabel(name);
    putEdge(variable_id, name_id, "name");
}

void Variable::toIR()
{
    nextRegister();
    irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue(name));
}

bool Variable::isConstant()
{
    if (analyzerContext.exists(this))
    {
        return analyzerContext.get(this)->isConstant();
    }
    else
    {
        Error::UndeclaredVariableError(name).error();
    }
    return false;
}

Constant *Variable::constantify()
{
    return analyzerContext.get(this);
}

Variable *Variable::setValueType(Enumeration::ValueType _type)
{
    valueType = _type;
    return this;
}

/*---------------------Void---------------------*/

Void::Void() : Constant(Enumeration::ValueType::VOID)
{
}

bool Void::isConstant()
{
    return false;
}

void Void::toMermaid()
{
    size_t void_id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    putEdge(void_id, getCounter(), "void");
}

std::string Void::toIRString()
{
    return "void";
}

void Void::toIR()
{
    nextRegister();
    irs.push_back((new IR::Assign())->setLeftValue(registerWrapper(getRegister()))->setRightValue("void"));
}

bool Void::isVoid()
{
    return true;
}

/*---------------------FunctionCall--------*/

FunctionCall::FunctionCall() : Mutable(Enumeration::NodeClass::FUNCTION_CALL, Enumeration::ValueType::VOID)
{
}

FunctionCall *FunctionCall::setName(const std::string &_name)
{
    name = _name;
    return this;
}

const std::string &FunctionCall::getName() const
{
    return name;
}

FunctionCall *FunctionCall::setArguments(const std::vector<Value *> &_arguments)
{
    arguments = _arguments;
    return this;
}

const std::vector<Value *> &FunctionCall::getArguments() const
{
    return arguments;
}

void FunctionCall::toMermaid()
{
    size_t functionCall_id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    size_t name_id = getCounter();
    putLabel(name);
    putEdge(functionCall_id, name_id, "name");
    for (size_t i = 0; i < arguments.size(); i++)
    {
        nextCounter();
        size_t argument_id = getCounter();
        putLabel("argument " + std::to_string(i));
        arguments[i]->toMermaid();
        putEdge(functionCall_id, argument_id, "argument " + std::to_string(i));
    }
}

Enumeration::ValueType FunctionCall::getValueType()
{
    if (analyzerContext.exists(this))
    {
        return analyzerContext.get(this)[0];
    }
    throw std::runtime_error("Function not found");
}

void FunctionCall::toIR()
{
    std::vector<size_t> argument_ids;
    for (size_t i = 0; i < arguments.size(); i++)
    {
        arguments[i]->toIR();
        argument_ids.push_back(getRegister());
    }
    nextRegister();
    size_t functionCall_id = getRegister();
    for (size_t i = 0; i < arguments.size(); i++)
    {
        irs.push_back((new IR::Argument())->setRegisterSource(argument_ids[i]));
    }
    irs.push_back((new IR::AssignCall())->setRegisterDestination(functionCall_id)->setFunction(name));
}

bool FunctionCall::isConstant()
{
    for (size_t i = 0; i < arguments.size(); i++)
    {
        arguments[i]->constantify();
    }
    return false;
}

Constant *FunctionCall::constantify()
{
    // 比较arguments的类型和函数的参数类型是否一致
    auto types = analyzerContext.get(this);
    types.erase(types.begin());
    if (types.size() != arguments.size())
    {
        Error::FunctionCallArgumentCountError(name, types.size(), arguments.size()).error();
    }
    for (size_t i = 0; i < arguments.size(); i++)
    {
        if (arguments[i]->getValueType() != types[i])
        {
            Error::FunctionCallArgumentTypeError(name, i, arguments[i]->getValueType(), types[i]).error();
        }
    }

    switch (getValueType())
    {
    case Enumeration::ValueType::INT_32:
        return new Int32();
    case Enumeration::ValueType::FLOAT_32:
        return new Float32();
    case Enumeration::ValueType::BOOLEAN:
        return new Boolean();
    case Enumeration::ValueType::POINTER:
        return new Pointer();
    case Enumeration::ValueType::VOID:
        return new Void();
    default:
        throw std::runtime_error("Invalid return type");
    }
}

Constant *Constant::createValue(Enumeration::ValueType type)
{
    switch (type)
    {
    case Enumeration::ValueType::INT_32:
        return new Int32();
    case Enumeration::ValueType::FLOAT_32:
        return new Float32();
    case Enumeration::ValueType::BOOLEAN:
        return new Boolean();
    case Enumeration::ValueType::POINTER:
        return new Pointer();
    case Enumeration::ValueType::VOID:
        return new Void();
    case Enumeration::ValueType::CHAR:
        return new Char();
    default:
        throw std::runtime_error("Invalid value type");
    }
}
} // namespace SED::AST