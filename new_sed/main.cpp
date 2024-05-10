#include "basicBlock.hpp"
#include "driver.hpp"
int main(int argc, char *argv[])
{
    std::string folderName = "/app/tests/test5/";
    std::string input = (argc == 6) ? argv[1] : folderName + "in.sy";
    std::string md = (argc == 6) ? argv[2] : folderName + "out.md";
    std::string error = (argc == 6) ? argv[3] : folderName + "out.err";
    std::string ir = (argc == 6) ? argv[4] : folderName + "out.ir";
    std::string block = (argc == 6) ? argv[5] : folderName + "block.md";
    driver.setSourceFileName(input);
    driver.setOutputFileName(md);
    driver.setErrorFileName(error);
    driver.setTraceParsing(false);
    driver.setTraceScanning(false);
    driver.parse();
    driver.result->analyze();
    driver.result->toMermaid();
    driver.setOutputFileName(ir);
    driver.result->toIR();
    driver.setOutputFileName(block);
    SED::IR::BasicBlockManager *bbm = new SED::IR::BasicBlockManager();
    bbm->load(irs);
    bbm->buildCFG();
    bbm->toMermaid();

    //     driver.setOutputFileName(ir);
    //     driver.result->toLLVM();
    return 0;
}
