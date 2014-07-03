# Author: Matthew Hoggan
# Date Created: Tuesday, Mar 6, 2012
.code16                    # Tell assembler to work in 16 bit mode (directive)
.section .text        
.globl _start              # Help linker find start of program
_start:                     
movb $0x0e,     %ah        # Function to print a character to the screen                 
movb $0x00,     %bh        # Indicate the page number
movb $0x07,     %bl        # Text attribute
mov  $'A',      %al        # Move data into low nibble                   
int  $0x10                 # Video Service Request to Bios                             
_hang:                                                                                  
jmp  _hang                                                                           
.end  */
