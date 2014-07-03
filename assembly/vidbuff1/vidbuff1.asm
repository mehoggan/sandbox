; Executable name : vidbuff1
; Version         : 1.0
; Created date    : 5/11/2009
; Last update     : 5/14/2009
; Author          : Jeff Duntemann
; Description     : A simple program in assembly for Linux, using NASM 2.05,
;                   deomonstrating string instruction operation by "faking"
;                   full-screen
;
; Build using these commands:
;   nasm -f elf -g -F stabs vidbuff1.asm
;   ld -o vidbuff1 vidbuff1.o

SECTION .data
  EOL equ 0x0A
  FILLCHR equ 0x20
  HBARCHR equ 0xC4
  STRTROW equ 0x02

; The dataset is just a table of byte-length numbers:
  Dataset db 9,71,17,52,55,18,29,36,18,68,77,63,58,44,0

  Message db "Data current as of 5/13/2009"
  MSGLEN equ $-Message

; This escape sequence will clear the console terminal and place the
; text cursor to the origin (1,1) on virtually all Linux consoles:
  ClrHome db 27,"[2J",27,"[01;01H"
  CLRLEN equ $-ClrHome

SECTION .bss
  COLS equ 0x51
  ROWS equ 0x19
  VidBuff resb COLS*ROWS

SECTION .text
  global _start

; This macro clears the Linux console terminal and sets teh cursor position
; to 1,1, using a single predefined escape sequence.
%macro ClearTerminal 0
  pushad
  mov eax, 0x04
  mov ebx, 0x01
  mov ecx, ClrHome
  mov edx, CLRLEN
  int 0x80
  popad
%endmacro


;-----------------------------------------------------------------------------
; Show:        Display a text buffer to the Linux console
; UPDATED:     5/13/2009
; IN:          Nothing
; RETURNS:     Nothing
; MODIFIES:    Nothing
; CALLS:       Linux sys_write
; DESCRIPTION: Send the buffer vidBuff to the Linux console via sys_write.
;              The number of bytes sent to the console is calculated by 
;              multiplying the COLS equate by the ROWS equate
Show: 
  pushad
  mov eax, 0x04
  mov ebx, 0x01
  mov ecx, VidBuff
  mov edx, COLS*ROWS
  int 0x80
  popad
  ret

;-----------------------------------------------------------------------------
; ClrVid:      Clears a text buffer to spaces and replaces all EOLs
; UPDATED:     5/13/2009
; IN:          Nothing
; RETURNS:     Nothing
; MODIFIES:    VidBuff, DF
; CALLS:       Nothing
; DESCRIPTION: Fills the buffer VidBuff with a predefined character
;              (FILLCHR) and then places an EOL character at the end
;              of every line, where a line ends every COLS bytes in 
;              VidBuff.
ClrVid:
  push eax
  push ecx
  cld
  mov al, FILLCHR
  mov edi, VidBuff
  mov ecx, COLS*ROWS
  rep stosb
;Buffer is cleared; now we need to re-insert the EOL char after each line;
  mov edi, VidBuff
  dec edi
  mov ecx, ROWS
PtEOL:
  add edi, COLS
  mov byte[edi], EOL
  loop PtEOL
  pop edi
  pop ecx
  pop eax
  ret

;-----------------------------------------------------------------------------
; WrtLn:       Writes a string to a text buffer at a 1-based X,Y position
; UPDATED:     5/13/2009
; IN:          The address of the string is passed in ESI
;              The 1-based X position (row #) is passed in EAX
;              The 1-based Y position (colum #) is passed in EAX
;              The length of the string in chars is passed in ECX
; RETURNS:     Nothing
; MODIFIES:    VidBuff, EDI, DF
; CALLS:       Nothing
; DESCRIPTION: Uses REP MOVSB to copy a string from the address in ESI
;              to an X,Y location in the text buffer VidBuff.
WrtLn:
  push eax
  push ebx
  push ecx
  push edi
  cld
  mov edi, VidBuff
  dec eax
  dec ebx
  mov ah, COLS
  mul ah
  add edi, eax
  add edi, ebx
  rep movsb
  pop edi
  pop ecx
  pop ebx
  pop eax
  ret

;-----------------------------------------------------------------------------
; WrtHB:       Generates a horizontal line bar at X,Y in text buffer
; UPDATED:     5/13/2009
; IN:          The 1-based X position (row #) is passed in EBX
;              The 1-based Y position (column #) is passed in EAX
;              The length of the bar in chars is passed in ECX
; RETURNS:     Nothing
; MODIFIES:    VidBuff, DF
; CALLS:       Nothing
; DESCRIPTION: Writes a horizontal bar to the video buffer VidBuff,
;              at the 1-based X,Y values passed in EBX, EAX. The bar is
;              "made of" the character in the equate HBARCHR. The
;              default is character 196; if your terminal won't display
;              that (you need the IBM 850 character set) change the 
;              value in HBARCHR to ASCII dash or something else supported
;              in your terminal.
WrtHB: 
  push eax
  push ebx
  push ecx
  push edi
  cld
  mov edi, VidBuff
  dec eax
  dec ebx
  mov ah, COLS
  mul ah
  add edi, eax
  add edi, ebx
  mov al, HBARCHR
  rep stosb
  pop edi
  pop ecx
  pop ebx
  pop eax
  ret

;-----------------------------------------------------------------------------
; Ruler:       Generate a "1234567890"-style ruler at X,Y in text buffer
; UPDATED:     5/13/2009
; IN:          The 1-based X position (row #) is passed in EBX
;              The 1-based Y position (column #) is passed in EAX
;              The length of the ruler in chars is passed in ECX
; RETURNS:     Nothing
; MODIFIES:    VidBuff
; CALLS:       Nothing
; DESCRIPTION: Writes a ruler to the video buffer VidBuff, at the 1-based
;              X,Y position passed in EBX, EAX. The ruler consists of a 
;              repeating sequence of the digits 1 through 0. The ruler
;              will wrap to subsequent lines and overwrite whatever EOL
;              characters fall within its length, if it will not fit
;              entirely on the line where it begins. Note that the Show
;              procedure must be called after Ruler to display the ruler
;              on the console
Ruler:
  push eax
  push ebx
  push ecx
  push edi
  mov edi, VidBuff
  dec eax
  dec ebx
  mov ah, COLS
  mul ah
  add edi, eax
  add edi, ebx
; EDI now contains the memory address in the buffer where the ruler
; is to begin. Now we display the ruler, starting at that position:
  mov al, '1'
DoChar:
  stosb
  add al, '1'
  aaa
  add al, '0'
  loop DoChar
  pop edi
  pop ecx
  pop ebx
  pop eax
  ret

;-----------------------------------------------------------------------------
; MAIN PROGRAM:

_start:
  nop

; Get the console and text display text buffer ready to go:
  ClearTerminal
  call ClrVid

; Next we display the top ruler:
  mov eax, 0x01
  mov ebx, 0x01
  mov ecx, COLS-1
  call Ruler

; Here we loop through the dataset and graph the data:
  mov esi, Dataset
  mov ebx, 0x01
  mov ebx, 0x00
.blast:
  mov eax, ebp
  add eax, STRTROW
  mov cl, byte[esi+ebp]
  cmp ecx, 0x00
  je .rule2
  call WrtHB
  inc ebp
  jmp .blast
  
; Display the bottom ruler:
.rule2:
  mov eax, ebp
  add eax, STRTROW
  mov ebx, 0x01
  mov ecx, COLS-1
  call Ruler

; Throw up an informative message centered on the last line
  mov esi, Message
  mov ecx, MSGLEN
  mov ebx, COLS
  sub ebx, ecx
  shr ebx, 0x01
  mov eax, 0x18
  call WrtLn

; Having written all that to the buffer, send the buffer to the console:
  call Show

Exit:
  mov eax, 0x01
  mov ebx, 0x00
  int 0x80
