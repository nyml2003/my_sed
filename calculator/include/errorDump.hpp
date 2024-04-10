#ifndef SED_ERROR_DUMP_HPP
#define SED_ERROR_DUMP_HPP
#include <string>
#include <vector>
namespace SED::Error
{
    enum class ErrorType
    {
        ERROR,
        WARNING,
        INFO
    };
    std::string to_string(const ErrorType errorType);

    class ErrorDump
    {
    public:
        virtual void dump(const std::string &message, ErrorType errorType = ErrorType::ERROR) = 0;
    };
} // namespace SED::Analyzable

#endif // !SED_ERROR_DUMP_HPP