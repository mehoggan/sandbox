; Executable name : hexdump3
; Version         : 1.0
; Created date    : 4/15/2009
; Last update     : 4/20/2009
; Author          : Jeff Dunteman
; Description     : A simple hex dump utility demonstrating the use of
;                   assembly language procedures
;
; Build using these commands:
;   nasm -f elf -g -F stabs hexdum2.asm
;   ld -o hexdump2 hexdump2.o
;

SECTION .data

SECTION .bss                                                                   ; Section containing uninitialized data

SECTION .text

EXTERN ClearLine, DumpChar, PrintLine, LoadBuff, Buff

global _start

;-----------------------------------------------------------------------------
; MAIN PROGRAM BEGINS HERE
;-----------------------------------------------------------------------------
_start:
  nop                                                                          ; No-ops for GDB
  nop

; Whatever initialization needs doing before the loops can start is here:
  xor esi, esi                                                                 ; Clear total byte counter to 0
  call LoadBuff                                                                ; Read first buffer of data from stdin
  cmp ebp, 0x00                                                                ; If ebp=0 sys_read reached EOF on stdin
  jbe Exit

; Go through the buffer and convert binary byte values to hex digits:
Scan:
  xor eax, eax                                                                 ; Clear EAX to 0
  mov al, byte[Buff+ecx]                                                       ; Get a byte from the buffer into AL
  mov edx, esi                                                                 ; Copy total counter into EDX
  and edx, 0x0000000F                                                          ; Mask out 4 bits of char counter
  call DumpChar                                                                ; Call the char poke procedure

; Bump the buffer pointer tothe next character and see if buffer's done:
  inc esi                                                                      ; Increment total chars processed counter
  inc ecx                                                                      ; Increment buffer pointer
  cmp ecx, ebp                                                                 ; Compare with # of chars in buffer
  jb .modTest                                                                  ; If we've processed all chars in buffer...
  call LoadBuff                                                                ; ...go fill the buffer again
  cmp ebp, 0x00                                                                ; If ebp=0, sys_read reached EOF on stdin
  jbe Done                                                                     ; If we got EOF, we're done
  

; See if we're at the end of a block of 16 and need to display a line:
.modTest:
  test esi, 0x0000000F                                                         ; Test 4 lowst bits in counter for 0
  jnz Scan                                                                     ; If counter is *not* modulo 16, loop back
  call PrintLine                                                               ; ...otherwise print the line
  call ClearLine                                                               ; Clear hex dump line to 0's
  jmp Scan                                                                     ; Continue scanning the buffer

; All done! Let's end this party:
Done:
  call PrintLine                                                               ; Print the "leftovers" line
Exit: 
  mov eax, 0X01                                                                ; Code for Exit Syscall
  mov ebx, 0x00                                                                ; Return a code of zero
  int 0x80                                                                     ; Make kernel call
   
































