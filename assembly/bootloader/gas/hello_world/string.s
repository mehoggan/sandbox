# Author: Matthew Hoggan
# Date Created: Tuesday, Mar 6, 2012

.code16                      # Tell assembler to work in 16 bit mode (directive)

.section .text        
.globl _start                # Help linker find start of program
_start:                     
  xor  %ax,  %ax             # Zero out ax register (ah used to specify bios function to Video Services) 
  movw %ax,  %ds             # Since ax is 0x00 0x00 use it to set data segment to 0
  mov  $msg, %si             # Use source index as pointer to string

loop:
  movb %ds:(%si), %al        # Pass data to BIOS function in low nibble of ax
  inc  %si                   # Advance the pointer
  or   %al, %al              # If byte stored in al is equal to zero then...
  jz   _hang                 # Zero signifies end of string
  call print_char            # Print current char in al
  jmp loop                   # Repeat

#
# Function that uses bios function calls
# to print char to screen
#
print_char:
  movb $0x0e, %ah             # Function to print a character to the screen
  movb $0x07, %bl             # color/style to use for the character
  int  $0x10                  # Video Service Request to Bios
  ret

#
# Function used as infinite loop
#
_hang:
  jmp  _hang

.section .data
msg:                         # Message to be printed to the screen
  .asciz "hello, world"
.end
