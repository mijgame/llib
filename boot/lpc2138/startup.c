#include <limits.h>
#include <stdlib.h>
#define register

#include <device_include.hpp>

/*
 * We gave 'weak' attribute, so these functions can be aliased into a single
 * function
 */
void __attribute__((weak)) __reset_handler();     /* Reset Handler */
void __attribute__((weak)) __undef_addr();        /* Undef_Addr */
void __attribute__((weak)) __software_interrupt();/* Software Interrupt Handler */
void __attribute__((weak)) __prefetch_abort();    /* Prefetch Abort Handler (instruction fetch memory fault) */
void __attribute__((weak)) __data_abort();        /* Data Abort Handler (data access memory fault) */
void __attribute__((weak)) __arm_irq();           /* IRQ Handler */
void __attribute__((weak)) __arm_fiq();           /* FIQ Handler */

int main();

void fatal_error_detected(const char *);

extern unsigned int __stack_end;
extern void __target_startup(); 

extern void *memcpy(void *destination, const void *source, size_t num);
extern void *memset(void *ptr, int value, size_t num);
 
 
void __default_handler(void);

#pragma weak __undef_addr         = __default_handler /* Undef_Addr */
#pragma weak __software_interrupt = __default_handler /* Software Interrupt Handler */
#pragma weak __prefetch_abort     = __default_handler /* Prefetch Abort Handler */
#pragma weak __data_abort         = __default_handler /* Data Abort Handler */
#pragma weak __arm_irq            = __default_handler /* IRQ Handler */
#pragma weak __arm_fiq            = __default_handler /* FIQ Handler */

void __default_handler(void) {
    while (1);
}

void __reset_handler() {
    extern unsigned int __data_init_start;
    extern unsigned int __data_start;
    extern unsigned int __data_end;
    extern unsigned int __bss_start;
    extern unsigned int __bss_end;

    // clear .bss section
    memset(&__bss_start, 0, &__bss_end - &__bss_start);

    // copy .data section from flash to ram
    memcpy(&__data_start, &__data_init_start, &__data_end - &__data_start);

    __target_startup();

    // call main
    (void) main();

    // when main returns: loop till hell freezes down
    while (1) {}
}

// junk that is not needed in an embedded context, but
// is still required to satisfy the C++ compiler
void *__dso_handle;

// handle a divide-by-zero error
// the standard library invokes abort
int __aeabi_idiv0() { return 0; }

// called when a vft entry is not yet filled in
void __cxa_pure_virtual() {}
