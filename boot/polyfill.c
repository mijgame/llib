#include <limits.h>
#include <stdlib.h>

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
    __uint8_t *a = (__uint8_t *) ptr1;
    __uint8_t *b = (__uint8_t *) ptr2;

    while (num--) {
        int r = *(a++) - *(b++);

        if (r != 0) {
            return r;
        }
    }

    return 0;
}

void *memset(void *ptr, int value, size_t num) {
    // According to the standard, the value is interpreted as
    // a unsigned char.
    __uint8_t v8 = (__uint8_t) value;

    if ((__uint32_t) ptr % sizeof(__uint32_t) == 0) {
        /*
         * First, set 4 bytes at a time, then
         * set the remaining bytes.
         */
        __uint32_t v32 = (v8 << 24 | v8 << 16 | v8 << 8 | v8);

        __uint32_t *lp = (__uint32_t *) ptr;
        while ((num / 4) > 0) {
            *(lp++) = v32;
            num -= 4;
        }

        __uint8_t *sp = (__uint8_t *) lp;
        while (num--) {
            *(sp++) = v8;
        }
    } else {
        __uint8_t *sp = (__uint8_t *) ptr;
        while (num--) {
            *(sp++) = v8;
        }
    }

    return ptr;
}

void *memcpy(void *destination, const void *source, size_t num) {
    if ((__uint32_t) destination % sizeof(__uint32_t) == 0
        && (__uint32_t) source % sizeof(__uint32_t) == 0) {
        /*
         * First, copy 4 bytes at a time, then
         * set the remaining bytes.
         */
        __uint32_t *ld = (__uint32_t *) destination;
        __uint32_t *ls = (__uint32_t *) source;
        while ((num / 4) > 0) {
            *(ld++) = *(ls++);
            num -= 4;
        }

        __uint8_t *ss = (__uint8_t *) ls;
        __uint8_t *sd = (__uint8_t *) ld;
        while (num--) {
            *(sd++) = *(ss++);
        }
    } else {
        // Byte by byte copy
        __uint8_t *sd = (__uint8_t *) destination;
        __uint8_t *ss = (__uint8_t *) source;
        while (num--) {
            *(sd++) = *(ss++);
        }
    }

    return destination;
}

void *memmove(void *destination, const void *source, size_t num) {
    if (destination < source) {
        // Destination starts before source; copy forwards. memcpy copies forwards.
        memcpy(destination, source, num);
    } else {
        // Memory alignment
        if ((__uint32_t) destination % sizeof(__uint32_t) == 0
            && (__uint32_t) source % sizeof(__uint32_t) == 0) {
            // Destination starts after source; copy backwards
            __uint32_t *ld = (__uint32_t *) destination + num - 1;
            __uint32_t *ls = (__uint32_t *) source + num - 1;

            while ((num / 4) > 0) {
                *(ld--) = *(ls--);
                num -= 4;
            }

            __uint8_t *ss = (__uint8_t *) ls;
            __uint8_t *sd = (__uint8_t *) ld;
            while (num--) {
                *(sd--) = *(ss--);
            }
        } else {
            // Byte by byte copy
            __uint8_t *sd = (__uint8_t *) destination + num - 1;
            __uint8_t *ss = (__uint8_t *) source + num - 1;

            while (num--) {
                *(sd--) = *(ss--);
            }
        }
    }

    return destination;
}