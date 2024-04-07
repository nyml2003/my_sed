#include "driver.hpp"
int main(int argc, char* argv[]) {
    std::cout << "Usage: " << argv[0] << " <input> <output.md> <output.err> <output.ll>\n";
    std::string folderName = "/app/tests/test1/";
    std::string input = (argc == 5) ? argv[1] : folderName + "in.sy";
    std::string md = (argc == 5) ? argv[2] : folderName + "out.md";
    std::string error = (argc == 5) ? argv[3] : folderName + "out.err";
    std::string ir = (argc == 5) ? argv[4] : folderName + "out.ll";
    driver.setSourceFileName(input);
    driver.setOutputFileName(md);
    driver.setErrorFileName(error);
    driver.setTraceParsing(false);
    driver.setTraceScanning(false);
    driver.parse();
    driver.result->analyze();
    driver.result->toMermaid();
//     driver.setOutputFileName(ir);
//     driver.result->toLLVM();
    return 0;
}
