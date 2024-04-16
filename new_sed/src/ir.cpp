#include "ir.hpp"

namespace SED::IR{
    Var* Var::setName(const std::string& _name){
        name = _name;
        return this;
    }
    std::string Var::getName() const{
        return name;
    }
    void Var::output(){
        std::cout << "var " << name << std::endl;
    }

    Assign* Assign::setLeftVar(const std::string& _leftVar){
        leftVar = _leftVar;
        return this;
    }
    Assign* Assign::setRightVar(const std::string& _rightVar){
        rightVar = _rightVar;
        return this;
    }
    std::string Assign::getLeftVar() const{
        return leftVar;
    }
    std::string Assign::getRightVar() const{
        return rightVar;
    }
    void Assign::output(){
        std::cout << leftVar << " = " << rightVar << std::endl;
    }

    Label* Label::setName(const std::string& _name){
        name = _name;
        return this;
    }
    std::string Label::getName() const{
        return name;
    }
    void Label::output(){
        std::cout << "label " << name << std::endl;
    }

    AssignUnary* AssignUnary::setLeftVar(const std::string& _leftVar){
        leftVar = _leftVar;
        return this;
    }
    AssignUnary* AssignUnary::setRightVar(const std::string& _rightVar){
        rightVar = _rightVar;
        return this;
    }
    AssignUnary* AssignUnary::setOp(const std::string& _op){
        op = _op;
        return this;
    }
    std::string AssignUnary::getLeftVar() const{
        return leftVar;
    }
    std::string AssignUnary::getRightVar() const{
        return rightVar;
    }
    std::string AssignUnary::getOp() const{
        return op;
    }
    void AssignUnary::output(){
        std::cout << leftVar << " = " << op << rightVar << std::endl;
    }

    AssignBinary* AssignBinary::setLeftVar(const std::string& _leftVar){
        leftVar = _leftVar;
        return this;
    }
    AssignBinary* AssignBinary::setRightVar1(const std::string& _rightVar1){
        rightVar1 = _rightVar1;
        return this;
    }

    AssignBinary* AssignBinary::setRightVar2(const std::string& _rightVar2){
        rightVar2 = _rightVar2;
        return this;
    }

    AssignBinary* AssignBinary::setOp(const std::string& _op){
        op = _op;
        return this;
    }

    std::string AssignBinary::getLeftVar() const{
        return leftVar;
    }

    std::string AssignBinary::getRightVar1() const{
        return rightVar1;
    }

    std::string AssignBinary::getRightVar2() const{
        return rightVar2;
    }

    std::string AssignBinary::getOp() const{
        return op;
    }

    void AssignBinary::output(){
        std::cout << leftVar << " = " << rightVar1 << " " << op << " " << rightVar2 << std::endl;
    }


    void Start::output(){
        std::cout << "start" << std::endl;
    }

    void End::output(){
        std::cout << "end" << std::endl;
    }

    Return* Return::setVar(const std::string& _var){
        var = _var;
        return this;
    }

    std::string Return::getVar() const{
        return var;
    }

    void Return::output(){
        std::cout << "return " << var << std::endl;
    }
}
