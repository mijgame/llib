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

   @ ldr r0, [ r0 ]
   @ mov r1, #16
   @ bl print_stack

   @ ldr r3, =_switch
   @ ldr r0, [ r3, #0x4 ]
   @ mov r1, #16
   @ bl print_stack

   # flush stack pointers
   isb

   # return from interrupt
   bx lr