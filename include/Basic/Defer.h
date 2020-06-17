#ifndef COMPILER_DEFER_H
#define COMPILER_DEFER_H

namespace calclang {

    struct Defer {

        Defer(std::function<void(void)> function) : _function{function} {};

        ~Defer() {
            _function();
        }

    private:
        std::function<void(void)> _function;
    };

}
#endif
