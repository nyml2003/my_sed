#include "ir.hpp"

namespace SED::IR
{

void Statement::output()
{
    ;
}

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
    std::cout << "\tvar " << name;
    Statement::output();
    std::cout << std::endl;
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
    std::cout << "\t" << leftValue << " = " << rightValue;
    Statement::output();
    std::cout << std::endl;
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
    std::cout << "label " << name;
    Statement::output();
    std::cout << std::endl;
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
    std::cout << "\t%" << registerDestination << " = " << op << " %" << registerSource;
    Statement::output();
    std::cout << std::endl;
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
              << "%" << registerTarget;
    Statement::output();
    std::cout << std::endl;
}

void Start::output()
{
    std::cout << "\tstart";
    Statement::output();
    std::cout << std::endl;
}

void End::output()
{
    std::cout << "\tend";
    Statement::output();
    std::cout << std::endl;
}

Return *Return::setRegisterSource(size_t _registerSource)
{
    registerSource = _registerSource;
    return this;
}

size_t Return::getRegisterSource() const
{
    return registerSource;
}

void Return::output()
{
    std::cout << "\treturn "
              << "%" << registerSource;
    Statement::output();
    std::cout << std::endl;
}

void Goto::output()
{
    std::cout << "\tgoto " << label;
    Statement::output();
    std::cout << std::endl;
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
              << "%" << registerSource << " goto L" << label;
    Statement::output();
    std::cout << std::endl;
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

Parameter *Parameter::setName(const std::string &_name)
{
    name = _name;
    return this;
}

std::string Parameter::getName() const
{
    return name;
}

void Parameter::output()
{
    std::cout << "\tparameter " << name;
    Statement::output();
    std::cout << std::endl;
}

AssignCall *AssignCall::setRegisterDestination(size_t _registerDestination)
{
    registerDestination = _registerDestination;
    return this;
}

AssignCall *AssignCall::setFunction(const std::string &_function)
{
    function = _function;
    return this;
}

size_t AssignCall::getRegisterDestination() const
{
    return registerDestination;
}

std::string AssignCall::getFunction() const
{
    return function;
}

void AssignCall::output()
{
    std::cout << "\t%" << registerDestination << " = call " << function;
    Statement::output();
    std::cout << std::endl;
}

Argument *Argument::setRegisterSource(size_t _registerSource)
{
    registerSource = _registerSource;
    return this;
}

size_t Argument::getRegisterSource() const
{
    return registerSource;
}

void Argument::output()
{
    std::cout << "\targument %" << registerSource;
    Statement::output();
    std::cout << std::endl;
}

std::vector<std::vector<Statement *>> splitBasicBlocks(const std::vector<Statement *> &irs)
{
    std::vector<std::vector<Statement *>> basicBlocks;
    std::vector<Statement *> basicBlock;
    std::map<std::string, size_t> labelToIndex;
    for (size_t i = 0; i < irs.size(); i++)
    {
        if (dynamic_cast<Label *>(irs[i]) != nullptr)
        {
            if (!basicBlock.empty())
            {
                basicBlocks.push_back(basicBlock);
                basicBlock.clear();
            }
        }
        basicBlock.push_back(irs[i]);
    }
    if (!basicBlock.empty())
    {
        basicBlocks.push_back(basicBlock);
    }
    return basicBlocks;
}
void outputBasicBlocks(const std::vector<std::vector<Statement *>> &basicBlocks)
{
    for (size_t i = 0; i < basicBlocks.size(); i++)
    {
        std::cout << "Basic Block " << i << std::endl;
        for (size_t j = 0; j < basicBlocks[i].size(); j++)
        {
            basicBlocks[i][j]->output();
        }
    }
}
} // namespace SED::IR
