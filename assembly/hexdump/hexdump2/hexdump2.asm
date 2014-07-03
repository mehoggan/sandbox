; Executable name : hexdump2
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

SECTION .bss                                                                   ; Section containing uninitialized data
  BUFFLEN equ 10
  Buff resb BUFFLEN

SECTION .data                                                                  ; Section containing initialized data

; Here we have two parts of a single useful data structure, implementing
; the text line of a hex dump utility. The first part displays 16 bytes in
; hex separated by spaces. Immediately following is a 16-character line
; delimited by vertical bar characters. Because they are adjacent, the two
; parts can be referenced separately or as a single contiguous unit.
; Remember that if DumLin is to be used separately, you must append an 
; EOL before sending it to the Linux console.

DumpLin: db " 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
DUMPLEN equ $-DumpLin
ASCLin: db "|................|",0x0A
ASCLEN equ $-ASCLin
FULLLEN equ $-DumpLin

; The HexDigits table is used to convert numericvalus to their hex 
; equivalents. Index by nybble without a scale: [HexDigits+eax]
HexDigits: db "0123456789ABCDEF"

; This table is used for ASCII character translation, into the ASCII
; portion of the hex dump line. via XLAT or ordinary memroy lookup.
; All printable characters "play through" as themselves. The high 128
; characters are translated to ASCII period (2Eh). The non-printable
; characters in the low 128 are also translated to ASCII period, as is 
; char 127.
DotXlat:
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F
  db 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F
  db 0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F
  db 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F
  db 0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F
  db 0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
  db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E

SECTION .text                                                                  ; Section containing code

;-----------------------------------------------------------------------------
; ClearLine   : Clear a hex dump line string to 16 0 values
; UPDATED     : 4/15/2009
; IN:         : Nothing
; RETURNS     : Nothing
; MODIFIERS   : Nothing
; Calls       : DumpChar
; Description : The hex dump line string is cleared to binary 0 by
;               calling DumpChar 16 times, passing it 0 each time
ClearLine:
  pushad                                                                       ; Save all caller's GP registers
  mov edx, 0x0F                                                                ; Store a counter into edx (i = 15)
  .poke: mov eax, 0x00                                                         ; Set the paramater to pass to DumChar to 0
  call DumpChar                                                                ; Insert the '0' into the hex dump string
  sub edx,1                                                                    ; DEC doesn't affect CF!
  jae .poke                                                                    ; Loop back if EDX >= 0
  popad                                                                        ; Restore all caller's GP registers
  ret                                                                          ; Return back to caller

;-----------------------------------------------------------------------------
; DumpChar    : "Poke" a value into the hex dump line string.
; UPDATED:    : 4/15/2009
; IN          : Pass the 8-bit value to be poked in EAX
;               Pass the value's position in the line (0-15) in EDX
; RETURNS     : Nothing
; MODIFIERS   : EAX, ASCLin, DumpLin
; CALLS       : Nothing
; DESCRIPTION : The value passed in EAX will be put in both the hex dump
;               portion and in the ASCII portion, at the position passed 
;               in EDX, represented by a space where it is not a printable
;               character
DumpChar:
  push ebx                                                                     ; Save caller's EBX
  push edi                                                                     ; Save caller's EDI
;First we insert the input char into the ASCII portion of the dump line
  mov bl, byte[DotXlat+eax]                                                    ; Translate non printables to '.'
  mov byte[ASCLin+edx+1], bl                                                  ; Write to ASCII portion
; Next we insert the hex equivalent of the input char in the hex portion
; of the hex dump line:
  mov ebx, eax                                                                 ; Save a second copy of the input char
  lea edi, [edx*2+edx]                                                         ; Calc offset into line string (EDX X 3)
; Look up low nybble character and insert it into the string
  and eax, 0x0000000F                                                          ; Mask out all by low nybble
  mov al, byte[HexDigits+eax]                                                  ; Lookup the char equivalent of nybble
  mov byte[DumpLin+edi+2], al                                                  ; Write the char equivalent to line string
; Look up high nybble character and insert it into the string
  and ebx, 0x0000000F                                                          ; Mask out all the but second-lowest nybble
  shr ebx, 0x04                                                                ; Shift high 4 bits of byte into low 4 bits
  mov bl, byte[HexDigits+ebx]                                                  ; Look up char equivalent of nybble
  mov byte[DumpLin+edi+1], bl                                                  ; Write the char equivalent to line string
; Done! Let's go home:
  pop edi                                                                      ; Restore caller's EDI
  pop ebx                                                                      ; Restore caller's EBX
  ret                                                                          ; Return to caller

;-----------------------------------------------------------------------------
; PrintLine   : Displays DumpLin to stdout
; UPDATED     : 4/15/2009
; IN          : Nothing
; RETURNS     : Nothing
; MODIFIES    : Nothing
; CALLS       : Kernel sys_write
; DESCRIPTION : The hex dump line string DumpLin is displayed to stdout
;               using INT 80h sys_write. All GP registers are preserved.
PrintLine:
  pushad                                                                       ; Save all caller's GP registers
  mov eax, 0x04                                                                ; Specify sys_write call
  mov ebx, 0x01                                                                ; Specify file descriptor 1: stdout
  mov ecx, DumpLin                                                             ; Pass offset of line string
  mov edx, FULLLEN                                                             ; Pass size of the line string
  int 0x80                                                                     ; Make kernel call to display line string
  popad                                                                        ; Restore all caller's GP registers
  ret                                                                          ; Return to caller

;-----------------------------------------------------------------------------
; LoadBuff    : Fills a buffer with data from stdin via INT 80h sys_read
; UPDATED     : 4/15/2009
; IN          : Nothing
; RETURNS     : # of bytes read in EBP
; MODIFIES    : ECX, EBP, Buff
; CALLS       : Kernel sys_write
; DESCRIPTION : Loads a buffer full of data (BUFFLEN bytes) from stdin
;               using INT 80h sys_read and places it in Buff. Buffer
;               offset counter ECX is zeroed, because we're starting in
;               on a new buffer full of data. Caller must test value in
;               EBP: If EBP contains zero or return, we hit EOF on stdin.
;               Less than 0 in EBP on return indicates some kind of error
LoadBuff:
  push eax                                                                     ; Save caller's EAX
  push ebx                                                                     ; Save caller's EBX
  push edx                                                                     ; Save caller's EDX
  mov eax, 0x03                                                                ; Specify sys_read call
  mov ebx, 0x00                                                                ; Specify file descriptor 0: Standard Input
  mov ecx, Buff                                                                ; Pass offset of the buffer to read to
  mov edx, BUFFLEN                                                             ; Pass number of bytes to read at one pass
  int 0x80                                                                     ; Make kernel call to fill buffer
  mov ebp, eax                                                                 ; Save # of bytes read from file for later
  xor ecx, ecx                                                                 ; Clear buffer pointer ECX to 0
  pop edx                                                                      ; Restore callers EDX
  pop ebx                                                                      ; Restore callers EBX
  pop eax                                                                      ; Restore callers EAX
  ret                                                                          ; And return to caller


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
   
































