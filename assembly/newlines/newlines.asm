;-----------------------------------------------------------------------------
; Newlines    : Sends between 1-15 newlines to the Linux console
; UPDATED     : 4/19/2009
; IN          : EDX: # of newlines to send, from 1 to 15
; RETURNS     : Nothing
; MODIFIES    : Nothing. All caller registers preserved.
; CALLS       : Kernel sys_write
; DESCRIPTION : The number of newline characters (0x0A) specified in EDX
;               is sent to stdout using INT 80h sys_write. This
;               procedure demonstrates placing constant data in the
;               procedure definition itself, rather than in the .data or
;               .bss sections.
;

Newlines:
  pushad                                                                       ; Save all caller's registers
  cmp edx, 0x0F                                                                ; Make sure caller didn't ask for more than 15
  ja .exit                                                                     ; If so, exit without doing anything
  mov ecx, EOLs                                                                ; Put address of EOLs table into ECX
  mov eax, 0x04                                                                ; Specify sys_write
  mov ebx, 0x01                                                                ; Specify stdout
  int 0x80                                                                     ; Make the kernel call
  .exit popad                                                                  ; Restore all caller's registers
  ret                                                                          ; Go home!

EOLs db 0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A
EOLc db 0x0A

global _start

_start:
; Need to write routine that processes command line arguments
  mov edx, 0x0F
  call Newlines
  mov eax, 0x01                                                                ; Specify sys_exit call
  mov ebx, 0x00                                                                ; Specify return value of 0
  int 0x80                                                                     ; Make the kernel call
 
