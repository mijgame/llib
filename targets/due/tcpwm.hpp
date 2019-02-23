#ifndef LLIB_DUE_TCPWM_HPP
#define LLIB_DUE_TCPWM_HPP

#include <cstdint>
#include <tc.hpp>
#include <peripheral.hpp>
#include <interrupt.hpp>
#include <type_traits>

namespace llib::due{
    template<typename Pin>
    class pin_tc{
        private:
            constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
            static inline uint32_t freq = 0;

        public:
            template<uint32_t frequency = 10000>
            static void init(){
                // create pointer to channel
                TcChannel * T_ch = &(tc::port<typename Pin::timer_channel::timer>->TC_CHANNEL[Pin::timer_channel::channel]);

                // remove write protect from TC
                tc::port<typename Pin::timer_channel::timer>->TC_WPMR = TC_WPMR_WPKEY_PASSWD;     

                if constexpr (!std::is_same_v<typename Pin::timer_pin, tc::tclk>){
                    if(!get_clock_status<typename Pin::timer_channel>()){
                        // enable peripheral clock
                        enable_clock<typename Pin::timer_channel>();

                        // disable tc clock
                        T_ch->TC_CCR = TC_CCR_CLKDIS;

                        // disable interrupts on channel
                        T_ch->TC_IDR = ~0x0;

                        // clear status registers
                        T_ch->TC_SR;

                        T_ch->TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVE | 
                                    TC_CMR_WAVSEL_UP_RC | TC_CMR_EEVT_XC0 | TC_CMR_ACPA_CLEAR | 
                                    TC_CMR_ACPC_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR;

                        // set frequency
                        set_frequency<frequency>();
                    }

                    // clear output
                    set<0x0>();

                    // setup peripheral
                    set_peripheral<Pin>();

                    // enable channel clock
                    T_ch->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

                } else {
                    // TODO: implement TCLK of tc
                }        
            }

            template<uint32_t frequency>
            static void set_frequency(){
                tc::port<typename Pin::timer_channel::timer>->
                    TC_CHANNEL[Pin::timer_channel::channel].TC_RC = (variant_mck / 2) / frequency;

                // set frequency for set function
                freq = (variant_mck / 2) / frequency;                
            }

            static void set_frequency(uint32_t frequency){
                tc::port<typename Pin::timer_channel::timer>->
                    TC_CHANNEL[Pin::timer_channel::channel].TC_RC = (variant_mck / 2) / frequency;

                // set frequency for set function
                freq = (variant_mck / 2) / frequency;
            }

            template<uint8_t value>
            static void set(){
                if constexpr(std::is_same_v<typename Pin::timer_pin, tc::tclk>){
                    // cant set a tclk pin sinds it is only an input
                    return;
                }
                
                // create pointer to channel
                TcChannel * T_ch = &(tc::port<typename Pin::timer_channel::timer>->TC_CHANNEL[Pin::timer_channel::channel]);

                if constexpr(std::is_same_v<typename Pin::timer_pin, tc::tioa>){
                    if constexpr (value){
                        T_ch->TC_RA = (value * freq) / 0xFF;
                        T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk)) | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET;
                    } else {
                         T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk)) | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR;
                    }
                } 
                else if(std::is_same_v<typename Pin::timer_pin, tc::tiob>){
                    if constexpr (value){
                        T_ch->TC_RB = (value * freq) / 0xFF;
                        T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk)) | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_SET;                   
                    } else {
                        T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk)) | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR;            
                    }
                }
            }

            static void set(const uint8_t value){
                if constexpr(std::is_same_v<Pin::timer_pin, tc::tclk>){
                    // cant set a tclk pin sinds it is only an input
                    return;
                }

                // create pointer to channel
                TcChannel * T_ch = &(tc::port<typename Pin::timer_channel::timer>->TC_CHANNEL[Pin::timer_channel::channel]);

                if constexpr(std::is_same_v<typename Pin::timer_pin, tc::tioa>){
                    if (value){
                        T_ch->TC_RA = (value * freq) / 0xFF;
                        T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk)) | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET;
                    } else {
                        T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk)) | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR;
                    }
                } 
                else if(std::is_same_v<typename Pin::timer_pin, tc::tiob>){
                    if (value){
                        T_ch->TC_RB = (value * freq) / 0xFF;
                        T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk)) | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_SET;                   
                    } else {
                        T_ch->TC_CMR = (T_ch->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk)) | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR;            
                    }             
                }
            }
    };
}

extern "C" {
void __TC0_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_0>(
        TC0->TC_CHANNEL[0].TC_SR,
        TC0->TC_CHANNEL[0].TC_IMR
    );
}

void __TC1_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_1>(
        TC0->TC_CHANNEL[1].TC_SR,
        TC0->TC_CHANNEL[1].TC_IMR
    );
}

void __TC2_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_2>(
        TC0->TC_CHANNEL[2].TC_SR,
        TC0->TC_CHANNEL[2].TC_IMR
    );
}

void __TC3_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_3>(
        TC1->TC_CHANNEL[0].TC_SR,
        TC1->TC_CHANNEL[0].TC_IMR
    );
}

void __TC4_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_4>(
        TC1->TC_CHANNEL[1].TC_SR,
        TC1->TC_CHANNEL[1].TC_IMR
    );
}

void __TC5_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_5>(
        TC1->TC_CHANNEL[2].TC_SR,
        TC1->TC_CHANNEL[2].TC_IMR
    );
}

void __TC6_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_6>(
        TC2->TC_CHANNEL[0].TC_SR,
        TC2->TC_CHANNEL[0].TC_IMR
    );
}

void __TC7_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_7>(
        TC2->TC_CHANNEL[1].TC_SR,
        TC2->TC_CHANNEL[1].TC_IMR
    );
}

void __TC8_Handler(){
    llib::due::_handle_isr<llib::due::tc::channel_8>(
        TC2->TC_CHANNEL[2].TC_SR,
        TC2->TC_CHANNEL[2].TC_IMR
    );
}

}

#endif
