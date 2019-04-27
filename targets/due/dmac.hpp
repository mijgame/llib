#ifndef LLIB_DUE_DMAC_HPP
#define LLIB_DUE_DMAC_HPP

#include "pio.hpp"
#include "interrupt.hpp"

namespace llib::due {
    namespace dma {
        enum class mode{
            MEM_TO_MEM = 0b000,
            MEM_TO_PER = 0b001,
            PER_TO_MEM = 0b010,
            PER_TO_PER = 0b011
        };

        enum class incr{
            INCREMENTING = 0b00,
            DECREMENTING = 0b01,
            FIXED = 0b10
        };

        enum class data_width{
            BYTE = 0b00,
            HALF_WORD = 0x01,
            WORD = 0x10
        };
        
        enum class peripheral_id {
            HSMCI_TX_RX = 0,
            SPI0_TX     = 1,
            SPI0_RX     = 2,
            SSC_TX      = 3,
            SSC_RX      = 4,
            SPI1_TX     = 5,
            SPI1_RX     = 6,
            TWI0_TX     = 7,
            TWI0_RX     = 8,
            USART0_TX   = 11,
            USART0_RX   = 12,
            USART1_TX   = 13,
            USART1_RX   = 14,
            PWM_TX      = 15
        };

        class controller {
            private:
                static uint8_t _get_unused_channel(){
                    uint8_t channels = (DMAC->DMAC_CHSR & 0x3F);

                    if((channels & 0x3F) < 0x3F){
                        // channel available
                        for(uint8_t id = 0; id < max_channels; id++){
                            if(!(channels & 1 << id)){
                                // return channel that is available
                                // llib::cout << "Using Channel: " << id << '\n';
                                return id;
                            }
                        }
                    }

                    // return max amount of channels sinds we dont have a channel left
                    return max_channels;
                }  

            public:
                constexpr static uint32_t instance_id = ID_DMAC;
                constexpr static uint32_t irqn = static_cast<uint32_t>(DMAC_IRQn);
                constexpr static inline uint8_t max_channels = 6;

                static uint8_t init(){
                    if(get_clock_status<controller>()){
                        // Dmac is already initilized
                        return _get_unused_channel();
                    }

                    attach_interrupt<controller, 0x0>(nullptr);

                    // disable write protection
                    DMAC->DMAC_WPMR = DMAC_WPMR_WPKEY_PASSWD;    

                    // enable clock
                    enable_clock<controller>();          

                    // disable dmac
                    DMAC->DMAC_EN = (~DMAC_EN_ENABLE);

                    DMAC->DMAC_GCFG = DMAC_GCFG_ARB_CFG_FIXED;

                    // enable dmac
                    DMAC->DMAC_EN = DMAC_EN_ENABLE;     

                    // disable all channels
                    DMAC->DMAC_CHDR = 0x3F;

                    // enable interupts
                    DMAC->DMAC_EBCIER = 0x3f;

                    // return a unused channel
                    return _get_unused_channel();
                }

                static void enable_channel(uint8_t channel){
                    if(channel >= max_channels){
                        return;
                    }
                    // disable channel                    
                    DMAC->DMAC_CHER = 1U << channel;
                }

                static void disable_channel(uint8_t channel){
                    if(channel >= max_channels){
                        return;
                    }
                    // enable channel
                    DMAC->DMAC_CHDR = 1U << channel;
                }

                static bool transfer_is_done(uint32_t channel) {
                    if(channel >= max_channels){
                        return true;
                    }                    
                    return !(DMAC->DMAC_CHSR & (1U << channel));
                }
                
                static bool is_stalled_suspended(uint32_t channel) {
                    if(channel >= max_channels){
                        return true;
                    }                    
                    return (DMAC->DMAC_CHSR & (1U << (channel + 8) | (1U << (channel + 24))));
                }                
            };
    }
}

extern "C" {
void __DMAC_Handler(){
    llib::due::_handle_isr<llib::due::dma::controller>(
        DMAC->DMAC_EBCISR,
        DMAC->DMAC_EBCIMR
    );
}    
}

#endif //LLIB_DUE_DMAC_HPP