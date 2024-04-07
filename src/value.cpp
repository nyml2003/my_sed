#include <stdexcept>
#include "value.hpp"
#include "context.hpp"
#include <iostream>
namespace SED::AST {


    RightValue::RightValue(AST::NodeClass _NodeClass) : Node(_NodeClass) {}

    bool RightValue::isSameValueType(RightValue *other) {
        return getNodeClass() == other->getNodeClass();
    }


    /**
    * @brief 对于一个右值来说，需要父节点来执行直接右值(常量化)
    * @brief 一个类没法自己修改自己的值，所以这里不实现，而是满足接口，真正的实现由父结点来调用右值定义的各种优化接口
    */
    void RightValue::analyze(){
        ;
    }

    void DirectRightValue::throwTypeMismatchError(const std::string &operation, NodeClass left, NodeClass right) {
        throw std::runtime_error(
                "Invalid operation: " + Generator::NodeClassToMermaid::toMermaid(left) + " " + operation + " " + Generator::NodeClassToMermaid::toMermaid(right));
    }

    void DirectRightValue::throwTypeMismatchError(const std::string &operation, NodeClass left) {
        throw std::runtime_error(
                "Invalid operation: " + operation + " " + Generator::NodeClassToMermaid::toMermaid(left));
    }

    bool DirectRightValue::isDirect() {
        return true;
    }

    DirectRightValue *DirectRightValue::directify() {
        return this;
    }

    DirectRightValue::DirectRightValue(AST::NodeClass _NodeClass) : RightValue(_NodeClass) {}

    DirectRightValue *DirectRightValue::_add_(RightValue *other) {
        throwTypeMismatchError("+", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_sub_(RightValue *other) {
        throwTypeMismatchError("-", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_mul_(RightValue *other) {
        throwTypeMismatchError("*", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_div_(RightValue *other) {
        throwTypeMismatchError("/", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_mod_(RightValue *other) {
        throwTypeMismatchError("%", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_and_(RightValue *other) {
        throwTypeMismatchError("&&", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_or_(RightValue *other) {
        throwTypeMismatchError("||", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_eq_(RightValue *other) {
        throwTypeMismatchError("==", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_ne_(RightValue *other) {
        throwTypeMismatchError("!=", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_lt_(RightValue *other) {
        throwTypeMismatchError("<", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_le_(RightValue *other) {
        throwTypeMismatchError("<=", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_gt_(RightValue *other) {
        throwTypeMismatchError(">", getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_ge_(RightValue *other) {
        throwTypeMismatchError(">=",getNodeClass(), other->getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_pos_() {
        throwTypeMismatchError("+", getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_neg_() {
        throwTypeMismatchError("-", getNodeClass());
        return nullptr;
    }

    DirectRightValue *DirectRightValue::_not_() {
        throwTypeMismatchError("!", getNodeClass());
        return nullptr;
    }

    bool DirectRightValue::isInt32() {
        return false;
    }

    bool DirectRightValue::isFloat32() {
        return false;
    }

    bool DirectRightValue::isBoolean() {
        return false;
    }

    bool DirectRightValue::isPointer() {
        return false;
    }

    bool DirectRightValue::isVoid() {
        return false;
    }


    Int32::Int32() : DirectRightValue(NodeClass::INT_32) {}

    int32_t Int32::getValue() const {
        return value;
    }

    void Int32::toMermaid() {
        size_t int32_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        putLabel(std::to_string(value));
        putEdge(int32_id, value_id, "value");
        count();
    }

    Int32 *Int32::setValue(int32_t _value) {
        this->value = _value;
        return this;
    }

    bool Int32::isInt32() {
        return true;
    }

    ValueType Int32::getValueType() {
        return ValueType::INT_32;
    }

    DirectRightValue *Int32::_add_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Int32())->setValue(value + ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_add_(other);
    }

    DirectRightValue *Int32::_sub_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Int32())->setValue(value - ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_sub_(other);
    }

    DirectRightValue *Int32::_mul_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Int32())->setValue(value * ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_mul_(other);
    }

    DirectRightValue *Int32::_div_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                if (((Int32 *) otherDirect )->getValue() == 0) {
                    throw std::runtime_error("Division by zero");
                }
                if (value % ((Int32 *) otherDirect)->getValue() == 0) {
                    return (new Int32())->setValue(value / ((Int32 *) otherDirect)->getValue());
                } else {
                    return (new Float32())->setValue((float) value / (float) ((Int32 *) otherDirect)->getValue());
                }
            }
        }
        return DirectRightValue::_div_(other);
    }

    DirectRightValue *Int32::_mod_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                if (((Int32 *) otherDirect)->getValue() == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return (new Int32())->setValue(value % ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_mod_(other);
    }

    DirectRightValue *Int32::_eq_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Boolean())->setValue(value == ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    DirectRightValue *Int32::_ne_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Boolean())->setValue(value != ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    DirectRightValue *Int32::_lt_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Boolean())->setValue(value < ((Int32 *) other)->getValue());
            }
        }
        return DirectRightValue::_lt_(other);
    }

    DirectRightValue *Int32::_le_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Boolean())->setValue(value <= ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_le_(other);
    }

    DirectRightValue *Int32::_gt_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Boolean())->setValue(value > ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_gt_(other);
    }

    DirectRightValue *Int32::_ge_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Boolean())->setValue(value >= ((Int32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ge_(other);
    }

    DirectRightValue *Int32::_pos_() {
        return (new Int32())->setValue(value);
    }

    DirectRightValue *Int32::_neg_() {
        return (new Int32())->setValue(-value);
    }

    Float32::Float32() : DirectRightValue(NodeClass::FLOAT_32) {}

    void Float32::toMermaid() {
        size_t float32_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        putLabel(std::to_string(value));
        putEdge(float32_id, value_id, "value");
        count();
    }

    Float32 *Float32::setValue(float _value) {
        this->value = _value;
        return this;
    }

    bool Float32::isFloat32() {
        return true;
    }

    DirectRightValue *Float32::_add_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Float32())->setValue(value + ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_add_(other);
    }

    DirectRightValue *Float32::_sub_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Float32())->setValue(value - ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_sub_(other);
    }

    DirectRightValue *Float32::_mul_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Float32())->setValue(value * ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_mul_(other);
    }

    DirectRightValue *Float32::_div_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                if (((Float32 *) otherDirect)->getValue() == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return (new Float32())->setValue(value / ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_div_(other);
    }

    float Float32::getValue() const {
        return value;
    }

    ValueType Float32::getValueType() {
        return ValueType::FLOAT_32;
    }

    DirectRightValue *Float32::_eq_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Boolean())->setValue(value == ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    DirectRightValue *Float32::_ne_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Boolean())->setValue(value != ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    DirectRightValue *Float32::_lt_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Boolean())->setValue(value < ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_lt_(other);
    }

    DirectRightValue *Float32::_le_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Boolean())->setValue(value <= ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_le_(other);
    }

    DirectRightValue *Float32::_gt_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Boolean())->setValue(value > ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_gt_(other);
    }

    DirectRightValue *Float32::_ge_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isFloat32()) {
                return (new Boolean())->setValue(value >= ((Float32 *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ge_(other);
    }

    DirectRightValue *Float32::_pos_() {
        return (new Float32())->setValue(value);
    }

    DirectRightValue *Float32::_neg_() {
        return (new Float32())->setValue(-value);
    }

    Boolean *Boolean::setValue(bool _value) {
        this->value = _value;
        return this;
    }

    bool Boolean::getValue() const {
        return value;
    }

    ValueType Boolean::getValueType() {
        return ValueType::BOOLEAN;
    }

    Boolean::Boolean() : DirectRightValue(NodeClass::BOOLEAN) {}

    void Boolean::toMermaid() {
        size_t boolean_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        putLabel(value ? "true" : "false");
        putEdge(boolean_id, value_id, "value");
        count();
    }

    bool Boolean::isBoolean() {
        return true;
    }

    DirectRightValue *Boolean::_and_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean()) {
                return (new Boolean())->setValue(value && ((Boolean *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_and_(other);
    }

    DirectRightValue *Boolean::_or_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean()) {
                return (new Boolean())->setValue(value || ((Boolean *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_or_(other);
    }

    DirectRightValue *Boolean::_eq_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean()) {
                return (new Boolean())->setValue(value == ((Boolean *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    DirectRightValue *Boolean::_ne_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isBoolean()) {
                return (new Boolean())->setValue(value != ((Boolean *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    DirectRightValue *Boolean::_not_() {
        return (new Boolean())->setValue(!value);
    }

    Pointer *Pointer::setValue(void *_value) {
        this->value = _value;
        return this;
    }

    void Pointer::toMermaid() {
        size_t pointer_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t value_id = getCounter();
        putLabel(std::to_string((size_t) value));
        putEdge(pointer_id, value_id, "value");
        count();
    }

    Pointer::Pointer() : DirectRightValue(NodeClass::POINTER) {}

    ValueType Pointer::getValueType() {
        return ValueType::POINTER;
    }

    bool Pointer::isPointer() {
        return true;
    }

    void *Pointer::getValue() const {
        return value;
    }

    DirectRightValue *Pointer::_add_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Pointer())->setValue((void *) ((size_t) value + ((Int32 *) otherDirect)->getValue()));
            }
        }
        return DirectRightValue::_add_(other);
    }

    DirectRightValue *Pointer::_sub_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isInt32()) {
                return (new Pointer())->setValue((void *) ((size_t) value - ((Int32 *) otherDirect)->getValue()));
            } else if (otherDirect->isPointer()) {
                return (new Int32())->setValue((int32_t) ((size_t) value - (size_t) ((Pointer *) otherDirect)->getValue()));
            }
        }
        return DirectRightValue::_sub_(other);
    }

    DirectRightValue *Pointer::_eq_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer()) {
                return (new Boolean())->setValue(value == ((Pointer *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_eq_(other);
    }

    DirectRightValue *Pointer::_ne_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer()) {
                return (new Boolean())->setValue(value != ((Pointer *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ne_(other);
    }

    DirectRightValue *Pointer::_lt_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer()) {
                return (new Boolean())->setValue(value < ((Pointer *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_lt_(other);
    }

    DirectRightValue *Pointer::_le_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer()) {
                return (new Boolean())->setValue(value <= ((Pointer *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_le_(other);
    }

    DirectRightValue *Pointer::_gt_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer()) {
                return (new Boolean())->setValue(value > ((Pointer *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_gt_(other);
    }

    DirectRightValue *Pointer::_ge_(RightValue *other) {
        if (other->isDirect()) {
            auto otherDirect = other->directify();
            if (otherDirect->isPointer()) {
                return (new Boolean())->setValue(value >= ((Pointer *) otherDirect)->getValue());
            }
        }
        return DirectRightValue::_ge_(other);
    }

    IndirectRightValue::IndirectRightValue(AST::NodeClass _NodeClass): RightValue(_NodeClass) {}

    DirectRightValue *IndirectRightValue::_add_(RightValue *other) {
        return this->directify()->_add_(other);
    }

    DirectRightValue *IndirectRightValue::_sub_(RightValue *other) {
        return this->directify()->_sub_(other);
    }

    DirectRightValue *IndirectRightValue::_mul_(RightValue *other) {
        return this->directify()->_mul_(other);
    }

    DirectRightValue *IndirectRightValue::_div_(RightValue *other) {
        return this->directify()->_div_(other);
    }

    DirectRightValue *IndirectRightValue::_mod_(RightValue *other) {
        return this->directify()->_mod_(other);
    }

    DirectRightValue *IndirectRightValue::_and_(RightValue *other) {
        return this->directify()->_and_(other);
    }

    DirectRightValue *IndirectRightValue::_or_(RightValue *other) {
        return this->directify()->_or_(other);
    }

    DirectRightValue *IndirectRightValue::_eq_(RightValue *other) {
        return this->directify()->_eq_(other);
    }

    DirectRightValue *IndirectRightValue::_ne_(RightValue *other) {
        return this->directify()->_ne_(other);
    }

    DirectRightValue *IndirectRightValue::_lt_(RightValue *other) {
        return this->directify()->_lt_(other);
    }

    DirectRightValue *IndirectRightValue::_le_(RightValue *other) {
        return this->directify()->_le_(other);
    }

    DirectRightValue *IndirectRightValue::_gt_(RightValue *other) {
        return this->directify()->_gt_(other);
    }

    DirectRightValue *IndirectRightValue::_ge_(RightValue *other) {
        return this->directify()->_ge_(other);
    }

    DirectRightValue *IndirectRightValue::_pos_() {
        return this->directify()->_pos_();
    }

    DirectRightValue *IndirectRightValue::_neg_() {
        return this->directify()->_neg_();
    }

    DirectRightValue *IndirectRightValue::_not_() {
        return this->directify()->_not_();
    }

    ValueType IndirectRightValue::getValueType() {
        return this->directify()->getValueType();
    }

    Binary *Binary::setLeft(RightValue *_left) {
        left = _left;
        return this;
    }

    Binary *Binary::setRight(RightValue *_right) {
        right = _right;
        return this;
    }

    Binary *Binary::setOp(Operator _op) {
        op = _op;
        return this;
    }

    RightValue *Binary::getLeft() const {
        return left;
    }

    RightValue *Binary::getRight() const {
        return right;
    }

    Operator Binary::getOp() const {
        return op;
    }

    void Binary::toMermaid() {
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

    DirectRightValue *Binary::directify() {
        try {
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
        }catch(std::runtime_error &e){
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        
    }

    Binary::Binary() : IndirectRightValue(NodeClass::BINARY) {}


    bool Binary::isDirect() {
        bool isLeftDirect = left->isDirect();
        if (isLeftDirect) {
            left = left->directify();
        }
        bool isRightDirect = right->isDirect();
        if (isRightDirect) {
            right = right->directify();
        }
        return isLeftDirect && isRightDirect;
    }

    /*---------------------Unary---------------------*/

    bool Unary::isDirect() {
        return expr->isDirect();
    }

    Unary *Unary::setExpr(AST::RightValue *_expr) {
        expr = _expr;
        return this;
    }

    RightValue *Unary::getExpr() const {
        return expr;
    }

    void Unary::toMermaid() {
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

    DirectRightValue *Unary::directify() {
        switch (op) {
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

    Unary *Unary::setOp(Operator _op) {
        op = _op;
        return this;
    }

    Operator Unary::getOp() const {
        return op;
    }

    Unary::Unary() : IndirectRightValue(NodeClass::UNARY) {}

    /*---------------------Variable---------------------*/
    Variable::Variable() : IndirectRightValue(NodeClass::VARIABLE) {}

    Variable *Variable::setName(const std::string &_name) {
        name = _name;
        return this;
    }

    const std::string &Variable::getName() const {
        return name;
    }

    void Variable::toMermaid() {
        size_t variable_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t name_id = getCounter();
        putLabel(name);
        putEdge(variable_id, name_id, "name");
    }

    bool Variable::isDirect() {
        return false;
    }

    DirectRightValue *Variable::directify() {
        try {
            return analyzerContext.get(this);
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        return nullptr;
    }

    /*---------------------DirectRightValueInitializer---------------------*/

    std::map<ValueType, DirectRightValue *> DirectRightValueInitializer::values = {
            {ValueType::INT_32, new Int32()},
            {ValueType::FLOAT_32, new Float32()},
            {ValueType::BOOLEAN, new Boolean()},
            {ValueType::POINTER, new Pointer()},
            {ValueType::VOID, new Void()}
    };

    DirectRightValue * DirectRightValueInitializer::get(ValueType type)
    {
        return values[type];
    }

    /*---------------------Void---------------------*/

    Void::Void() : DirectRightValue(NodeClass::VOID) {}

    void Void::toMermaid() {
        size_t void_id = getCounter();
        putLabel(getNodeClass());
        count();
        putEdge(void_id, getCounter(), "void");
    }

    ValueType Void::getValueType() {
        return ValueType::VOID;
    }

    bool Void::isVoid() {
        return true;
    }

    /*---------------------FunctionCall---------------------*/

    FunctionCall::FunctionCall() : IndirectRightValue(NodeClass::FUNCTION_CALL) {}

    FunctionCall *FunctionCall::setName(const std::string &_name) {
        name = _name;
        return this;
    }

    const std::string &FunctionCall::getName() const {
        return name;
    }

    FunctionCall *FunctionCall::setArgs(const std::vector<RightValue *> &_args) {
        args = _args;
        return this;
    }

    const std::vector<RightValue *> &FunctionCall::getArgs() const {
        return args;
    }

    void FunctionCall::toMermaid() {
        size_t function_call_id = getCounter();
        putLabel(getNodeClass());
        count();
        size_t name_id = getCounter();
        putLabel(name);
        putEdge(function_call_id, name_id, "name");
        count();
        size_t args_id = getCounter();
        for (auto &arg : args) {
            arg->toMermaid();
            putEdge(args_id, getCounter(), "arg");
            count();
        }
    }

    bool FunctionCall::isDirect() {
        return false;
    }

    /**
    * @brief 暂时没做函数调用的优化，所以直接返回一个空指针
    */
    DirectRightValue *FunctionCall::directify() {
        // // TODO: 目前返回一个空指针，后续需要实现
        // try {
        //     return DirectRightValueInitializer::get(analyzerContext.get(this));
        // } catch (std::runtime_error &e) {
        //     std::cerr << e.what() << std::endl;
        //     exit(1);
        // }
        // return nullptr;
        return nullptr;
    }




}