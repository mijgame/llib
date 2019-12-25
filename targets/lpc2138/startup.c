// PLL pointers
#define PLLCON         (*((volatile unsigned char *) 0xE01FC080))
#define PLLCFG         (*((volatile unsigned char *) 0xE01FC084))
#define PLLSTAT        (*((volatile unsigned short*) 0xE01FC088))
#define PLLFEED        (*((volatile unsigned char *) 0xE01FC08C))

// PLL Enable
#define PLLCON_PLLE (1<<0)
// PLL Connect
#define PLLCON_PLLC (1<<1)
//PLL Multiplier
#define PLLCFG_MSEL (0x1F<<0)
// PLL Divider
#define PLLCFG_PSEL (0x03<<5)
// PLL Lock Status
#define PLLSTAT_PLOCK (1<<10)

// Memory Accelerator Module pointers
#define MAMCR          (*((volatile unsigned char *) 0xE01FC000))
#define MAMTIM         (*((volatile unsigned char *) 0xE01FC004))

void __target_startup() {
    // VPBDIV = 0x00;

    // configure and enable the pll
    PLLCFG = 0x24;
    PLLCON = PLLCON_PLLE;
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    // wait until the pll is locked
    while (!(PLLSTAT & PLLSTAT_PLOCK)) {}

    // switch to pll clock
    PLLCON = 0x03;
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    // Memory mapping setup
    MAMTIM = 0x04;
    MAMCR = 0x2;
}