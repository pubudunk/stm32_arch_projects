ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rw):ORIGIN =0x08000000, LENGTH =2048K
	SRAM(rwx):ORIGIN =0x20000000, LENGTH =192K
}

SECTIONS
{
	.text :
	{
		*(.isr_vector)
		*(.text)
		*(.text.*)		/* added to include sub text section introduced by C lib */
		*(.init)		/* merge additional text sections. not mandetory */
		*(.fini)		/* merge additional text sections. not mandetory */
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);	/* align to next word boundary */	
		_etext = .;  	/* use the location counter will contain the updated VMA address info of the .text section */
	} > FLASH
	
	_la_data = LOADADDR(.data);
	.data :
	{
		_sdata = .;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = .;
	} > SRAM AT > FLASH
	
	.bss :
	{
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
		. = ALIGN(4);
		end = .;
	} > SRAM
}