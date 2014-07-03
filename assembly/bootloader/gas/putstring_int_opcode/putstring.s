# Author: Matthew Hoggan
# Date Created: Tuesday, Mar 6, 2012
.code16                        # Tell assembler to work in 16 bit mode (directive)

.section .data
msg:                           # Message to be printed to the screen
  .asciz "hello, world"

.section .text        
.globl _start                  # Help linker find start of program
_start:
    xor  %ax,       %ax        # We need a 0 for %ds
    movw %ax,       %ds        # Set data segment to 0
    mov  $msg,      %si        # Point %si at our data

_loop:
    movb %ds:(%si), %al        # Move the nth char to register use for data on int 0x10
    or   %al,       %al        # Make sure this is not the end of the data
    jz   _hang;                # Loop infinetly if it is
    inc  %si                   # Point %si at next character/btye
    call _putchar              # _putchar handles bios function to output contents of %al
    jmp  _loop                 # Repeat
                
_putchar:  
    movb $0x00,     %bh        # Indicate the page number
    movb $0x07,     %bl        # Text attribute
    movb $0x0e,     %ah        # Function to print a character to the screen                 
    movb $0x07,     %bl        # Text attribute

    int  $0x10                 # Video Service Request to Bios                             
    ret

_hang:                                                                                  
jmp  _hang                                                                           
.end  */
