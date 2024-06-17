SECTIONS
{
	.text :
	{
		*(.text.*AlignStack)
		*(.text.*Entry)
		*(.rdata*)
	}
}