#ifndef COMPILER_NODEAST_H
#define COMPILER_NODEAST_H

#include <list>
#include "Visitor.h"
#include "Location.h"

#define ACCEPT() void accept(Visitor& visitor) { visitor.visit(*this); }
#define ACCEPT_VIRTUAL() virtual void accept(Visitor&) = 0;

namespace calclang {

    class NodeAST {
    public:
        explicit NodeAST(Location location) : _location{location} {};

        virtual ~NodeAST() = default;

        auto location() const -> const Location& {
            return _location;
        }

        ACCEPT_VIRTUAL();

    private:
        Location _location;
    };

}

#endif
