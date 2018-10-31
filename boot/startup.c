int main();

void fatal_error_detected(const char *);

void __startup();

extern unsigned __stack_end();

void (*const volatile __vectors[8])(void)
__attribute__ ((section(".vectors"))) = {
                (void (*)(void)) &__stack_end,
                __startup
        };

void __attribute__((noreturn)) __startup() {
    extern unsigned int __data_init_start;
    extern unsigned int __data_start;
    extern unsigned int __data_end;
    extern unsigned int __bss_start;
    extern unsigned int __bss_end;

    unsigned int *s, *d, *e;

    // clear .bss section
    d = &__bss_start;
    e = &__bss_end;
    while (d != e) {
        *d++ = 0;
    }

    // copy .data section from flash to ram
    s = &__data_init_start;
    d = &__data_start;
    e = &__data_end;
    while (d != e) {
        *d++ = *s++;
    }

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
