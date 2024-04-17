#ifndef SED_IR_HPP


#define SED_IR_HPP


#include "ast.hpp"
namespace SED::IR{
    class Statement{
        
    public:
        virtual void output() = 0;
    };

    class Var : public Statement{
        std::string name;
    public:
        Var* setName(const std::string& _name);
        std::string getName() const;
        void output() override;
    };

    class Assign : public Statement{
        std::string leftValue;
        std::string rightValue;
    public:
        Assign* setLeftValue(const std::string& _leftValue);
        Assign* setLeftValue(size_t _register_id);
        Assign* setRightValue(const std::string& _rightValue);
        Assign* setRightValue(size_t _register_id);
        std::string getLeftValue() const;
        std::string getRightValue() const;
        void output() override;
    };

    class Label : public Statement{
        std::string name;
    public:
        Label* setName(const std::string& _name);
        std::string getName() const;
        void output() override;
    };

    class AssignUnary : public Statement{
        size_t registerSource;
        size_t registerDestination;
        std::string op;
    public:
        AssignUnary* setRegisterSource(size_t _registerSource);
        AssignUnary* setRegisterDestination(size_t _registerDestination);
        AssignUnary* setOp(const std::string& _op);
        size_t getRegisterSource() const;
        size_t getRegisterDestination() const;
        std::string getOp() const;
        void output() override;
    };

    class AssignBinary : public Statement{
        std::string op;
        size_t registerSource;
        size_t registerDestination;
        size_t registerTarget;
    public:
        AssignBinary* setRegisterSource(size_t _registerSource);
        AssignBinary* setRegisterDestination(size_t _registerDestination);
        AssignBinary* setRegisterTarget(size_t _registerTarget);
        AssignBinary* setOp(const std::string& _op);
        size_t getRegisterSource() const;
        size_t getRegisterDestination() const;
        size_t getRegisterTarget() const;
        std::string getOp() const;
        void output() override;
    };

    class Start : public Statement{
    public:
        void output() override;
    };

    class End : public Statement{
    public:
        void output() override;
    };

    class Return : public Statement{
        std::string var;
    public:
        Return* setVar(const std::string& _var);
        std::string getVar() const;
        void output() override;
    };


};
inline std::vector<SED::IR::Statement *> irs;
#endif // !SED_IR_HPP