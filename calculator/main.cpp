#include "driver.hpp"
int main(int argc, char* argv[]) {
    driver.setTraceParsing(false);
    driver.setTraceScanning(false);
    driver.parse();
    return 0;
}
