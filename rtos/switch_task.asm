   .cpu cortex-m3
   .syntax unified
	.thumb
	.thumb_func   
   .global __pendsv_handler
   .text
   .align 2
   
__pendsv_handler:
    # get the current and next stack locations
    ldr r3, =_switch

    # *old_sp
    ldr r0, [ r3, #0 ]
    # new_sp
    ldr r1, [ r3, #4 ]

    # get process stack pointer
    mrs r2, PSP

    # save current context on the old stack
    stmdb r2!, { r4 - r11 }

    # store the new location for later use
    str r2, [ r0 ]

    # restore the new context from the stack
    ldmia r1!, { r4 - r11 }

    # **current
    ldr r0, [ r3, #8 ]
    # **next
    ldr r3, [r3, #12 ]

    # *next
    ldr r3, [ r3 ]
    # current = next
    str r3, [ r0 ]

    # update the new stack pointer
    msr PSP, r1

    # flush stack pointers
    isb
    dsb

    # return from interrupt
    bx lr