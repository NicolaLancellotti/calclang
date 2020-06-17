#ifndef COMPILER_UNREACHABLE_H
#define COMPILER_UNREACHABLE_H

#include <iostream>

namespace calclang {

    inline auto unreachable() {
        std::cerr << "unreachable" << std::endl;
        exit(EXIT_FAILURE);
    }

}

#endif