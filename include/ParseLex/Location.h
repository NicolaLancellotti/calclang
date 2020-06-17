#ifndef COMPILER_LOCATION_H
#define COMPILER_LOCATION_H

#include "location.hh"

namespace calclang {

    using Location = yy::location;

    inline auto location_to_string(const Location& location) -> std::string {
        auto file_name = location.begin.filename;
        return (file_name != nullptr ? *file_name + ":" : "") +
               std::to_string(location.begin.line) + ":" +
               std::to_string(location.begin.column);
    }

}

#endif