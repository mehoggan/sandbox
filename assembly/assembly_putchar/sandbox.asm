section .bss

section .data
    hello: db "Hello World",0xa      ;10 is EOL
    newline: db 0xa                  ;
    SYS_EXIT  equ 0x1                ;
    SYS_WRITE equ 0x4                ;
    STDOUT    equ 0x1                ;
    TRAP      equ 0x80               ;

section .text
    global _start

_start:

    nop                              ; For gdb
    mov ecx, hello;                  ; char *ecx = hello

read:
    cmp byte[ecx], 0xa               ; while(ecx++)
    je  exit                         ; 

    ; setup registers to do the printing
    mov eax, SYS_WRITE               ; set sys_write syscall
    mov ebx, STDOUT                  ; move one byte at a time
    mov edx, 1                       ; number of bytes to read
    int TRAP                         ; execute the syscall

    inc ecx                          ; i++
    jmp read                         ;

exit:    
    mov eax, SYS_WRITE               ; print newline before exit
    mov ebx, STDOUT
    mov ecx, newline
    mov edx, 1
    int TRAP

    mov eax, SYS_EXIT                ; 0x01 = syscall for exit
    int TRAP                         ;
