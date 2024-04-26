#include "error.hpp"
#include "value.hpp"
namespace SED::Error
{

std::map<Enumeration::ValueType, std::string> ValueTypeEnumMap = {{Enumeration::ValueType::INT_32, "int32"},
                                                                  {Enumeration::ValueType::FLOAT_32, "float32"},
                                                                  {Enumeration::ValueType::BOOLEAN, "bool"},
                                                                  {Enumeration::ValueType::VOID, "void"},
                                                                  {Enumeration::ValueType::CHAR, "char"}};

std::string errorValueTypeWrapper(Enumeration::ValueType type)
{
    return ValueTypeEnumMap[type];
}

std::map<Enumeration::Operator, std::string> OperatorEnumMap = {
    {Enumeration::Operator::ADD, "+"}, {Enumeration::Operator::SUB, "-"}, {Enumeration::Operator::MUL, "*"},
    {Enumeration::Operator::DIV, "/"}, {Enumeration::Operator::MOD, "%"}, {Enumeration::Operator::AND, "&&"},
    {Enumeration::Operator::OR, "||"}, {Enumeration::Operator::NOT, "!"}, {Enumeration::Operator::EQ, "=="},
    {Enumeration::Operator::NE, "!="}, {Enumeration::Operator::LT, "<"},  {Enumeration::Operator::LE, "<="},
    {Enumeration::Operator::GT, ">"},  {Enumeration::Operator::GE, ">="}};

std::string errorOperatorWrapper(Enumeration::Operator op)
{
    return OperatorEnumMap[op];
}

std::map<Error::Code, std::string> Error::CodeEnumMap = {{Code::SYNTAX_ERROR, "Syntax Error"},
                                                         {Code::SEMANTIC_ERROR, "Semantic Error"},
                                                         {Code::RUNTIME_ERROR, "Runtime Error"}};

std::string Error::CodeEnumMapToString(Code code)
{
    return CodeEnumMap[code];
}

std::map<Error::Type, std::string> Error::TypeEnumMap = {
    {Type::ERROR, "Error"}, {Type::WARNING, "Warning"}, {Type::INFO, "Info"}, {Type::DEBUG, "Debug"}};

std::string Error::TypeEnumMapToString(Type type)
{
    return TypeEnumMap[type];
}

void Error::info()
{
    std::cout << "INFO: " << message << std::endl;
}

void Error::warning()
{
    std::cerr << "Warning: " << message << std::endl;
}

void Error::error()
{
    std::cerr << CodeEnumMapToString(code) << ": " << message << std::endl;
    exit(1);
}

void Error::debug()
{
    std::cout << "Debug: " << message << std::endl;
}

Error::Error(Type type, Code code, std::string message) : type(type), code(code), message(message)
{
}

TypeMismatchError::TypeMismatchError(Enumeration::ValueType type1, Enumeration::ValueType type2)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR,
            "Type Mismatch: " + errorValueTypeWrapper(type1) + " and " + errorValueTypeWrapper(type2))
{
}

UndeclaredVariableError::UndeclaredVariableError(std::string variable)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Undeclared Variable: " + variable)
{
}

UndeclaredFunctionError::UndeclaredFunctionError(std::string function)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Undeclared Function: " + function)
{
}

InvalidOperationError::InvalidOperationError(Enumeration::ValueType type1, Enumeration::Operator op,
                                             Enumeration::ValueType type2)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR,
            "Invalid Operation: " + errorValueTypeWrapper(type1) + " " + errorOperatorWrapper(op) + " " +
                errorValueTypeWrapper(type2))
{
}

InvalidOperationError::InvalidOperationError(Enumeration::ValueType type1, Enumeration::Operator op)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR,
            "Invalid Operation: " + errorValueTypeWrapper(type1) + " " + errorOperatorWrapper(op))
{
}

VariableRedeclarationError::VariableRedeclarationError(std::string variable)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Variable Redeclaration: " + variable)
{
}

FunctionRedeclarationError::FunctionRedeclarationError(std::string function)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Function Redeclaration: " + function)
{
}

DivisionByZeroError::DivisionByZeroError() : Error(Type::ERROR, Code::RUNTIME_ERROR, "Division by Zero")
{
}

ConditionNotBoolError::ConditionNotBoolError(Enumeration::ValueType type)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Condition Not Bool: " + errorValueTypeWrapper(type))
{
}
} // namespace SED::Error