#include <limits.h>
#include <stdlib.h>
#define register

/*
 * We gave 'weak' attribute, so these functions can be aliased into a single
 * function
 */
void __attribute__((weak)) __reset_handler();                   /* Reset Handler */
void __attribute__((weak)) __nmi_handler();                     /* NMI Handler */
void __attribute__((weak)) __hardfault_handler();               /* Hard Fault Handler */
void __attribute__((weak)) __memmanage_handler();               /* MPU Fault Handler */
void __attribute__((weak)) __busfault_handler();                /* Bus Fault Handler */
void __attribute__((weak)) __usagefault_handler();              /* Usage Fault Handler */
void __attribute__((weak)) __svc_handler();                     /* SVCall Handler */
void __attribute__((weak)) __debugmon_handler();                /* Debug Monitor Handler */
void __attribute__((weak)) __pendsv_handler();                  /* PendSV Handler */
void __attribute__((weak)) __systick_handler();                 /* SysTick Handler */

/* Peripherals handlers */
void __attribute__((weak)) __DMA0_DMA16_IRQHandler();           /* 0   DMA channel 0/16 transfer complete*/
void __attribute__((weak)) __DMA1_DMA17_IRQHandler();           /* 1   DMA channel 1/17 transfer complete*/
void __attribute__((weak)) __DMA2_DMA18_IRQHandler();           /* 2   DMA channel 2/18 transfer complete*/
void __attribute__((weak)) __DMA3_DMA19_IRQHandler();           /* 3   DMA channel 3/19 transfer complete*/
void __attribute__((weak)) __DMA4_DMA20_IRQHandler();           /* 4   DMA channel 4/20 transfer complete*/
void __attribute__((weak)) __DMA5_DMA21_IRQHandler();           /* 5   DMA channel 5/21 transfer complete*/
void __attribute__((weak)) __DMA6_DMA22_IRQHandler();           /* 6   DMA channel 6/22 transfer complete*/
void __attribute__((weak)) __DMA7_DMA23_IRQHandler();           /* 7   DMA channel 7/23 transfer complete*/
void __attribute__((weak)) __DMA8_DMA24_IRQHandler();           /* 8   DMA channel 8/24 transfer complete*/
void __attribute__((weak)) __DMA9_DMA25_IRQHandler();           /* 9   DMA channel 9/25 transfer complete*/
void __attribute__((weak)) __DMA10_DMA26_IRQHandler();          /* 10  DMA channel 10/26 transfer complete*/
void __attribute__((weak)) __DMA11_DMA27_IRQHandler();          /* 11  DMA channel 11/27 transfer complete*/
void __attribute__((weak)) __DMA12_DMA28_IRQHandler();          /* 12  DMA channel 12/28 transfer complete*/
void __attribute__((weak)) __DMA13_DMA29_IRQHandler();          /* 13  DMA channel 13/29 transfer complete*/
void __attribute__((weak)) __DMA14_DMA30_IRQHandler();          /* 14  DMA channel 14/30 transfer complete*/
void __attribute__((weak)) __DMA15_DMA31_IRQHandler();          /* 15  DMA channel 15/31 transfer complete*/
void __attribute__((weak)) __DMA_ERROR_IRQHandler();            /* 16  DMA error interrupt channels 0-15 / 16-31*/
void __attribute__((weak)) __CTI0_ERROR_IRQHandler();           /* 17  CTI0_Error*/
void __attribute__((weak)) __CTI1_ERROR_IRQHandler();           /* 18  CTI1_Error*/
void __attribute__((weak)) __CORE_IRQHandler();                 /* 19  CorePlatform exception IRQ*/
void __attribute__((weak)) __LPUART1_IRQHandler();              /* 20  LPUART1 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPUART2_IRQHandler();              /* 21  LPUART2 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPUART3_IRQHandler();              /* 22  LPUART3 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPUART4_IRQHandler();              /* 23  LPUART4 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPUART5_IRQHandler();              /* 24  LPUART5 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPUART6_IRQHandler();              /* 25  LPUART6 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPUART7_IRQHandler();              /* 26  LPUART7 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPUART8_IRQHandler();              /* 27  LPUART8 TX interrupt and RX interrupt*/
void __attribute__((weak)) __LPI2C1_IRQHandler();               /* 28  LPI2C1 interrupt*/
void __attribute__((weak)) __LPI2C2_IRQHandler();               /* 29  LPI2C2 interrupt*/
void __attribute__((weak)) __LPI2C3_IRQHandler();               /* 30  LPI2C3 interrupt*/
void __attribute__((weak)) __LPI2C4_IRQHandler();               /* 31  LPI2C4 interrupt*/
void __attribute__((weak)) __LPSPI1_IRQHandler();               /* 32  LPSPI1 single interrupt vector for all sources*/
void __attribute__((weak)) __LPSPI2_IRQHandler();               /* 33  LPSPI2 single interrupt vector for all sources*/
void __attribute__((weak)) __LPSPI3_IRQHandler();               /* 34  LPSPI3 single interrupt vector for all sources*/
void __attribute__((weak)) __LPSPI4_IRQHandler();               /* 35  LPSPI4  single interrupt vector for all sources*/
void __attribute__((weak)) __CAN1_IRQHandler();                 /* 36  CAN1 interrupt*/
void __attribute__((weak)) __CAN2_IRQHandler();                 /* 37  CAN2 interrupt*/
void __attribute__((weak)) __FLEXRAM_IRQHandler();              /* 38  FlexRAM address out of range Or access hit IRQ*/
void __attribute__((weak)) __KPP_IRQHandler();                  /* 39  Keypad nterrupt*/
void __attribute__((weak)) __TSC_DIG_IRQHandler();              /* 40  TSC interrupt*/
void __attribute__((weak)) __GPR_IRQ_IRQHandler();              /* 41  GPR interrupt*/
void __attribute__((weak)) __LCDIF_IRQHandler();                /* 42  LCDIF interrupt*/
void __attribute__((weak)) __CSI_IRQHandler();                  /* 43  CSI interrupt*/
void __attribute__((weak)) __PXP_IRQHandler();                  /* 44  PXP interrupt*/
void __attribute__((weak)) __WDOG2_IRQHandler();                /* 45  WDOG2 interrupt*/
void __attribute__((weak)) __SNVS_HP_WRAPPER_IRQHandler();      /* 46  SRTC Consolidated Interrupt. Non TZ*/
void __attribute__((weak)) __SNVS_HP_WRAPPER_TZ_IRQHandler();   /* 47  SRTC Security Interrupt. TZ*/
void __attribute__((weak)) __SNVS_LP_WRAPPER_IRQHandler();      /* 48  ON-OFF button press shorter than 5 secs (pulse event)*/
void __attribute__((weak)) __CSU_IRQHandler();                  /* 49  CSU interrupt*/
void __attribute__((weak)) __DCP_IRQHandler();                  /* 50  DCP_IRQ interrupt*/
void __attribute__((weak)) __DCP_VMI_IRQHandler();              /* 51  DCP_VMI_IRQ interrupt*/
                                                                /* 52  Reserved interrupt*/
void __attribute__((weak)) __TRNG_IRQHandler();                 /* 53  TRNG interrupt*/
void __attribute__((weak)) __SJC_IRQHandler();                  /* 54  SJC interrupt*/
void __attribute__((weak)) __BEE_IRQHandler();                  /* 55  BEE interrupt*/
void __attribute__((weak)) __SAI1_IRQHandler();                 /* 56  SAI1 interrupt*/
void __attribute__((weak)) __SAI2_IRQHandler();                 /* 57  SAI1 interrupt*/
void __attribute__((weak)) __SAI3_RX_IRQHandler();              /* 58  SAI3 interrupt*/
void __attribute__((weak)) __SAI3_TX_IRQHandler();              /* 59  SAI3 interrupt*/
void __attribute__((weak)) __SPDIF_IRQHandler();                /* 60  SPDIF interrupt*/
void __attribute__((weak)) __PMU_EVENT_IRQHandler();            /* 61  Brown-out event interrupt*/
                                                                /* 62  Reserved interrupt*/
void __attribute__((weak)) __TEMP_LOW_HIGH_IRQHandler();        /* 63  TempSensor low/high interrupt*/
void __attribute__((weak)) __TEMP_PANIC_IRQHandler();           /* 64  TempSensor panic interrupt*/
void __attribute__((weak)) __USB_PHY1_IRQHandler();             /* 65  USBPHY (UTMI0), Interrupt*/
void __attribute__((weak)) __USB_PHY2_IRQHandler();             /* 66  USBPHY (UTMI1), Interrupt*/
void __attribute__((weak)) __ADC1_IRQHandler();                 /* 67  ADC1 interrupt*/
void __attribute__((weak)) __ADC2_IRQHandler();                 /* 68  ADC2 interrupt*/
void __attribute__((weak)) __DCDC_IRQHandler();                 /* 69  DCDC interrupt*/
                                                                /* 70  Reserved interrupt*/
                                                                /* 71  Reserved interrupt*/
void __attribute__((weak)) __GPIO1_INT0_IRQHandler();           /* 72  Active HIGH Interrupt from INT0 from GPIO*/
void __attribute__((weak)) __GPIO1_INT1_IRQHandler();           /* 73  Active HIGH Interrupt from INT1 from GPIO*/
void __attribute__((weak)) __GPIO1_INT2_IRQHandler();           /* 74  Active HIGH Interrupt from INT2 from GPIO*/
void __attribute__((weak)) __GPIO1_INT3_IRQHandler();           /* 75  Active HIGH Interrupt from INT3 from GPIO*/
void __attribute__((weak)) __GPIO1_INT4_IRQHandler();           /* 76  Active HIGH Interrupt from INT4 from GPIO*/
void __attribute__((weak)) __GPIO1_INT5_IRQHandler();           /* 77  Active HIGH Interrupt from INT5 from GPIO*/
void __attribute__((weak)) __GPIO1_INT6_IRQHandler();           /* 78  Active HIGH Interrupt from INT6 from GPIO*/
void __attribute__((weak)) __GPIO1_INT7_IRQHandler();           /* 79  Active HIGH Interrupt from INT7 from GPIO*/
void __attribute__((weak)) __GPIO1_Combined_0_15_IRQHandler();  /* 80  Combined interrupt indication for GPIO1 signal 0 throughout 15*/
void __attribute__((weak)) __GPIO1_Combined_16_31_IRQHandler(); /* 81  Combined interrupt indication for GPIO1 signal 16 throughout 31*/
void __attribute__((weak)) __GPIO2_Combined_0_15_IRQHandler();  /* 82  Combined interrupt indication for GPIO2 signal 0 throughout 15*/
void __attribute__((weak)) __GPIO2_Combined_16_31_IRQHandler(); /* 83  Combined interrupt indication for GPIO2 signal 16 throughout 31*/
void __attribute__((weak)) __GPIO3_Combined_0_15_IRQHandler();  /* 84  Combined interrupt indication for GPIO3 signal 0 throughout 15*/
void __attribute__((weak)) __GPIO3_Combined_16_31_IRQHandler(); /* 85  Combined interrupt indication for GPIO3 signal 16 throughout 31*/
void __attribute__((weak)) __GPIO4_Combined_0_15_IRQHandler();  /* 86  Combined interrupt indication for GPIO4 signal 0 throughout 15*/
void __attribute__((weak)) __GPIO4_Combined_16_31_IRQHandler(); /* 87  Combined interrupt indication for GPIO4 signal 16 throughout 31*/
void __attribute__((weak)) __GPIO5_Combined_0_15_IRQHandler();  /* 88  Combined interrupt indication for GPIO5 signal 0 throughout 15*/
void __attribute__((weak)) __GPIO5_Combined_16_31_IRQHandler(); /* 89  Combined interrupt indication for GPIO5 signal 16 throughout 31*/
void __attribute__((weak)) __FLEXIO1_IRQHandler();              /* 90  FLEXIO1 interrupt*/
void __attribute__((weak)) __FLEXIO2_IRQHandler();              /* 91  FLEXIO2 interrupt*/
void __attribute__((weak)) __WDOG1_IRQHandler();                /* 92  WDOG1 interrupt*/
void __attribute__((weak)) __RTWDOG_IRQHandler();               /* 93  RTWDOG interrupt*/
void __attribute__((weak)) __EWM_IRQHandler();                  /* 94  EWM interrupt*/
void __attribute__((weak)) __CCM_1_IRQHandler();                /* 95  CCM IRQ1 interrupt*/
void __attribute__((weak)) __CCM_2_IRQHandler();                /* 96  CCM IRQ2 interrupt*/
void __attribute__((weak)) __GPC_IRQHandler();                  /* 97  GPC interrupt*/
void __attribute__((weak)) __SRC_IRQHandler();                  /* 98  SRC interrupt*/
                                                                /* 99  Reserved interrupt*/
void __attribute__((weak)) __GPT1_IRQHandler();                 /* 100 GPT1 interrupt*/
void __attribute__((weak)) __GPT2_IRQHandler();                 /* 101 GPT2 interrupt*/
void __attribute__((weak)) __PWM1_0_IRQHandler();               /* 102 PWM1 capture 0, compare 0, or reload 0 interrupt*/
void __attribute__((weak)) __PWM1_1_IRQHandler();               /* 103 PWM1 capture 1, compare 1, or reload 0 interrupt*/
void __attribute__((weak)) __PWM1_2_IRQHandler();               /* 104 PWM1 capture 2, compare 2, or reload 0 interrupt*/
void __attribute__((weak)) __PWM1_3_IRQHandler();               /* 105 PWM1 capture 3, compare 3, or reload 0 interrupt*/
void __attribute__((weak)) __PWM1_FAULT_IRQHandler();           /* 106 PWM1 fault or reload error interrupt*/
void __attribute__((weak)) __FLEXSPI2_IRQHandler();             /* 107 FlexSPI2 interrupt*/
void __attribute__((weak)) __FLEXSPI_IRQHandler();              /* 108 FlexSPI0 interrupt*/
void __attribute__((weak)) __SEMC_IRQHandler();                 /* 109 SEMC interrupt*/
void __attribute__((weak)) __USDHC1_IRQHandler();               /* 110 USDHC1 interrupt*/
void __attribute__((weak)) __USDHC2_IRQHandler();               /* 111 USDHC2 interrupt*/
void __attribute__((weak)) __USB_OTG2_IRQHandler();             /* 112 USBO2 USB OTG2*/
void __attribute__((weak)) __USB_OTG1_IRQHandler();             /* 113 USBO2 USB OTG1*/
void __attribute__((weak)) __ENET_IRQHandler();                 /* 114 ENET interrupt*/
void __attribute__((weak)) __ENET_1588_Timer_IRQHandler();      /* 115 ENET_1588_Timer interrupt*/
void __attribute__((weak)) __XBAR1_IRQ_0_1_IRQHandler();        /* 116 XBAR1 interrupt*/
void __attribute__((weak)) __XBAR1_IRQ_2_3_IRQHandler();        /* 117 XBAR1 interrupt*/
void __attribute__((weak)) __ADC_ETC_IRQ0_IRQHandler();         /* 118 ADCETC IRQ0 interrupt*/
void __attribute__((weak)) __ADC_ETC_IRQ1_IRQHandler();         /* 119 ADCETC IRQ1 interrupt*/
void __attribute__((weak)) __ADC_ETC_IRQ2_IRQHandler();         /* 120 ADCETC IRQ2 interrupt*/
void __attribute__((weak)) __ADC_ETC_ERROR_IRQ_IRQHandler();    /* 121 ADCETC Error IRQ interrupt*/
void __attribute__((weak)) __PIT_IRQHandler();                  /* 122 PIT interrupt*/
void __attribute__((weak)) __ACMP1_IRQHandler();                /* 123 ACMP interrupt*/
void __attribute__((weak)) __ACMP2_IRQHandler();                /* 124 ACMP interrupt*/
void __attribute__((weak)) __ACMP3_IRQHandler();                /* 125 ACMP interrupt*/
void __attribute__((weak)) __ACMP4_IRQHandler();                /* 126 ACMP interrupt*/
                                                                /* 127 Reserved interrupt*/
                                                                /* 128 Reserved interrupt*/
void __attribute__((weak)) __ENC1_IRQHandler();                 /* 129 ENC1 interrupt*/
void __attribute__((weak)) __ENC2_IRQHandler();                 /* 130 ENC2 interrupt*/
void __attribute__((weak)) __ENC3_IRQHandler();                 /* 131 ENC3 interrupt*/
void __attribute__((weak)) __ENC4_IRQHandler();                 /* 132 ENC4 interrupt*/
void __attribute__((weak)) __TMR1_IRQHandler();                 /* 133 TMR1 interrupt*/
void __attribute__((weak)) __TMR2_IRQHandler();                 /* 134 TMR2 interrupt*/
void __attribute__((weak)) __TMR3_IRQHandler();                 /* 135 TMR3 interrupt*/
void __attribute__((weak)) __TMR4_IRQHandler();                 /* 136 TMR4 interrupt*/
void __attribute__((weak)) __PWM2_0_IRQHandler();               /* 137 PWM2 capture 0, compare 0, or reload 0 interrupt*/
void __attribute__((weak)) __PWM2_1_IRQHandler();               /* 138 PWM2 capture 1, compare 1, or reload 0 interrupt*/
void __attribute__((weak)) __PWM2_2_IRQHandler();               /* 139 PWM2 capture 2, compare 2, or reload 0 interrupt*/
void __attribute__((weak)) __PWM2_3_IRQHandler();               /* 140 PWM2 capture 3, compare 3, or reload 0 interrupt*/
void __attribute__((weak)) __PWM2_FAULT_IRQHandler();           /* 141 PWM2 fault or reload error interrupt*/
void __attribute__((weak)) __PWM3_0_IRQHandler();               /* 142 PWM3 capture 0, compare 0, or reload 0 interrupt*/
void __attribute__((weak)) __PWM3_1_IRQHandler();               /* 143 PWM3 capture 1, compare 1, or reload 0 interrupt*/
void __attribute__((weak)) __PWM3_2_IRQHandler();               /* 144 PWM3 capture 2, compare 2, or reload 0 interrupt*/
void __attribute__((weak)) __PWM3_3_IRQHandler();               /* 145 PWM3 capture 3, compare 3, or reload 0 interrupt*/
void __attribute__((weak)) __PWM3_FAULT_IRQHandler();           /* 146 PWM3 fault or reload error interrupt*/
void __attribute__((weak)) __PWM4_0_IRQHandler();               /* 147 PWM4 capture 0, compare 0, or reload 0 interrupt*/
void __attribute__((weak)) __PWM4_1_IRQHandler();               /* 148 PWM4 capture 1, compare 1, or reload 0 interrupt*/
void __attribute__((weak)) __PWM4_2_IRQHandler();               /* 149 PWM4 capture 2, compare 2, or reload 0 interrupt*/
void __attribute__((weak)) __PWM4_3_IRQHandler();               /* 150 PWM4 capture 3, compare 3, or reload 0 interrupt*/
void __attribute__((weak)) __PWM4_FAULT_IRQHandler();           /* 151 PWM4 fault or reload error interrupt*/
void __attribute__((weak)) __ENET2_IRQHandler();                /* 152 ENET2 interrupt*/
void __attribute__((weak)) __ENET2_1588_Timer_IRQHandler();     /* 153 ENET2_1588_Timer interrupt*/
void __attribute__((weak)) __CAN3_IRQHandler();                 /* 154 CAN3 interrupt*/
                                                                /* 155 Reserved interrupt */
void __attribute__((weak)) __FLEXIO3_IRQHandler();              /* 156 FLEXIO3 interrupt */
void __attribute__((weak)) __GPIO6_7_8_9_IRQHandler();          /* 157 GPIO6, GPIO7, GPIO8, GPIO9 interrupt */
                                                                /* 158 till 238 not used */


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
                __DMA0_DMA16_IRQHandler,              /* 0   DMA channel 0/16 transfer complete*/                                                  
                __DMA1_DMA17_IRQHandler,              /* 1   DMA channel 1/17 transfer complete*/                                                  
                __DMA2_DMA18_IRQHandler,              /* 2   DMA channel 2/18 transfer complete*/                                                  
                __DMA3_DMA19_IRQHandler,              /* 3   DMA channel 3/19 transfer complete*/                                                  
                __DMA4_DMA20_IRQHandler,              /* 4   DMA channel 4/20 transfer complete*/                                                  
                __DMA5_DMA21_IRQHandler,              /* 5   DMA channel 5/21 transfer complete*/                                                  
                __DMA6_DMA22_IRQHandler,              /* 6   DMA channel 6/22 transfer complete*/                                                  
                __DMA7_DMA23_IRQHandler,              /* 7   DMA channel 7/23 transfer complete*/                                                  
                __DMA8_DMA24_IRQHandler,              /* 8   DMA channel 8/24 transfer complete*/                                                  
                __DMA9_DMA25_IRQHandler,              /* 9   DMA channel 9/25 transfer complete*/                                                  
                __DMA10_DMA26_IRQHandler,             /* 10  DMA channel 10/26 transfer complete*/                                                  
                __DMA11_DMA27_IRQHandler,             /* 11  DMA channel 11/27 transfer complete*/                                                  
                __DMA12_DMA28_IRQHandler,             /* 12  DMA channel 12/28 transfer complete*/                                                  
                __DMA13_DMA29_IRQHandler,             /* 13  DMA channel 13/29 transfer complete*/                                                  
                __DMA14_DMA30_IRQHandler,             /* 14  DMA channel 14/30 transfer complete*/                                                  
                __DMA15_DMA31_IRQHandler,             /* 15  DMA channel 15/31 transfer complete*/                                                  
                __DMA_ERROR_IRQHandler,               /* 16  DMA error interrupt channels 0-15 / 16-31*/                                              
                __CTI0_ERROR_IRQHandler,              /* 17  CTI0_Error*/                                                  
                __CTI1_ERROR_IRQHandler,              /* 18  CTI1_Error*/                                                  
                __CORE_IRQHandler,                    /* 19  CorePlatform exception IRQ*/                                          
                __LPUART1_IRQHandler,                 /* 20  LPUART1 TX interrupt and RX interrupt*/                                              
                __LPUART2_IRQHandler,                 /* 21  LPUART2 TX interrupt and RX interrupt*/                                              
                __LPUART3_IRQHandler,                 /* 22  LPUART3 TX interrupt and RX interrupt*/                                              
                __LPUART4_IRQHandler,                 /* 23  LPUART4 TX interrupt and RX interrupt*/                                              
                __LPUART5_IRQHandler,                 /* 24  LPUART5 TX interrupt and RX interrupt*/                                              
                __LPUART6_IRQHandler,                 /* 25  LPUART6 TX interrupt and RX interrupt*/                                              
                __LPUART7_IRQHandler,                 /* 26  LPUART7 TX interrupt and RX interrupt*/                                              
                __LPUART8_IRQHandler,                 /* 27  LPUART8 TX interrupt and RX interrupt*/                                              
                __LPI2C1_IRQHandler,                  /* 28  LPI2C1 interrupt*/                                              
                __LPI2C2_IRQHandler,                  /* 29  LPI2C2 interrupt*/                                              
                __LPI2C3_IRQHandler,                  /* 30  LPI2C3 interrupt*/                                              
                __LPI2C4_IRQHandler,                  /* 31  LPI2C4 interrupt*/                                              
                __LPSPI1_IRQHandler,                  /* 32  LPSPI1 single interrupt vector for all sources*/                                              
                __LPSPI2_IRQHandler,                  /* 33  LPSPI2 single interrupt vector for all sources*/                                              
                __LPSPI3_IRQHandler,                  /* 34  LPSPI3 single interrupt vector for all sources*/                                              
                __LPSPI4_IRQHandler,                  /* 35  LPSPI4  single interrupt vector for all sources*/                                              
                __CAN1_IRQHandler,                    /* 36  CAN1 interrupt*/                                          
                __CAN2_IRQHandler,                    /* 37  CAN2 interrupt*/                                          
                __FLEXRAM_IRQHandler,                 /* 38  FlexRAM address out of range Or access hit IRQ*/                                              
                __KPP_IRQHandler,                     /* 39  Keypad nterrupt*/                                          
                __TSC_DIG_IRQHandler,                 /* 40  TSC interrupt*/                                              
                __GPR_IRQ_IRQHandler,                 /* 41  GPR interrupt*/                                              
                __LCDIF_IRQHandler,                   /* 42  LCDIF interrupt*/                                          
                __CSI_IRQHandler,                     /* 43  CSI interrupt*/                                          
                __PXP_IRQHandler,                     /* 44  PXP interrupt*/                                          
                __WDOG2_IRQHandler,                   /* 45  WDOG2 interrupt*/                                          
                __SNVS_HP_WRAPPER_IRQHandler,         /* 46  SRTC Consolidated Interrupt. Non TZ*/                                                      
                __SNVS_HP_WRAPPER_TZ_IRQHandler,      /* 47  SRTC Security Interrupt. TZ*/                                                          
                __SNVS_LP_WRAPPER_IRQHandler,         /* 48  ON-OFF button press shorter than 5 secs (pulse event)*/                                                      
                __CSU_IRQHandler,                     /* 49  CSU interrupt*/                                          
                __DCP_IRQHandler,                     /* 50  DCP_IRQ interrupt*/                                          
                __DCP_VMI_IRQHandler,                 /* 51  DCP_VMI_IRQ interrupt*/                                              
                0,                                    /* 52  Reserved interrupt*/                          
                __TRNG_IRQHandler,                    /* 53  TRNG interrupt*/                                          
                __SJC_IRQHandler,                     /* 54  SJC interrupt*/                                          
                __BEE_IRQHandler,                     /* 55  BEE interrupt*/                                          
                __SAI1_IRQHandler,                    /* 56  SAI1 interrupt*/                                          
                __SAI2_IRQHandler,                    /* 57  SAI1 interrupt*/                                          
                __SAI3_RX_IRQHandler,                 /* 58  SAI3 interrupt*/                                              
                __SAI3_TX_IRQHandler,                 /* 59  SAI3 interrupt*/                                              
                __SPDIF_IRQHandler,                   /* 60  SPDIF interrupt*/                                          
                __PMU_EVENT_IRQHandler,               /* 61  Brown-out event interrupt*/                                              
                0,                                    /* 62  Reserved interrupt*/                          
                __TEMP_LOW_HIGH_IRQHandler,           /* 63  TempSensor low/high interrupt*/                                                  
                __TEMP_PANIC_IRQHandler,              /* 64  TempSensor panic interrupt*/                                                  
                __USB_PHY1_IRQHandler,                /* 65  USBPHY (UTMI0), Interrupt*/                                              
                __USB_PHY2_IRQHandler,                /* 66  USBPHY (UTMI1), Interrupt*/                                              
                __ADC1_IRQHandler,                    /* 67  ADC1 interrupt*/                                          
                __ADC2_IRQHandler,                    /* 68  ADC2 interrupt*/                                          
                __DCDC_IRQHandler,                    /* 69  DCDC interrupt*/                                          
                0,                                    /* 70  Reserved interrupt*/                          
                0,                                    /* 71  Reserved interrupt*/                          
                __GPIO1_INT0_IRQHandler,              /* 72  Active HIGH Interrupt from INT0 from GPIO*/                                                  
                __GPIO1_INT1_IRQHandler,              /* 73  Active HIGH Interrupt from INT1 from GPIO*/                                                  
                __GPIO1_INT2_IRQHandler,              /* 74  Active HIGH Interrupt from INT2 from GPIO*/                                                  
                __GPIO1_INT3_IRQHandler,              /* 75  Active HIGH Interrupt from INT3 from GPIO*/                                                  
                __GPIO1_INT4_IRQHandler,              /* 76  Active HIGH Interrupt from INT4 from GPIO*/                                                  
                __GPIO1_INT5_IRQHandler,              /* 77  Active HIGH Interrupt from INT5 from GPIO*/                                                  
                __GPIO1_INT6_IRQHandler,              /* 78  Active HIGH Interrupt from INT6 from GPIO*/                                                  
                __GPIO1_INT7_IRQHandler,              /* 79  Active HIGH Interrupt from INT7 from GPIO*/                                                  
                __GPIO1_Combined_0_15_IRQHandler,     /* 80  Combined interrupt indication for GPIO1 signal 0 throughout 15*/                                                          
                __GPIO1_Combined_16_31_IRQHandler,    /* 81  Combined interrupt indication for GPIO1 signal 16 throughout 31*/                                                          
                __GPIO2_Combined_0_15_IRQHandler,     /* 82  Combined interrupt indication for GPIO2 signal 0 throughout 15*/                                                          
                __GPIO2_Combined_16_31_IRQHandler,    /* 83  Combined interrupt indication for GPIO2 signal 16 throughout 31*/                                                          
                __GPIO3_Combined_0_15_IRQHandler,     /* 84  Combined interrupt indication for GPIO3 signal 0 throughout 15*/                                                          
                __GPIO3_Combined_16_31_IRQHandler,    /* 85  Combined interrupt indication for GPIO3 signal 16 throughout 31*/                                                          
                __GPIO4_Combined_0_15_IRQHandler,     /* 86  Combined interrupt indication for GPIO4 signal 0 throughout 15*/                                                          
                __GPIO4_Combined_16_31_IRQHandler,    /* 87  Combined interrupt indication for GPIO4 signal 16 throughout 31*/                                                          
                __GPIO5_Combined_0_15_IRQHandler,     /* 88  Combined interrupt indication for GPIO5 signal 0 throughout 15*/                                                          
                __GPIO5_Combined_16_31_IRQHandler,    /* 89  Combined interrupt indication for GPIO5 signal 16 throughout 31*/                                                          
                __FLEXIO1_IRQHandler,                 /* 90  FLEXIO1 interrupt*/                                              
                __FLEXIO2_IRQHandler,                 /* 91  FLEXIO2 interrupt*/                                              
                __WDOG1_IRQHandler,                   /* 92  WDOG1 interrupt*/                                          
                __RTWDOG_IRQHandler,                  /* 93  RTWDOG interrupt*/                                              
                __EWM_IRQHandler,                     /* 94  EWM interrupt*/                                          
                __CCM_1_IRQHandler,                   /* 95  CCM IRQ1 interrupt*/                                          
                __CCM_2_IRQHandler,                   /* 96  CCM IRQ2 interrupt*/                                          
                __GPC_IRQHandler,                     /* 97  GPC interrupt*/                                          
                __SRC_IRQHandler,                     /* 98  SRC interrupt*/                                          
                0,                                    /* 99  Reserved interrupt*/                          
                __GPT1_IRQHandler,                    /* 100 GPT1 interrupt*/                                          
                __GPT2_IRQHandler,                    /* 101 GPT2 interrupt*/                                          
                __PWM1_0_IRQHandler,                  /* 102 PWM1 capture 0, compare 0, or reload 0 interrupt*/                                              
                __PWM1_1_IRQHandler,                  /* 103 PWM1 capture 1, compare 1, or reload 0 interrupt*/                                              
                __PWM1_2_IRQHandler,                  /* 104 PWM1 capture 2, compare 2, or reload 0 interrupt*/                                              
                __PWM1_3_IRQHandler,                  /* 105 PWM1 capture 3, compare 3, or reload 0 interrupt*/                                              
                __PWM1_FAULT_IRQHandler,              /* 106 PWM1 fault or reload error interrupt*/                                                  
                __FLEXSPI2_IRQHandler,                /* 107 FlexSPI2 interrupt*/                                              
                __FLEXSPI_IRQHandler,                 /* 108 FlexSPI0 interrupt*/                                              
                __SEMC_IRQHandler,                    /* 109 SEMC interrupt*/                                          
                __USDHC1_IRQHandler,                  /* 110 USDHC1 interrupt*/                                              
                __USDHC2_IRQHandler,                  /* 111 USDHC2 interrupt*/                                              
                __USB_OTG2_IRQHandler,                /* 112 USBO2 USB OTG2*/                                              
                __USB_OTG1_IRQHandler,                /* 113 USBO2 USB OTG1*/                                              
                __ENET_IRQHandler,                    /* 114 ENET interrupt*/                                          
                __ENET_1588_Timer_IRQHandler,         /* 115 ENET_1588_Timer interrupt*/                                                      
                __XBAR1_IRQ_0_1_IRQHandler,           /* 116 XBAR1 interrupt*/                                                  
                __XBAR1_IRQ_2_3_IRQHandler,           /* 117 XBAR1 interrupt*/                                                  
                __ADC_ETC_IRQ0_IRQHandler,            /* 118 ADCETC IRQ0 interrupt*/                                                  
                __ADC_ETC_IRQ1_IRQHandler,            /* 119 ADCETC IRQ1 interrupt*/                                                  
                __ADC_ETC_IRQ2_IRQHandler,            /* 120 ADCETC IRQ2 interrupt*/                                                  
                __ADC_ETC_ERROR_IRQ_IRQHandler,       /* 121 ADCETC Error IRQ interrupt*/                                                      
                __PIT_IRQHandler,                     /* 122 PIT interrupt*/                                          
                __ACMP1_IRQHandler,                   /* 123 ACMP interrupt*/                                          
                __ACMP2_IRQHandler,                   /* 124 ACMP interrupt*/                                          
                __ACMP3_IRQHandler,                   /* 125 ACMP interrupt*/                                          
                __ACMP4_IRQHandler,                   /* 126 ACMP interrupt*/                                          
                0,                                    /* 127 Reserved interrupt*/                          
                0,                                    /* 128 Reserved interrupt*/                          
                __ENC1_IRQHandler,                    /* 129 ENC1 interrupt*/                                          
                __ENC2_IRQHandler,                    /* 130 ENC2 interrupt*/                                          
                __ENC3_IRQHandler,                    /* 131 ENC3 interrupt*/                                          
                __ENC4_IRQHandler,                    /* 132 ENC4 interrupt*/                                          
                __TMR1_IRQHandler,                    /* 133 TMR1 interrupt*/                                          
                __TMR2_IRQHandler,                    /* 134 TMR2 interrupt*/                                          
                __TMR3_IRQHandler,                    /* 135 TMR3 interrupt*/                                          
                __TMR4_IRQHandler,                    /* 136 TMR4 interrupt*/                                          
                __PWM2_0_IRQHandler,                  /* 137 PWM2 capture 0, compare 0, or reload 0 interrupt*/                                              
                __PWM2_1_IRQHandler,                  /* 138 PWM2 capture 1, compare 1, or reload 0 interrupt*/                                              
                __PWM2_2_IRQHandler,                  /* 139 PWM2 capture 2, compare 2, or reload 0 interrupt*/                                              
                __PWM2_3_IRQHandler,                  /* 140 PWM2 capture 3, compare 3, or reload 0 interrupt*/                                              
                __PWM2_FAULT_IRQHandler,              /* 141 PWM2 fault or reload error interrupt*/                                                  
                __PWM3_0_IRQHandler,                  /* 142 PWM3 capture 0, compare 0, or reload 0 interrupt*/                                              
                __PWM3_1_IRQHandler,                  /* 143 PWM3 capture 1, compare 1, or reload 0 interrupt*/                                              
                __PWM3_2_IRQHandler,                  /* 144 PWM3 capture 2, compare 2, or reload 0 interrupt*/                                              
                __PWM3_3_IRQHandler,                  /* 145 PWM3 capture 3, compare 3, or reload 0 interrupt*/                                              
                __PWM3_FAULT_IRQHandler,              /* 146 PWM3 fault or reload error interrupt*/                                                  
                __PWM4_0_IRQHandler,                  /* 147 PWM4 capture 0, compare 0, or reload 0 interrupt*/                                              
                __PWM4_1_IRQHandler,                  /* 148 PWM4 capture 1, compare 1, or reload 0 interrupt*/                                              
                __PWM4_2_IRQHandler,                  /* 149 PWM4 capture 2, compare 2, or reload 0 interrupt*/                                              
                __PWM4_3_IRQHandler,                  /* 150 PWM4 capture 3, compare 3, or reload 0 interrupt*/                                              
                __PWM4_FAULT_IRQHandler,              /* 151 PWM4 fault or reload error interrupt*/                                                  
                __ENET2_IRQHandler,                   /* 152 ENET2 interrupt*/                                          
                __ENET2_1588_Timer_IRQHandler,        /* 153 ENET2_1588_Timer interrupt*/                                                      
                __CAN3_IRQHandler,                    /* 154 CAN3 interrupt*/                                          
                0,                                    /* 155 Reserved interrupt */                          
                __FLEXIO3_IRQHandler,                 /* 156 FLEXIO3 interrupt */                                              
                __GPIO6_7_8_9_IRQHandler,             /* 157 GPIO6, GPIO7, GPIO8, GPIO9 interrupt */                                                  
                0,                                    /* 158 till 238 not used */
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,                
                (void*)0xFFFFFFFF                     /* reserved for user trim value */
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

#pragma weak __DMA0_DMA16_IRQHandler            = __default_handler
#pragma weak __DMA1_DMA17_IRQHandler            = __default_handler
#pragma weak __DMA2_DMA18_IRQHandler            = __default_handler
#pragma weak __DMA3_DMA19_IRQHandler            = __default_handler
#pragma weak __DMA4_DMA20_IRQHandler            = __default_handler
#pragma weak __DMA5_DMA21_IRQHandler            = __default_handler
#pragma weak __DMA6_DMA22_IRQHandler            = __default_handler
#pragma weak __DMA7_DMA23_IRQHandler            = __default_handler
#pragma weak __DMA8_DMA24_IRQHandler            = __default_handler
#pragma weak __DMA9_DMA25_IRQHandler            = __default_handler
#pragma weak __DMA10_DMA26_IRQHandler           = __default_handler
#pragma weak __DMA11_DMA27_IRQHandler           = __default_handler
#pragma weak __DMA12_DMA28_IRQHandler           = __default_handler
#pragma weak __DMA13_DMA29_IRQHandler           = __default_handler
#pragma weak __DMA14_DMA30_IRQHandler           = __default_handler
#pragma weak __DMA15_DMA31_IRQHandler           = __default_handler
#pragma weak __DMA_ERROR_IRQHandler             = __default_handler
#pragma weak __CTI0_ERROR_IRQHandler            = __default_handler
#pragma weak __CTI1_ERROR_IRQHandler            = __default_handler
#pragma weak __CORE_IRQHandler                  = __default_handler
#pragma weak __LPUART1_IRQHandler               = __default_handler
#pragma weak __LPUART2_IRQHandler               = __default_handler
#pragma weak __LPUART3_IRQHandler               = __default_handler
#pragma weak __LPUART4_IRQHandler               = __default_handler
#pragma weak __LPUART5_IRQHandler               = __default_handler
#pragma weak __LPUART6_IRQHandler               = __default_handler
#pragma weak __LPUART7_IRQHandler               = __default_handler
#pragma weak __LPUART8_IRQHandler               = __default_handler
#pragma weak __LPI2C1_IRQHandler                = __default_handler
#pragma weak __LPI2C2_IRQHandler                = __default_handler
#pragma weak __LPI2C3_IRQHandler                = __default_handler
#pragma weak __LPI2C4_IRQHandler                = __default_handler
#pragma weak __LPSPI1_IRQHandler                = __default_handler
#pragma weak __LPSPI2_IRQHandler                = __default_handler
#pragma weak __LPSPI3_IRQHandler                = __default_handler
#pragma weak __LPSPI4_IRQHandler                = __default_handler
#pragma weak __CAN1_IRQHandler                  = __default_handler
#pragma weak __CAN2_IRQHandler                  = __default_handler
#pragma weak __FLEXRAM_IRQHandler               = __default_handler
#pragma weak __KPP_IRQHandler                   = __default_handler
#pragma weak __TSC_DIG_IRQHandler               = __default_handler
#pragma weak __GPR_IRQ_IRQHandler               = __default_handler
#pragma weak __LCDIF_IRQHandler                 = __default_handler
#pragma weak __CSI_IRQHandler                   = __default_handler
#pragma weak __PXP_IRQHandler                   = __default_handler
#pragma weak __WDOG2_IRQHandler                 = __default_handler
#pragma weak __SNVS_HP_WRAPPER_IRQHandler       = __default_handler
#pragma weak __SNVS_HP_WRAPPER_TZ_IRQHandler    = __default_handler
#pragma weak __SNVS_LP_WRAPPER_IRQHandler       = __default_handler
#pragma weak __CSU_IRQHandler                   = __default_handler
#pragma weak __DCP_IRQHandler                   = __default_handler
#pragma weak __DCP_VMI_IRQHandler               = __default_handler
#pragma weak __TRNG_IRQHandler                  = __default_handler
#pragma weak __SJC_IRQHandler                   = __default_handler
#pragma weak __BEE_IRQHandler                   = __default_handler
#pragma weak __SAI1_IRQHandler                  = __default_handler
#pragma weak __SAI2_IRQHandler                  = __default_handler
#pragma weak __SAI3_RX_IRQHandler               = __default_handler
#pragma weak __SAI3_TX_IRQHandler               = __default_handler
#pragma weak __SPDIF_IRQHandler                 = __default_handler
#pragma weak __PMU_EVENT_IRQHandler             = __default_handler
#pragma weak __TEMP_LOW_HIGH_IRQHandler         = __default_handler
#pragma weak __TEMP_PANIC_IRQHandler            = __default_handler
#pragma weak __USB_PHY1_IRQHandler              = __default_handler
#pragma weak __USB_PHY2_IRQHandler              = __default_handler
#pragma weak __ADC1_IRQHandler                  = __default_handler
#pragma weak __ADC2_IRQHandler                  = __default_handler
#pragma weak __DCDC_IRQHandler                  = __default_handler
#pragma weak __GPIO1_INT0_IRQHandler            = __default_handler
#pragma weak __GPIO1_INT1_IRQHandler            = __default_handler
#pragma weak __GPIO1_INT2_IRQHandler            = __default_handler
#pragma weak __GPIO1_INT3_IRQHandler            = __default_handler
#pragma weak __GPIO1_INT4_IRQHandler            = __default_handler
#pragma weak __GPIO1_INT5_IRQHandler            = __default_handler
#pragma weak __GPIO1_INT6_IRQHandler            = __default_handler
#pragma weak __GPIO1_INT7_IRQHandler            = __default_handler
#pragma weak __GPIO1_Combined_0_15_IRQHandler   = __default_handler
#pragma weak __GPIO1_Combined_16_31_IRQHandler  = __default_handler
#pragma weak __GPIO2_Combined_0_15_IRQHandler   = __default_handler
#pragma weak __GPIO2_Combined_16_31_IRQHandler  = __default_handler
#pragma weak __GPIO3_Combined_0_15_IRQHandler   = __default_handler
#pragma weak __GPIO3_Combined_16_31_IRQHandler  = __default_handler
#pragma weak __GPIO4_Combined_0_15_IRQHandler   = __default_handler
#pragma weak __GPIO4_Combined_16_31_IRQHandler  = __default_handler
#pragma weak __GPIO5_Combined_0_15_IRQHandler   = __default_handler
#pragma weak __GPIO5_Combined_16_31_IRQHandler  = __default_handler
#pragma weak __FLEXIO1_IRQHandler               = __default_handler
#pragma weak __FLEXIO2_IRQHandler               = __default_handler
#pragma weak __WDOG1_IRQHandler                 = __default_handler
#pragma weak __RTWDOG_IRQHandler                = __default_handler
#pragma weak __EWM_IRQHandler                   = __default_handler
#pragma weak __CCM_1_IRQHandler                 = __default_handler
#pragma weak __CCM_2_IRQHandler                 = __default_handler
#pragma weak __GPC_IRQHandler                   = __default_handler
#pragma weak __SRC_IRQHandler                   = __default_handler
#pragma weak __GPT1_IRQHandler                  = __default_handler
#pragma weak __GPT2_IRQHandler                  = __default_handler
#pragma weak __PWM1_0_IRQHandler                = __default_handler
#pragma weak __PWM1_1_IRQHandler                = __default_handler
#pragma weak __PWM1_2_IRQHandler                = __default_handler
#pragma weak __PWM1_3_IRQHandler                = __default_handler
#pragma weak __PWM1_FAULT_IRQHandler            = __default_handler
#pragma weak __FLEXSPI2_IRQHandler              = __default_handler
#pragma weak __FLEXSPI_IRQHandler               = __default_handler
#pragma weak __SEMC_IRQHandler                  = __default_handler
#pragma weak __USDHC1_IRQHandler                = __default_handler
#pragma weak __USDHC2_IRQHandler                = __default_handler
#pragma weak __USB_OTG2_IRQHandler              = __default_handler
#pragma weak __USB_OTG1_IRQHandler              = __default_handler
#pragma weak __ENET_IRQHandler                  = __default_handler
#pragma weak __ENET_1588_Timer_IRQHandler       = __default_handler
#pragma weak __XBAR1_IRQ_0_1_IRQHandler         = __default_handler
#pragma weak __XBAR1_IRQ_2_3_IRQHandler         = __default_handler
#pragma weak __ADC_ETC_IRQ0_IRQHandler          = __default_handler
#pragma weak __ADC_ETC_IRQ1_IRQHandler          = __default_handler
#pragma weak __ADC_ETC_IRQ2_IRQHandler          = __default_handler
#pragma weak __ADC_ETC_ERROR_IRQ_IRQHandler     = __default_handler
#pragma weak __PIT_IRQHandler                   = __default_handler
#pragma weak __ACMP1_IRQHandler                 = __default_handler
#pragma weak __ACMP2_IRQHandler                 = __default_handler
#pragma weak __ACMP3_IRQHandler                 = __default_handler
#pragma weak __ACMP4_IRQHandler                 = __default_handler
#pragma weak __ENC1_IRQHandler                  = __default_handler
#pragma weak __ENC2_IRQHandler                  = __default_handler
#pragma weak __ENC3_IRQHandler                  = __default_handler
#pragma weak __ENC4_IRQHandler                  = __default_handler
#pragma weak __TMR1_IRQHandler                  = __default_handler
#pragma weak __TMR2_IRQHandler                  = __default_handler
#pragma weak __TMR3_IRQHandler                  = __default_handler
#pragma weak __TMR4_IRQHandler                  = __default_handler
#pragma weak __PWM2_0_IRQHandler                = __default_handler
#pragma weak __PWM2_1_IRQHandler                = __default_handler
#pragma weak __PWM2_2_IRQHandler                = __default_handler
#pragma weak __PWM2_3_IRQHandler                = __default_handler
#pragma weak __PWM2_FAULT_IRQHandler            = __default_handler
#pragma weak __PWM3_0_IRQHandler                = __default_handler
#pragma weak __PWM3_1_IRQHandler                = __default_handler
#pragma weak __PWM3_2_IRQHandler                = __default_handler
#pragma weak __PWM3_3_IRQHandler                = __default_handler
#pragma weak __PWM3_FAULT_IRQHandler            = __default_handler
#pragma weak __PWM4_0_IRQHandler                = __default_handler
#pragma weak __PWM4_1_IRQHandler                = __default_handler
#pragma weak __PWM4_2_IRQHandler                = __default_handler
#pragma weak __PWM4_3_IRQHandler                = __default_handler
#pragma weak __PWM4_FAULT_IRQHandler            = __default_handler
#pragma weak __ENET2_IRQHandler                 = __default_handler
#pragma weak __ENET2_1588_Timer_IRQHandler      = __default_handler
#pragma weak __CAN3_IRQHandler                  = __default_handler
#pragma weak __FLEXIO3_IRQHandler               = __default_handler
#pragma weak __GPIO6_7_8_9_IRQHandler           = __default_handler

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
