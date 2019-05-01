/******************************************************************************

* author: Freddie Chopin, http://www.freddiechopin.info/

* file: lpc1114_rom.ld

* last change: 2010-10-13

*

* chip: LPC1114

* compiler: arm-none-eabi-gcc (Sourcery G++ Lite 2010q1-188) 4.4.1

*

* description:

* Linker script for LPC1114 chip (/301 version) (32kB Flash, 4kB SRAM).

******************************************************************************/
SEARCH_DIR(.);
/*

+=============================================================================+

| format configurations

+=============================================================================+

*/
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm");
OUTPUT_ARCH(arm);


/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = 73728;

/*

+=============================================================================+

| available memories definitions

+=============================================================================+

*/
MEMORY
{
	rom (rx) : org = 0x00000000, len = 512k
	ram (rwx) : org = 0x20070000, len = 96k
}
__rom_start = ORIGIN(rom);
__rom_size = LENGTH(rom);
__rom_end = __rom_start + __rom_size;
__ram_start = ORIGIN(ram);
__ram_size = LENGTH(ram);
__ram_end = __ram_start + __ram_size;
/*

+=============================================================================+

| entry point

+=============================================================================+

*/
ENTRY( __reset_handler );
/*

+=============================================================================+

| put data in sections

+=============================================================================+

*/
SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		__text_start = .;
		KEEP(*(.vectors .vectors.*))
		*(.text .text.* .gnu.linkonce.t.*); /* text segment */
		*(.glue_7t .glue_7); /* glue arm to thumb code, glue thumb to arm code*/
		*(.rodata .rodata.* .gnu.linkonce.r.*); /* Constands, strings, etc */
		*(.ARM.extab* .gnu.linkonce.armextab.*); /* exception unwinding information */

        /* Support C constructors, and C destructors in both user code
           and the C library. This also provides support for C++ code. */		
		. = ALIGN(4);
		KEEP(*(.init));
		. = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;		

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))

        . = ALIGN(4);

		*(.gcc_except_table); /* information used for stack unwinding during exception */
		. = ALIGN(4);
		*(.eh_frame_hdr); /* additional information about .ex_frame section */
		. = ALIGN(4);
		*(.eh_frame); /* information used for stack unwinding during exception */
		. = ALIGN(4);
		__text_end = .;
	} > rom

	. = ALIGN(4);
	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*);
	} > rom	
	. = ALIGN(4);
	__exidx_end = .;	

	.stack (NOLOAD) :
	{
		. = ALIGN(4);
		__stack_start = .;
		. = ALIGN(4);
		. = . + STACK_SIZE;
		. = ALIGN(8);
		__main_stack_end = .;
		. = ALIGN(4);
		__stack_end = .;
	} > ram

	.bss (NOLOAD) :
	{
		. = ALIGN(4);
		__bss_start = .;
		. = ALIGN(4);
		*(.bss .bss.* .gnu.linkonce.b.*)
		. = ALIGN(4);
		*(COMMON);
		. = ALIGN(4);
		__bss_end = .;
	} > ram

	.data :
	{
		. = ALIGN(4);
		__data_init_start = LOADADDR (.data);
		__data_start = .;
		. = ALIGN(4);
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN(4);
		__data_end = .;
		__data_init_end = LOADADDR (.data);
	} > ram AT > rom

	.heap (NOLOAD) :
	{
		. = ALIGN(4);
		__heap_start = .;
		. = ALIGN(4);
		__heap_end = __ram_end;
	} > ram

    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 : { *(.ARM.attributes) }

	.stab 0 (NOLOAD) : { *(.stab) }
	.stabstr 0 (NOLOAD) : { *(.stabstr) }
	/* DWARF debug sections.

	* Symbols in the DWARF debugging sections are relative to the beginning

	* of the section so we begin them at 0. */
	/* DWARF 1 */
	.debug 0 : { *(.debug) }
	.line 0 : { *(.line) }
	/* GNU DWARF 1 extensions */
	.debug_srcinfo 0 : { *(.debug_srcinfo) }
	.debug_sfnames 0 : { *(.debug_sfnames) }
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges 0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	/* DWARF 2 */
	.debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_line 0 : { *(.debug_line) }
	.debug_frame 0 : { *(.debug_frame) }
	.debug_str 0 : { *(.debug_str) }
	.debug_loc 0 : { *(.debug_loc) }
	.debug_macinfo 0 : { *(.debug_macinfo) }
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames 0 : { *(.debug_varnames) }
	.note.gnu.arm.ident 0 : { KEEP(*(.note.gnu.arm.ident)) }
	.ARM.attributes 0 : { KEEP(*(.ARM.attributes)) }
	/DISCARD/ : { *(.note.GNU-stack) }
}
PROVIDE(__text_size = __text_end - __text_start);
PROVIDE(__exidx_size = __exidx_end - __exidx_start);
PROVIDE(__bss_size = __bss_end - __bss_start);
PROVIDE(__stack_size = __stack_end - __stack_start);
PROVIDE(__heap_size = __heap_end - __heap_start);
