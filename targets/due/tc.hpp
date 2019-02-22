#ifndef LLIB_DUE_TC_HPP
#define LLIB_DUE_TC_HPP

#include <base.hpp>

namespace llib::due{
    namespace tc{
        struct tc0 {};

        struct tc1 {};

        struct tc2 {};

        struct tioa {}; // I/O line A

        struct tiob {}; // I/O line B

        struct tclk {}; // External Clock Input

        struct channel_0{
            using timer = tc0;
            constexpr static uint32_t instance_id = ID_TC0;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC0_IRQn);
        };

        struct channel_1{
            using timer = tc0;
            constexpr static uint32_t instance_id = ID_TC1;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC1_IRQn);
        };

        struct channel_2{
            using timer = tc0;
            constexpr static uint32_t instance_id = ID_TC2;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC2_IRQn);
        };

        struct channel_3{
            using timer = tc1;
            constexpr static uint32_t instance_id = ID_TC3;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC3_IRQn);
        };

        struct channel_4{
            using timer = tc1;
            constexpr static uint32_t instance_id = ID_TC4;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC4_IRQn);
        };

        struct channel_5{
            using timer = tc1;
            constexpr static uint32_t instance_id = ID_TC5;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC5_IRQn);
        };

        struct channel_6{
            using timer = tc2;
            constexpr static uint32_t instance_id = ID_TC6;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC6_IRQn);
        };

        struct channel_7{
            using timer = tc2;
            constexpr static uint32_t instance_id = ID_TC7;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC7_IRQn);
        };

        struct channel_8{
            using timer = tc2;
            constexpr static uint32_t instance_id = ID_TC8;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TC8_IRQn);
        };

        template<typename TC>
        Tc *const port = nullptr;

        template<>
        Tc *const port<tc0> = TC0;        

        template<>
        Tc *const port<tc1> = TC1; 

        template<>
        Tc *const port<tc2> = TC2; 

        enum class clock_selection{
            TIMER_CLOCK1,
            TIMER_CLOCK2,
            TIMER_CLOCK3,
            TIMER_CLOCK4,
            TIMER_CLOCK5,
            XC0,
            XC1,
            XC2
        };

        enum class clock_and{
            NONE,
            XC0,
            XC1,
            XC2
        };

        enum class edge_selection{
            NONE,
            RISING,
            FALLING,
            EDGE
        };
    }
}

#endif
