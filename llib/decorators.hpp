#ifndef LLIB_DECORATORS_HPP
#define LLIB_DECORATORS_HPP

#include "peripheral.hpp"

namespace llib {
    template<typename Base>
    class pin_out_toggle {
    protected:
        bool value;

    public:
        constexpr pin_out_toggle()
            : value(false) {}

        constexpr explicit pin_out_toggle(bool value)
            : value(value) {}

        constexpr void toggle() {
            value = !value;
            Base::set(value);
        }

        template<bool Val>
        constexpr void set() {
            Base::template set<Val>();
        }

        constexpr void set(const bool val) {
            Base::set(val);
        }
    };
}

#endif //LLIB_DECORATORS_HPP
