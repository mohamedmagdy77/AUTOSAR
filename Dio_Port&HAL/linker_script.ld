ENTRY(Reset_Handler)

MEMORY{
	FLASH(rx): ORIGIN =0x00000000 LENGTH =16K
	SRAM(rwx): ORIGIN =0x20000000 LENGTH =4K
}

__max_heap_size = 0X200;
__max_stack_size = 0X200;

SECTIONS
{
	.text :
	{
		*(.isr_vector)
		*(.text)
		. = ALIGN(4);
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
	}> FLASH
	
	.data :
	{
		_sdata = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;
	}> SRAM AT> FLASH
	
	.bss :
	{
		_sbss = .;
		*(.bss)
		. = ALIGN(4);
		_ebss = .;
	}> SRAM
}