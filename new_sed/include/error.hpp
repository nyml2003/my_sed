#ifndef SED_ERROR_DUMP_HPP
#define SED_ERROR_DUMP_HPP
#include <string>
#include <vector>
#include <map>
#include "ast.hpp"
// 1.报错信息 info warning error
// 2.报错信息的输出
// 3.错误码
namespace SED::Error
{
    class Error
    {
    protected:
        enum class Type
        {
            ERROR,
            WARNING,
            INFO,
            DEBUG
        } type;
        enum class Code
        {
            SYNTAX_ERROR,
            SEMANTIC_ERROR,
            RUNTIME_ERROR
        } code;
        explicit Error(Type type, Code code, std::string message);
        std::string message;
        static std::map<Code, std::string> CodeEnumMap;
        static std::map<Type, std::string> TypeEnumMap;
        static std::string CodeEnumMapToString(Code code);
        static std::string TypeEnumMapToString(Type type);

    public:
        void info();
        void warning();
        void error();
        void debug();
    };

    class TypeMismatchError : public Error
    {
    public:
        explicit TypeMismatchError(AST::ValueType type1, AST::ValueType type2);
    };

    class UndeclaredVariableError : public Error
    {
    public:
        explicit UndeclaredVariableError(std::string variable);
    };

    class UndeclaredFunctionError : public Error
    {
    public:
        explicit UndeclaredFunctionError(std::string function);
    };

    class InvalidOperationError : public Error
    {
    public:
        explicit InvalidOperationError(AST::ValueType type1, AST::Operator op, AST::ValueType type2);
        explicit InvalidOperationError(AST::ValueType type1, AST::Operator op);
    };

    class VariableRedeclarationError : public Error
    {
    public:
        explicit VariableRedeclarationError(std::string variable);
    };

    class FunctionRedeclarationError : public Error
    {
    public:
        explicit FunctionRedeclarationError(std::string function);
    };

    class DivisionByZeroError : public Error
    {
    public:
        explicit DivisionByZeroError();
    };

} // namespace SED::Analyzable

#endif // !SED_ERROR_DUMP_HPP