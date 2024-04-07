#ifndef SED_ANALYZER_HPP
#define SED_ANALYZER_HPP

namespace SED
{
    class Analyzable
    {
        public:
        virtual void analyze() = 0;
    };
} // namespace SED::Analyzable

#endif // !SED_ANALYZER_HPP