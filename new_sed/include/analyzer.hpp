#ifndef SED_ANALYZER
#define SED_ANALYZER

namespace SED::Analyzer
{
    class Analyzable
    {
    public:
        virtual void analyze() = 0;
    };
}

#endif // !SED_ANALYZER