#include "Driver.h"

int main(int argc, const char*  argv[]) {
    auto driver = calclang::Driver{};
    return driver.run(argc, argv);
}
