#include "error.hpp"
#include "value.hpp"
namespace SED::Error{
    Error::Error(Type type, Code code, std::string message) : type(type), code(code), message(message) {}

    std::map<Error::Code, std::string> Error::CodeEnumMap = {
        {Code::SYNTAX_ERROR, "Syntax Error"},
        {Code::SEMANTIC_ERROR, "Semantic Error"},
        {Code::RUNTIME_ERROR, "Runtime Error"}};

    std::map<Error::Type, std::string> Error::TypeEnumMap = {
        {Type::ERROR, "Error"},
        {Type::WARNING, "Warning"},
        {Type::INFO, "Info"},
        {Type::DEBUG, "Debug"}};

    void Error::info() {
        std::cout << "\033[34mINFO: \033[0m"<< message << std::endl;
    }

    void Error::warning() {
        std::cerr << "\033[33mWarning: \033[0m" << message << std::endl;
    }

    void Error::error() {
        std::cerr << "\033[31mError: \033[0m" << message << std::endl;
        throw std::runtime_error("This statement will never be executed");
    }

    void Error::debug() {
        std::cout << "\033[36mDebug: \033[0m" << message << std::endl;
    }

    TypeMismatchError::TypeMismatchError(AST::ValueType type1, AST::ValueType type2) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Type Mismatch: " + AST::ValueTypeEnumMapToString(type1) + " and " + AST::ValueTypeEnumMapToString(type2)) {}

    UndefinedVariableError::UndefinedVariableError(std::string variable) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Undefined Variable: " + variable) {}

    UndefinedFunctionError::UndefinedFunctionError(std::string function) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Undefined Function: " + function) {}

    InvalidOperationError::InvalidOperationError(AST::ValueType type1, AST::Operator op, AST::ValueType type2) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Invalid Operation: " + AST::ValueTypeEnumMapToString(type1) + " " + AST::OperatorEnumMapToString(op) + " " + AST::ValueTypeEnumMapToString(type2)) {}

    InvalidOperationError::InvalidOperationError(AST::ValueType type1, AST::Operator op) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Invalid Operation: " + AST::ValueTypeEnumMapToString(type1) + " " + AST::OperatorEnumMapToString(op)) {}

    VariableRedeclarationError::VariableRedeclarationError(std::string variable) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Variable Redeclaration: " + variable) {}

    FunctionRedeclarationError::FunctionRedeclarationError(std::string function) : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Function Redeclaration: " + function) {}

    DivisionByZeroError::DivisionByZeroError() : Error(Type::ERROR, Code::RUNTIME_ERROR, "Division by Zero") {}
}