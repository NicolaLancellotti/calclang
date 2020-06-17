#ifndef COMPILER_DIAGNOSTICENGINE_H
#define COMPILER_DIAGNOSTICENGINE_H

#include <Location.h>
#include "Error.h"

namespace calclang {

    class DiagnosticEngine {
    public:

        DiagnosticEngine(bool show_error): _show_error{show_error} {};

        bool is_correct() const {
            return _correct;
        }

        void undefined_variable(const Location& loc, const std::string& id) {
            _correct = false;
            if (_show_error) Error::analysis(loc, Error::UndefinedVariable, id.c_str());
        }

        void assign_to_rvalue(const Location& loc, const std::string& id) {
            _correct = false;
            if (_show_error) Error::analysis(loc, Error::AssignToRval, id.c_str());
        }

    private:
        bool _correct = true;
        bool _show_error;
    };

}

#endif
