#include "tc_interrupt.hpp"

extern "C" {
void __TC0_Handler(){   
    (void) TC0->TC_CHANNEL[0].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_0>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_0>::isr();
    }
}

void __TC1_Handler(){  
    (void) TC0->TC_CHANNEL[1].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_1>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_1>::isr();
    }
}

void __TC2_Handler(){
    (void) TC0->TC_CHANNEL[2].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_2>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_2>::isr();
    }
}

void __TC3_Handler() {
    (void) TC1->TC_CHANNEL[0].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_3>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_3>::isr();
    }
}

void __TC4_Handler() {
    (void) TC1->TC_CHANNEL[1].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_4>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_4>::isr();
    }
}
   
void __TC5_Handler() {
    (void) TC1->TC_CHANNEL[2].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_5>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_5>::isr();
    }
}

void __TC6_Handler() {
    (void) TC2->TC_CHANNEL[0].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_6>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_6>::isr();
    }
}

void __TC7_Handler() {
    (void) TC2->TC_CHANNEL[1].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_7>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_7>::isr();
    }
}

void __TC8_Handler() {
    (void) TC2->TC_CHANNEL[2].TC_SR;

    if (llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_8>::isr) {
        llib::target::tc::detail::_isr_store<llib::sam3x8e::tc::channel_8>::isr();
    }
}

}