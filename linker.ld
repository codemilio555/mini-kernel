ENTRY(_start)

SECTIONS
{
	. = 1M;
		.multiboot :
		{
			KEEP(*(.multiboot))
		}	
		.text :
		{
			*(.text)
		}

		.data :
		{
			*(.data)	
		}
		
		.rodata :
		{
			*(.rodata)
		}	

		.bss :
		{
			*(.bss)
		}
}
