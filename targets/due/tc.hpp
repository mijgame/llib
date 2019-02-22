#ifndef LLIB_DUE_TC_HPP
#define LLIB_DUE_TC_HPP

#include <cstdint>
#include <pio.hpp>
#include <base.hpp>

namespace llib::due{
    namespace tc{
        struct tc0{
            constexpr static uint32_t instance_id = ID_TC0;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC0_IRQn);
        };

        struct tc1{
            constexpr static uint32_t instance_id = ID_TC1;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC1_IRQn);
        };

        struct tc2{
            constexpr static uint32_t instance_id = ID_TC2;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC2_IRQn);
        };

        template<typename TC>
        Tc *const port = nullptr;

        template<>
        Tc *const port<tc0> = TC0;        

        template<>
        Tc *const port<tc1> = TC1; 

        template<>
        Tc *const port<tc2> = TC2; 
        
    }
}

#endif