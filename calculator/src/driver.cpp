//
// Created by venty on 2024/3/24.
//

#include "driver.hpp"
#include "context.hpp"


namespace SED::Driver{
    Driver::Driver(Config config) : traceParsing(config.traceParsing), traceScanning(config.traceScanning) {
    }

    void Driver::setTraceParsing(bool traceParsing) {
        this->traceParsing = traceParsing;
    }

    void Driver::setTraceScanning(bool traceScanning) {
        this->traceScanning = traceScanning;
    }

    void Driver::parse() {
        location.initialize();
        yy::parser parse(*this);
        parse.set_debug_level(traceParsing);
        
        int res = parse();
        if (res != 0) {
            std::cerr << "Parse failed" << std::endl;
        }
    }

    void Driver::error(const yy::location &l, const std::string &m) {
        std::cerr << l << ": " << m << std::endl;
    }
}