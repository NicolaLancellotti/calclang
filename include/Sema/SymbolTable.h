#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <set>

namespace calclang {

    class SymbolTable {
    public:

        SymbolTable(std::shared_ptr<SymbolTable> previous) : _previous(
                previous) {}

        auto add_variable(const std::string& id) -> bool {
            if (_variables.find(id) == _variables.end()) {
                _variables.insert(id);
                return true;
            } else {
                return false;
            }
        }

        auto exist_variable(const std::string& id) -> bool {
            if (_variables.find(id) != _variables.end()) {
                return true;
            } else if (_previous != nullptr) {
                return _previous->exist_variable(id);
            } else {
                return false;
            }
        }

        auto previous() const -> const std::shared_ptr<SymbolTable> {
            return _previous;
        }

    private:
        std::set<std::string> _variables;
        std::shared_ptr<SymbolTable> _previous;
    };


    class SymbolTableManager {
    public:

        auto current() const -> const std::shared_ptr<SymbolTable> {
            return _current;
        }

        bool add_variable(const std::string& id) {
            return _current->add_variable(id);
        }

        auto exist_variable(const std::string& id) const -> bool {
            return _current->exist_variable(id);
        }

        void enter_scope() {
            _current = std::make_shared<SymbolTable>(_current);
        }

        void exit_scope() {
            _current = _current->previous();
        }

    private:
        std::shared_ptr<SymbolTable> _current;
    };

}

#endif
