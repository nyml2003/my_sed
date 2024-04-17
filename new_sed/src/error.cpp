#include "error.hpp"
#include "value.hpp"
namespace SED::Error
{
    Error::Error(Type type, Code code, std::string message) : type(type), code(code), message(message) {}

    std::map<Error::Code, std::string> Error::CodeEnumMap = {
        {Code::SYNTAX_ERROR, "Syntax Error"},
        {Code::SEMANTIC_ERROR, "Semantic Error"},
        {Code::RUNTIME_ERROR, "Runtime Error"}};

    std::string Error::CodeEnumMapToString(Code code)
    {
        return CodeEnumMap[code];
    }

    std::map<Error::Type, std::string> Error::TypeEnumMap = {
        {Type::ERROR, "Error"},
        {Type::WARNING, "Warning"},
        {Type::INFO, "Info"},
        {Type::DEBUG, "Debug"}};

    std::string Error::TypeEnumMapToString(Type type)
    {
        return TypeEnumMap[type];
    }

    void Error::info()
    {
        std::cout << "\033[34mINFO: \033[0m" << message << std::endl;
    }

    void Error::warning()
    {
        std::cerr << "\033[33mWarning: \033[0m" << message << std::endl;
    }

    void Error::error()
    {
        std::cerr << "\033[31m" << CodeEnumMapToString(code) << ": \033[0m" << message << std::endl;
        exit(1);
    }

    void Error::debug()
    {
        std::cout << "\033[36mDebug: \033[0m" << message << std::endl;
    }

    TypeMismatchError::TypeMismatchError(AST::ValueType type1, AST::ValueType type2) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Type Mismatch: the statement trys to assign a " + AST::ValueTypeEnumMapToString(type2) + " value to a " + AST::ValueTypeEnumMapToString(type1) + " variable") {}

    UndeclaredVariableError::UndeclaredVariableError(std::string variable) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Undeclared Variable: " + variable) {}

    UndeclaredFunctionError::UndeclaredFunctionError(std::string function) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Undeclared Function: " + function) {}

    InvalidOperationError::InvalidOperationError(AST::ValueType type1, AST::Operator op, AST::ValueType type2) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Invalid Operation: " + AST::ValueTypeEnumMapToString(type1) + " " + AST::OperatorEnumMapToString(op) + " " + AST::ValueTypeEnumMapToString(type2)) {}

    InvalidOperationError::InvalidOperationError(AST::ValueType type1, AST::Operator op) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Invalid Operation: " + AST::ValueTypeEnumMapToString(type1) + " " + AST::OperatorEnumMapToString(op)) {}

    VariableRedeclarationError::VariableRedeclarationError(std::string variable) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Variable Redeclaration: " + variable) {}

    FunctionRedeclarationError::FunctionRedeclarationError(std::string function) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Function Redeclaration: " + function) {}

    DivisionByZeroError::DivisionByZeroError() : Error(Type::ERROR, Code::RUNTIME_ERROR, "Division by Zero") {}
}