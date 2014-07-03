section .data
  EditBuff: db 'abcdefghijklm',0x0A
  BUFFLEN   equ $-EditBuff
  ENDPOS    equ 12
  INSRTPOS  equ 5

section .text
  global _start

; Specify size of buff in edx
PrintBuff:
  mov eax, 0x04                   ; Specify sys_write call
  mov ebx, 0x01                   ; Specify File Descripor 1: Standard Output
  mov ecx, EditBuff               ; Pass offset of the error message
  int 0x80                        ; Call the linux service dispatcher
  ret

_start:
  nop
  mov edx, BUFFLEN
  call PrintBuff

  std                             ; Down-memory transfer (from high to low)
  mov ebx, EditBuff+INSRTPOS      ; Save address of insert point
  mov esi, EditBuff+ENDPOS        ; Start at end of text
  mov edi, EditBuff+ENDPOS+1      ; Bump text right by 1
  mov ecx, ENDPOS-INSRTPOS+1      ; # of chars to bump
  rep movsb                       ; Move 'em!
  mov byte [ebx], ' '             ; Write a space at insert point

  mov edx, BUFFLEN+1
  call PrintBuff

Exit:
  mov eax, 0x01                   ; Specify sys_exit
  mov ebx, 0x00                   ; Return value of 0
  int 0x80                        ; Exit program
  nop
