SECTIONS
{
    /* Set location counter to 0x7c00 */
    . = 0x7c00;
    .text : { *(.text) }
    .data : { *(.data) }
    .other : 
    {
      FILL(0x000000)
      . = 0x1D1;
      BYTE(0x55)
      BYTE(0xAA)
    }
}
