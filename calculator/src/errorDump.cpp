#include "errorDump.hpp"
namespace SED::Error{
    std::string to_string(const ErrorType errorType)
    {
        switch (errorType)
        {
        case ErrorType::ERROR:
            return "ERROR";
        case ErrorType::WARNING:
            return "WARNING";
        case ErrorType::INFO:
            return "INFO";
        default:
            return "UNKNOWN";
        }
    }
}