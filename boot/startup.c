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

/* Peripherals handlers */
void __attribute__((weak)) __SUPC_Handler();    /*  0 Supply Controller (SUPC) */
void __attribute__((weak)) __RSTC_Handler();    /*  1 Reset Controller (RSTC) */
void __attribute__((weak)) __RTC_Handler();     /*  2 Real Time Clock (RTC) */
void __attribute__((weak)) __RTT_Handler();     /*  3 Real Time Timer (RTT) */
void __attribute__((weak)) __WDT_Handler();     /*  4 Watchdog Timer (WDT) */
void __attribute__((weak)) __PMC_Handler();     /*  5 Power Management Controller (PMC) */
void __attribute__((weak)) __EFC0_Handler();    /*  6 Enhanced Flash Controller 0 (EFC0) */
void __attribute__((weak)) __EFC1_Handler();    /*  7 Enhanced Flash Controller 1 (EFC1) */
void __attribute__((weak)) __UART_Handler();    /*  8 Universal Asynchronous Receiver Transceiver (UART) */
void __attribute__((weak)) __SMC_Handler();     /*  9 Static Memory Controller (SMC) */
                                                /* 10 not used */
void __attribute__((weak)) __PIOA_Handler();    /* 11 Parallel I/O Controller A, (PIOA) */
void __attribute__((weak)) __PIOB_Handler();    /* 12 Parallel I/O Controller B (PIOB) */
void __attribute__((weak)) __PIOC_Handler();    /* 13 Parallel I/O Controller C (PIOC) */
void __attribute__((weak)) __PIOD_Handler();    /* 14 Parallel I/O Controller D (PIOD) */
                                                /* 15 not used */
                                                /* 16 not used */
void __attribute__((weak)) __USART0_Handler();  /* 17 USART 0 (USART0) */
void __attribute__((weak)) __USART1_Handler();  /* 18 USART 1 (USART1) */
void __attribute__((weak)) __USART2_Handler();  /* 19 USART 2 (USART2) */
void __attribute__((weak)) __USART3_Handler();  /* 20 USART 3 (USART3) */
void __attribute__((weak)) __HSMCI_Handler();   /* 21 Multimedia Card Interface (HSMCI) */
void __attribute__((weak)) __TWI0_Handler();    /* 22 Two-Wire Interface 0 (TWI0) */
void __attribute__((weak)) __TWI1_Handler();    /* 23 Two-Wire Interface 1 (TWI1) */
void __attribute__((weak)) __SPI0_Handler();    /* 24 Serial Peripheral Interface (SPI0) */
                                                /* 25 not used */
void __attribute__((weak)) __SSC_Handler();     /* 26 Synchronous Serial Controller (SSC) */
void __attribute__((weak)) __TC0_Handler();     /* 27 Timer Counter 0 (TC0) */
void __attribute__((weak)) __TC1_Handler();     /* 28 Timer Counter 1 (TC1) */
void __attribute__((weak)) __TC2_Handler();     /* 29 Timer Counter 2 (TC2) */
void __attribute__((weak)) __TC3_Handler();     /* 30 Timer Counter 3 (TC3) */
void __attribute__((weak)) __TC4_Handler();     /* 31 Timer Counter 4 (TC4) */
void __attribute__((weak)) __TC5_Handler();     /* 32 Timer Counter 5 (TC5) */
void __attribute__((weak)) __TC6_Handler();     /* 33 Timer Counter 6 (TC6) */
void __attribute__((weak)) __TC7_Handler();     /* 34 Timer Counter 7 (TC7) */
void __attribute__((weak)) __TC8_Handler();     /* 35 Timer Counter 8 (TC8) */
void __attribute__((weak)) __PWM_Handler();     /* 36 Pulse Width Modulation Controller (PWM) */
void __attribute__((weak)) __ADC_Handler();     /* 37 ADC Controller (ADC) */
void __attribute__((weak)) __DACC_Handler();    /* 38 DAC Controller (DACC) */
void __attribute__((weak)) __DMAC_Handler();    /* 39 DMA Controller (DMAC) */
void __attribute__((weak)) __UOTGHS_Handler();  /* 40 USB OTG High Speed (UOTGHS) */
void __attribute__((weak)) __TRNG_Handler();    /* 41 True Random Number Generator (TRNG) */
void __attribute__((weak)) __EMAC_Handler();    /* 42 Ethernet MAC (EMAC) */
void __attribute__((weak)) __CAN0_Handler();    /* 43 CAN Controller 0 (CAN0) */
void __attribute__((weak)) __CAN1_Handler();    /* 44 CAN Controller 1 (CAN1) */

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
                0,                    // Reserved
                0,                    // Reserved
                0,                    // Reserved
                0,                    // Reserved
                __svc_handler,        // SVCall handler
                __debugmon_handler,   // Debug monitor handler
                0,                    // Reserved
                __pendsv_handler,     // The PendSV handler
                __systick_handler,    // The SysTick handler
                // peripheral interupts
                __SUPC_Handler,       //  0 Supply Controller (SUPC)                      
                __RSTC_Handler,       //  1 Reset Controller (RSTC)                          
                __RTC_Handler,        //  2 Real Time Clock (RTC)              
                __RTT_Handler,        //  3 Real Time Timer (RTT)              
                __WDT_Handler,        //  4 Watchdog Timer (WDT)              
                __PMC_Handler,        //  5 Power Management Controller (PMC)              
                __EFC0_Handler,       //  6 Enhanced Flash Controller 0 (EFC0)              
                __EFC1_Handler,       //  7 Enhanced Flash Controller 1 (EFC1)              
                __UART_Handler,       //  8 Universal Asynchronous Receiver Transceiver (UART)              
                __SMC_Handler,        //  9 Static Memory Controller (SMC)              
                0,                    // 10 not used  
                __PIOA_Handler,       // 11 Parallel I/O Controller A, (PIOA)              
                __PIOB_Handler,       // 12 Parallel I/O Controller B (PIOB)              
                __PIOC_Handler,       // 13 Parallel I/O Controller C (PIOC)              
                __PIOD_Handler,       // 14 Parallel I/O Controller D (PIOD)              
                0,                    // 15 not used  
                0,                    // 16 not used  
                __USART0_Handler,     // 17 USART 0 (USART0)                  
                __USART1_Handler,     // 18 USART 1 (USART1)                  
                __USART2_Handler,     // 19 USART 2 (USART2)                  
                __USART3_Handler,     // 20 USART 3 (USART3)                  
                __HSMCI_Handler,      // 21 Multimedia Card Interface (HSMCI)                  
                __TWI0_Handler,       // 22 Two-Wire Interface 0 (TWI0)              
                __TWI1_Handler,       // 23 Two-Wire Interface 1 (TWI1)              
                __SPI0_Handler,       // 24 Serial Peripheral Interface (SPI0)              
                0,                    // 25 not used  
                __SSC_Handler,        // 26 Synchronous Serial Controller (SSC)              
                __TC0_Handler,        // 27 Timer Counter 0 (TC0)              
                __TC1_Handler,        // 28 Timer Counter 1 (TC1)              
                __TC2_Handler,        // 29 Timer Counter 2 (TC2)              
                __TC3_Handler,        // 30 Timer Counter 3 (TC3)              
                __TC4_Handler,        // 31 Timer Counter 4 (TC4)              
                __TC5_Handler,        // 32 Timer Counter 5 (TC5)              
                __TC6_Handler,        // 33 Timer Counter 6 (TC6)              
                __TC7_Handler,        // 34 Timer Counter 7 (TC7)              
                __TC8_Handler,        // 35 Timer Counter 8 (TC8)              
                __PWM_Handler,        // 36 Pulse Width Modulation Controller (PWM)              
                __ADC_Handler,        // 37 ADC Controller (ADC)              
                __DACC_Handler,       // 38 DAC Controller (DACC)              
                __DMAC_Handler,       // 39 DMA Controller (DMAC)              
                __UOTGHS_Handler,     // 40 USB OTG High Speed (UOTGHS)                  
                __TRNG_Handler,       // 41 True Random Number Generator (TRNG)              
                __EMAC_Handler,       // 42 Ethernet MAC (EMAC)              
                __CAN0_Handler,       // 43 CAN Controller 0 (CAN0)              
                __CAN1_Handler,       // 44 CAN Controller 1 (CAN1)              
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

#pragma weak __SUPC_Handler       = __default_handler
#pragma weak __RSTC_Handler       = __default_handler
#pragma weak __RTC_Handler        = __default_handler
#pragma weak __RTT_Handler        = __default_handler
#pragma weak __WDT_Handler        = __default_handler
#pragma weak __PMC_Handler        = __default_handler
#pragma weak __EFC0_Handler       = __default_handler
#pragma weak __EFC1_Handler       = __default_handler
#pragma weak __UART_Handler       = __default_handler
#pragma weak __SMC_Handler        = __default_handler
#pragma weak __PIOA_Handler       = __default_handler
#pragma weak __PIOB_Handler       = __default_handler
#pragma weak __PIOC_Handler       = __default_handler
#pragma weak __PIOD_Handler       = __default_handler
#pragma weak __USART0_Handler     = __default_handler    
#pragma weak __USART1_Handler     = __default_handler    
#pragma weak __USART2_Handler     = __default_handler    
#pragma weak __USART3_Handler     = __default_handler    
#pragma weak __HSMCI_Handler      = __default_handler    
#pragma weak __TWI0_Handler       = __default_handler
#pragma weak __TWI1_Handler       = __default_handler
#pragma weak __SPI0_Handler       = __default_handler
#pragma weak __SSC_Handler        = __default_handler
#pragma weak __TC0_Handler        = __default_handler
#pragma weak __TC1_Handler        = __default_handler
#pragma weak __TC2_Handler        = __default_handler
#pragma weak __TC3_Handler        = __default_handler
#pragma weak __TC4_Handler        = __default_handler
#pragma weak __TC5_Handler        = __default_handler
#pragma weak __TC6_Handler        = __default_handler
#pragma weak __TC7_Handler        = __default_handler
#pragma weak __TC8_Handler        = __default_handler
#pragma weak __PWM_Handler        = __default_handler
#pragma weak __ADC_Handler        = __default_handler
#pragma weak __DACC_Handler       = __default_handler
#pragma weak __DMAC_Handler       = __default_handler
#pragma weak __UOTGHS_Handler     = __default_handler    
#pragma weak __TRNG_Handler       = __default_handler
#pragma weak __EMAC_Handler       = __default_handler
#pragma weak __CAN0_Handler       = __default_handler
#pragma weak __CAN1_Handler       = __default_handler

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
