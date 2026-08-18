ENTRY(_start)

SECTIONS
{
	. = 1M;
	.text :
	{
		KEEP(*(.multiboot))
	}

	.rodata :
	{
		*(.rodata)
	}	

	.data :
	{
		*(.data)	
	}

	.bss :
	{
		*(.bss)
	}

	_kernel_end = .;
}
