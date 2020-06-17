#ifndef COMPILER_STORE_H
#define COMPILER_STORE_H

#include <map>

namespace calclang {

    class Store {
    public:

        Store(std::shared_ptr<Store> previous) : _previous(previous) {}

        auto set_variable_value(const std::string& id, int value) -> void {
            if (int* pvalue = variable_value(id)) {
                *pvalue = value;
            } else {
                _variables[id] = value;
            }
        }

        auto variable_value(const std::string& id) -> int* {
            if (_variables.find(id) != _variables.end()) {
                return &_variables[id];
            } else if (_previous != nullptr) {
                return _previous->variable_value(id);
            } else {
                return nullptr;
            }
        }

        auto previous() const -> const std::shared_ptr<Store> {
            return _previous;
        }

    private:
        std::map<std::string, int> _variables;
        std::shared_ptr<Store> _previous;
    };

    class StoreManager {
    public:

        auto current() const -> const std::shared_ptr<Store> {
            return _current;
        }

        auto set_variable_value(const std::string& id, int value) -> void {
            _current->set_variable_value(id, value);
        }

        auto variable_value(const std::string& id) -> int {
            return *_current->variable_value(id);
        }

        void enter_scope() {
            _current = std::make_shared<Store>(_current);
        }

        void exit_scope() {
            _current = _current->previous();
        }

    private:
        std::shared_ptr<Store> _current;
    };

}

#endif
