#include "ir.hpp"

namespace SED::IR
{
Var *Var::setName(const std::string &_name)
{
    name = _name;
    return this;
}
std::string Var::getName() const
{
    return name;
}
void Var::output()
{
    std::cout << "\tvar " << name << std::endl;
}

Assign *Assign::setLeftValue(const std::string &_leftValue)
{
    leftValue = _leftValue;
    return this;
}

Assign *Assign::setLeftValue(size_t _register_id)
{
    leftValue = "%" + std::to_string(_register_id);
    return this;
}

Assign *Assign::setRightValue(const std::string &_rightValue)
{
    rightValue = _rightValue;
    return this;
}

Assign *Assign::setRightValue(size_t _register_id)
{
    rightValue = "%" + std::to_string(_register_id);
    return this;
}

std::string Assign::getLeftValue() const
{
    return leftValue;
}

std::string Assign::getRightValue() const
{
    return rightValue;
}

void Assign::output()
{
    std::cout << "\t" << leftValue << " = " << rightValue << std::endl;
}

Label *Label::setName(const std::string &_name)
{
    name = _name;
    return this;
}

std::string Label::getName() const
{
    return name;
}

void Label::output()
{
    std::cout << "label " << name << std::endl;
}

AssignUnary *AssignUnary::setRegisterSource(size_t _registerSource)
{
    registerSource = _registerSource;
    return this;
}

AssignUnary *AssignUnary::setRegisterDestination(size_t _registerDestination)
{
    registerDestination = _registerDestination;
    return this;
}

AssignUnary *AssignUnary::setOp(const std::string &_op)
{
    op = _op;
    return this;
}

size_t AssignUnary::getRegisterSource() const
{
    return registerSource;
}

size_t AssignUnary::getRegisterDestination() const
{
    return registerDestination;
}

std::string AssignUnary::getOp() const
{
    return op;
}

void AssignUnary::output()
{
    std::cout << "\t%" << registerDestination << " = " << op << " %" << registerSource << std::endl;
}

AssignBinary *AssignBinary::setRegisterSource(size_t _registerSource)
{
    registerSource = _registerSource;
    return this;
}

AssignBinary *AssignBinary::setRegisterDestination(size_t _registerDestination)
{
    registerDestination = _registerDestination;
    return this;
}

AssignBinary *AssignBinary::setRegisterTarget(size_t _registerTarget)
{
    registerTarget = _registerTarget;
    return this;
}

AssignBinary *AssignBinary::setOp(const std::string &_op)
{
    op = _op;
    return this;
}

size_t AssignBinary::getRegisterSource() const
{
    return registerSource;
}

size_t AssignBinary::getRegisterDestination() const
{
    return registerDestination;
}

size_t AssignBinary::getRegisterTarget() const
{
    return registerTarget;
}

std::string AssignBinary::getOp() const
{
    return op;
}
void AssignBinary::output()
{
    std::cout << "\t%" << registerDestination << " = "
              << "%" << registerSource << " " << op << " "
              << "%" << registerTarget << std::endl;
}

void Start::output()
{
    std::cout << "\tstart" << std::endl;
}

void End::output()
{
    std::cout << "\tend" << std::endl;
}

Return *Return::setVar(const std::string &_var)
{
    var = _var;
    return this;
}

std::string Return::getVar() const
{
    return var;
}

void Return::output()
{
    std::cout << "\treturn " << var << std::endl;
}

void Goto::output()
{
    std::cout << "\tgoto " << label << std::endl;
}

Goto *Goto::setLabel(const std::string &_label)
{
    label = _label;
    return this;
}

std::string Goto::getLabel() const
{
    return label;
}

void Ifz::output()
{
    std::cout << "\tifz "
              << "%" << registerSource << " goto L" << label << std::endl;
}

Ifz *Ifz::setRegisterSource(size_t _registerSource)
{
    registerSource = _registerSource;
    return this;
}

Ifz *Ifz::setLabel(size_t _label)
{
    label = _label;
    return this;
}

size_t Ifz::getRegisterSource() const
{
    return registerSource;
}

size_t Ifz::getLabel() const
{
    return label;
}

} // namespace SED::IR
