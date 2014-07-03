SECTIONS
{
    /*
     * Set location counter to 0x7c00 where
     * BIOS looks for start of boot sector
     */
    . = 0x7c00;
    /* 
     * Next section is the text
     * followed by the data
     */
    .text : { *(.text) }
    .data : { *(.data) }
    .other : 
    {
      FILL(0x000000)
      . = 0x1D5;
      BYTE(0x55)
      BYTE(0xAA)
    }
}
