#include <limits.h>
#include <stdlib.h>
#define register

/*
 * We gave 'weak' attribute, so these functions can be aliased into a single
 * function
 */
void __attribute__((weak)) __reset_handler();     /* Reset Handler */
void __attribute__((weak)) __nmi_handler();       /* NMI Handler */
void __attribute__((weak)) __hardfault_handler(); /* Hard Fault Handler */
void __attribute__((weak)) __memmanage_handler(); /* MPU Fault Handler */
void __attribute__((weak)) __busfault_handler();  /* Bus Fault Handler */
void __attribute__((weak)) __usagefault_handler();/* Usage Fault Handler */
void __attribute__((weak)) __svc_handler();       /* SVCall Handler */
void __attribute__((weak)) __debugmon_handler();  /* Debug Monitor Handler */
void __attribute__((weak)) __pendsv_handler();    /* PendSV Handler */
void __attribute__((weak)) __systick_handler();   /* SysTick Handler */

int main();

void fatal_error_detected(const char *);

extern unsigned __stack_end();
extern void __target_startup();

extern void *memcpy(void *destination, const void *source, size_t num);
extern void *memset(void *ptr, int value, size_t num);

void (*const volatile __vectors[])(void)
__attribute__ ((section(".vectors"))) = {
                (void (*)(void)) &__stack_end,
                __reset_handler,      // The reset handler
                __nmi_handler,        // The NMI handler
                __hardfault_handler,  // The hard fault handler
                __memmanage_handler,  // The MPU fault handler
                __busfault_handler,   // The bus fault handler
                __usagefault_handler, // The usage fault handler
                0,                  // Reserved
                0,                  // Reserved
                0,                  // Reserved
                0,                  // Reserved
                __svc_handler,        // SVCall handler
                __debugmon_handler,   // Debug monitor handler
                0,                  // Reserved
                __pendsv_handler,     // The PendSV handler
                __systick_handler,    // The SysTick handler
        };

void __default_handler(void);
#pragma weak __nmi_handler        = __default_handler /* NMI handler */
#pragma weak __hardfault_handler  = __default_handler /* Hard Fault handler */
#pragma weak __memmanage_handler  = __default_handler /* MPU Fault Handler */
#pragma weak __busfault_handler   = __default_handler /* Bus Fault Handler */
#pragma weak __usagefault_handler = __default_handler /* Usage Fault Handler */
#pragma weak __svc_handler        = __default_handler /* SVCall Handler */
#pragma weak __debugmon_handler   = __default_handler /* Debug Monitor Handler */
#pragma weak __pendsv_handler     = __default_handler /* PendSV Handler */
#pragma weak __systick_handler    = __default_handler /* SysTick Handler */

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
