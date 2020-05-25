   .arch armv4t
   .syntax unified
   .global __vectors

.section .vectors
.align 4
__vectors:
   b __internal_reset_handler
   b __undef_addr
   b __software_interrupt
   b __prefetch_abort
   b __data_abort
   nop
   b __arm_irq
   b __arm_fiq

.text
.align 4
__internal_reset_handler:
   // init the stack before we call the
   // reset handler as we cannot be 
   // sure that c++ will not use the stack 
   // this needs to be run as assembly
   ldr r0, =__stack_end

   // bit 6 and 7 are the IRQ and FIQ 
   // disable bits when these bits are
   // set they are disabled (msr cpsr_c)

   // Enter Undefined Instruction Mode and
   // set its Stack Pointer
   msr cpsr_c, #0xdb
   mov sp, r0
   sub r0, 0x10

   // Enter Abort Mode and set its Stack 
   // Pointer
   msr cpsr_c, #0xd7
   mov sp, r0
   sub r0, 0x10

   // Enter FIQ Mode and set its Stack 
   // Pointer
   msr cpsr_c, #0xd1
   mov sp, r0
   sub r0, 0x10

   // Enter IRQ Mode and set its Stack 
   // Pointer
   msr cpsr_c, #0xd2
   mov sp, r0
   sub r0, 0x200

   // Enter Supervisor Mode and set its 
   // Stack Pointer
   msr cpsr_c, #0xd3
   mov sp, r0
   sub r0, 0x10

   // Enter User Mode and set its Stack 
   // Pointer
   msr cpsr_c, 0xd0
   mov sp, r0

   // limit the stack on the stack size
   // sl = r10 = stack limit pointer
   ldr r1, =__stack_size
   sub sl, sp, r1

   // branch to the __reset_handler to
   // finish the setup of the chip
   b __reset_handler