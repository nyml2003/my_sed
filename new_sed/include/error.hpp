
#ifndef SED_ERROR_DUMP_HPP
#define SED_ERROR_DUMP_HPP
#include "enumeration.hpp"
#include "location.hh"
#include <map>
#include <string>
#include <vector>
namespace SED::AST
{
class Constant;
class Variable;

} // namespace SED::AST

namespace SED::Error
{

extern std::map<Enumeration::ValueType, std::string> errorValueTypeMap;
extern std::string errorValueTypeWrapper(Enumeration::ValueType valueType);
extern std::map<Enumeration::Operator, std::string> errorOperatorMap;
extern std::string errorOperatorWrapper(Enumeration::Operator op);

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
    void errorWithLocation(const yy::location &l);
    void debug();
    void locate();
};

class TypeMismatchError : public Error
{
  public:
    explicit TypeMismatchError(Enumeration::ValueType type1, Enumeration::ValueType type2);
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
    explicit InvalidOperationError(Enumeration::ValueType type1, Enumeration::Operator op,
                                   Enumeration::ValueType type2);
    explicit InvalidOperationError(Enumeration::ValueType type1, Enumeration::Operator op);
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

// 条件语句中的条件表达式不是bool类型
class ConditionNotBoolError : public Error
{
  public:
    explicit ConditionNotBoolError(Enumeration::ValueType type);
};

class FunctionNoReturnValueError : public Error
{
  public:
    explicit FunctionNoReturnValueError(std::string function);
};

class UnexpectedTokenError : public Error
{
  public:
    explicit UnexpectedTokenError(std::string token);
};

class VoidParameterError : public Error
{
  public:
    explicit VoidParameterError(std::string function);
};

class FunctionCallArgumentTypeError : public Error
{
  public:
    explicit FunctionCallArgumentTypeError(std::string function, int index, Enumeration::ValueType actualType,
                                           Enumeration::ValueType predictedType);
};

// 不支持函数重载错误
class FunctionOverloadError : public Error
{
  public:
    explicit FunctionOverloadError(std::string function);
};

// 函数调用参数数量错误
class FunctionCallArgumentCountError : public Error
{
  public:
    explicit FunctionCallArgumentCountError(std::string function, int predictedCount, int actualCount);
};

} // namespace SED::Error

#endif // !SED_ERROR_DUMP_HPP