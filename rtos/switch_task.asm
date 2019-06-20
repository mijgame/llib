   .cpu cortex-m3
   .syntax unified
   .global __pendsv_handler
   .global _switch
   
.bss
.align 2
_switch: 
   .word 0x00000000 
   .word 0x00000000

.text
.align 2
__pendsv_handler:
   # get the current and next stack locations
   ldr r3, =_switch

   # &old->sp
   ldr r0, [ r3, #0x0 ]
   # next->sp, r3 not required anymore
   ldr r1, [ r3, #0x4 ]

   # get process stack pointer
   mrs r2, PSP

   # save current context on the old stack
   stmdb	r2!, { r4 - r11 }

   # store the new location for later use
   str r2, [ r0 ]

   # restore the new context from the stack
   ldmia r1!, { r4 - r11 }

   # update the new stack pointer
   msr PSP, r1

   # flush stack pointers
   isb

   # return from interrupt
   bx lr