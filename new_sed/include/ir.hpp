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
        std::string leftVar;
        std::string rightVar;
    public:
        Assign* setLeftVar(const std::string& _leftVar);
        Assign* setRightVar(const std::string& _rightVar);
        std::string getLeftVar() const;
        std::string getRightVar() const;
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
        std::string leftVar;
        std::string rightVar;
        std::string op;
    public:
        AssignUnary* setLeftVar(const std::string& _leftVar);
        AssignUnary* setRightVar(const std::string& _rightVar);
        AssignUnary* setOp(const std::string& _op);
        std::string getLeftVar() const;
        std::string getRightVar() const;
        std::string getOp() const;
        void output() override;
    };

    class AssignBinary : public Statement{
        std::string leftVar;
        std::string rightVar1;
        std::string rightVar2;
        std::string op;
    public:
        AssignBinary* setLeftVar(const std::string& _leftVar);
        AssignBinary* setRightVar1(const std::string& _rightVar1);
        AssignBinary* setRightVar2(const std::string& _rightVar2);
        AssignBinary* setOp(const std::string& _op);
        std::string getLeftVar() const;
        std::string getRightVar1() const;
        std::string getRightVar2() const;
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