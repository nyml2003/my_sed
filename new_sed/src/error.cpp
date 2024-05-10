#include "error.hpp"
#include "context.hpp"
#include "driver.hpp"
#include "value.hpp"
#include <fstream>
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
    locate();
    std::cerr << "| " << CodeEnumMapToString(code) << ": " << message << std::endl;
    exit(1);
}

void Error::errorWithLocation(const yy::location &l)
{
    std::ifstream targetFile(driver.sourceFileName);
    std::vector<std::string> lines;
    std::string line;
    for (int i = 0; i < l.begin.line - 1; i++)
    {
        std::getline(targetFile, line);
    }
    for (int i = l.begin.line - 1; i < l.end.line; i++)
    {
        std::getline(targetFile, line);
        lines.push_back(line);
    }
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::cerr << "|" << lines[i] << std::endl;
        std::cerr << "|";
        if (i == 0)
        {
            for (int j = 0; j < l.begin.column - 1; j++)
            {
                std::cerr << " ";
            }
            if (l.begin.line == l.end.line)
            {
                for (int j = l.begin.column - 1; j < l.end.column - 1; j++)
                {
                    std::cerr << "^";
                }
            }
            else
            {
                for (size_t j = l.begin.column - 1; j < lines[i].size(); j++)
                {
                    std::cerr << "^";
                }
            }
        }
        else if (i == lines.size() - 1)
        {
            for (int j = 0; j < l.end.column - 1; j++)
            {
                std::cerr << "^";
            }
        }
        else
        {
            for (size_t j = 0; j < lines[i].size(); j++)
            {
                std::cerr << " ";
            }
        }
        std::cerr << std::endl;
    }
    std::cerr << "| " << CodeEnumMapToString(code) << ": " << message << std::endl;
    exit(1);
}

void Error::debug()
{
    std::cout << "Debug: " << message << std::endl;
}

void Error::locate()
{
    std::ifstream targetFile(driver.sourceFileName);
    std::vector<std::string> lines;
    std::string line;
    AST::Node *node = analyzerContext.nodeStack.top();
    for (int i = 0; i < node->begin.line - 1; i++)
    {
        std::getline(targetFile, line);
    }
    for (int i = node->begin.line - 1; i < node->end.line; i++)
    {
        std::getline(targetFile, line);
        lines.push_back(line);
    }
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::cerr << "|" << lines[i] << std::endl;
        std::cerr << "|";
        if (i == 0)
        {
            for (int j = 0; j < node->begin.column - 1; j++)
            {
                std::cerr << " ";
            }
            if (node->begin.line == node->end.line)
            {
                for (int j = node->begin.column - 1; j < node->end.column - 1; j++)
                {
                    std::cerr << "^";
                }
            }
            else
            {
                for (size_t j = node->begin.column - 1; j < lines[i].size(); j++)
                {
                    std::cerr << "^";
                }
            }
        }
        else if (i == lines.size() - 1)
        {
            for (int j = 0; j < node->end.column - 1; j++)
            {
                std::cerr << "^";
            }
        }
        else
        {
            for (size_t j = 0; j < lines[i].size(); j++)
            {
                std::cerr << " ";
            }
        }
        std::cerr << std::endl;
    }
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

FunctionNoReturnValueError::FunctionNoReturnValueError(std::string function)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Function No Return Value: " + function)
{
}

UnexpectedTokenError::UnexpectedTokenError(std::string token)
    : Error(Type::ERROR, Code::SYNTAX_ERROR, "Unexpected Token: " + token)
{
}

VoidParameterError::VoidParameterError(std::string function)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "The type of parameter in function " + function + " can't be void")
{
}

FunctionCallArgumentTypeError::FunctionCallArgumentTypeError(std::string function, int index,
                                                             Enumeration::ValueType actualType,
                                                             Enumeration::ValueType predictedType)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR,
            "The type of argument " + std::to_string(index) + " in function " + function + " is predicted to be " +
                errorValueTypeWrapper(predictedType) + ", but you provide " + errorValueTypeWrapper(actualType))
{
}

FunctionOverloadError::FunctionOverloadError(std::string function)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR, "Function Overload: " + function)
{
}

FunctionCallArgumentCountError::FunctionCallArgumentCountError(std::string function, int predictedCount,
                                                               int actualCount)
    : Error(Type::ERROR, Code::SEMANTIC_ERROR,
            "The number of arguments in function " + function + " is " + std::to_string(predictedCount) +
                ", but you "
                "provide " +
                std::to_string(actualCount))

{
}

} // namespace SED::Error