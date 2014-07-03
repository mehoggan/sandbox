# Author: Matthew Hoggan
# Date Created: Tuesday, Mar 6, 2012
.code16                        # Tell assembler to work in 16 bit mode (directive)

.section .data
msg:                           # Message to be printed to the screen
  .asciz "hello, world"

.section .text        
.globl _start                  # Help linker find start of program
_start:
    mov  $0x0000,   %ax
    mov  %ax,       %es        # es will be used for segment where msg is
    mov  $msg,      %si        # point si at start of msg
    mov  $0xb800,   %ax     
    mov  %ax,       %ds        # ds will be used to point to video text mode buffer segment
    xor  %di,       %di        # 0 out di -- to point at begining of video text mode buffer

_loop:
    movb %es:(%si), %al        # Move character pointed to in %es + %si to %al for comparison
    inc  %si                   # Advance %si to point to next char
    or   %al,       %al        # See if we are at null terminated string
    jz   _hang;                # Infinite loop if at end of string

    mov  %al,       %ds:(%di)  # Move actuall data into %di
    inc  %di                   # Advnace %si to point to next spot in buffer

    movb $0x1e,     %al
    mov  %al,       %ds:(%di)  # Move color attribute for text into next slot in buffer    
    inc  %di                   # %di += 2: One for data one for color attribute

    jmp  _loop
    
_hang:                                                                                  
    jmp  _hang                                                                           
.end 
