#include "tc_interrupt.hpp"
#include "stream.hpp"

extern "C" {
void __TC0_Handler(){   
    (void) TC0->TC_CHANNEL[0].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::due::tc::channel_0>::isr) {
        llib::target::tc::detail::_isr_store<llib::due::tc::channel_0>::isr();
    }
}

void __TC1_Handler(){  
    (void) TC0->TC_CHANNEL[1].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::due::tc::channel_1>::isr) {
        llib::target::tc::detail::_isr_store<llib::due::tc::channel_1>::isr();
    }
}

void __TC2_Handler(){    
    llib::due::_handle_isr<llib::due::tc::channel_2>(
        TC0->TC_CHANNEL[2].TC_SR,
        TC0->TC_CHANNEL[2].TC_IMR
    );
}

void __TC3_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_3>(
        TC1->TC_CHANNEL[0].TC_SR,
        TC1->TC_CHANNEL[0].TC_IMR
    );
}

void __TC4_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_4>(
        TC1->TC_CHANNEL[1].TC_SR,
        TC1->TC_CHANNEL[1].TC_IMR
    );
}
   
void __TC5_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_5>(
        TC1->TC_CHANNEL[2].TC_SR,
        TC1->TC_CHANNEL[2].TC_IMR
    );
}

void __TC6_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_6>(
        TC2->TC_CHANNEL[0].TC_SR,
        TC2->TC_CHANNEL[0].TC_IMR
    );
}

void __TC7_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_7>(
        TC2->TC_CHANNEL[1].TC_SR,
        TC2->TC_CHANNEL[1].TC_IMR
    );
}

void __TC8_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_8>(
        TC2->TC_CHANNEL[2].TC_SR,
        TC2->TC_CHANNEL[2].TC_IMR
    );
}

}