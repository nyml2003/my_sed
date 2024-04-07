#ifndef SED_ERROR_DUMP_HPP
#define SED_ERROR_DUMP_HPP

namespace SED
{
    class ErrorDump
    {
    public:
        virtual void dump(const std::string &message) = 0;
    };
} // namespace SED::Analyzable

#endif // !SED_ERROR_DUMP_HPP