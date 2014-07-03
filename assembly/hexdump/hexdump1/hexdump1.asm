; Executable name : hexdump1
; Version         : 1.0
; Created date    : December 9, 2011
; Author          : Jeff Duntemann
; Description     : A simple program in assembly for Linux, using NASM 2.05,
;   demonstrating the conversion of binary values to hexadecimal strings.
;   It acts as a very simple hex dump utility for files, though without the
;   ASCII equivalent column
;
; Run it this way:
;     hexdump1 < [input file]
;
; Build using these commands:
;     nasm -f elf -g -F stabs hexdump1.asm
;     ld -o hexdump1 hexdump1.o
;

SECTION .bss                                     ; Section containing uninitialized data
    BUFFLEN   equ 16                             ; We read the file 16 bytes at a time
    Buff:     resb BUFFLEN                       ; Text buffer itself

SECTION .data                                    ; Section containing initialized data
    ;HexStr:   db " 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00",0x0A
    HexStr:   db " 10 20 30 40 50 60 70 80 90 A0 B0 C0 D0 E0 F0 G0",0x0A
    HEXLEN    equ $-HexStr

    Digits:   db "0123456789ABCDEF"               ; Simple lookup table

    STDIN     equ 0x00
    SYS_EXIT  equ 0x00
    STDOUT    equ 0x01
    SYS_READ  equ 0x03
    SYS_WRITE equ 0x04
    TRAP      equ 0x80

SECTION .text                                    ; Section containing code
    global _start

    _start:                                      ; Entry into the program
        nop                                      ; Make gdb happy
    
    ; Read a buffer full of text from stdin
    Read:
        mov eax, SYS_READ                        ; Set system call to be sys_read
        mov ebx, STDIN                           ; Specify File Descriptor 0: Standard Input
        mov ecx, Buff                            ; Pass offset of the buffer to read to
        mov edx, BUFFLEN                         ; Pass number of bytes to read at one pass
        int TRAP                                 ; Call software interupt with 80h
        mov ebp, eax                             ; Save # of bytes read from file for later
        cmp eax, 0                               ; If # of btye == 0 -> sys_read reached EOF
        je Done                                  ; Jmp if ZF == 1 to exit the program
    
    ;Reset HexStr to All 0's
    mov ecx, HexStr;                             ; Keep a pointer to the begining of the string
    lea edx, [HexStr+HEXLEN]                     ; Keep a pointer to the end of the string
    Reset:                                       
        cmp ecx, edx                             ; See if the begining pointer is equal or past end pointer
        jge Write
        mov byte[ecx+0x01], 0x30                 ; Load '0' into slot [ecx+1] '[ecx+0][ecx+1][ecx+2]'
        mov byte[ecx+0x02], 0x30                 ; Load '0' into slot [ecx+2]
        inc ecx
        inc ecx
        inc ecx
        jmp Reset                                ; Return back to top of loop

    ; Set up the retisters for the process buffer step:
        mov esi, Buff                            ; Place addresss of file buffer into esi
        mov edi, HexStr                          ; Place address of line string into edi
        xor ecx, ecx                             ; Clear ecx to 0
    
    ; Go through the buffer and convert binary values to hex digits:
    Scan:
        xor eax, eax                             ; Clear eax to 0
        mov edx, ecx                             ; Move the value in ecx to edx
        shl edx, 0x01                            ; Multiply the value of edx by 2
        add edx, ecx                             ; ecx * 2 + ecx = ecx x 3

    ; Get a character from the buffer and put it in both eax and ebx:
        mov al, byte[esi+ecx]                    ; Put a byte from the input buffer into al
        mov ebx, eax                             ; Duplicate the byte in bl for second nybble

    ; Look up low nybble character and insert it into the string:
        and al, 0x0F                             ; Mask out all but the low nybble
        mov al, byte[Digits+eax]                 ; Look up in table the char equivalent of nybble
        mov byte[HexStr+edx+2], al               ; Write LSB char digit to line string
        
    ; Look up high nybble character and insert it into the string:
        shr bl, 0x04                             ; Shift high 4 bits of char into low 4 bits
        mov bl, byte[Digits+ebx]                 ; Look up in table the char equivalent to nybble
        mov byte[HexStr+edx+1], bl               ; Write MSB char digit to line string

    ; Bump the buffer pointer to the ext character and see if we're done:
        inc ecx                                  ; Increment line string pointer
        cmp ecx, ebp                             ; Compare to the number of chars in the buffer
        jna Scan                                 ; Loop back if ecx is <= number of chars in buffer
 
    Write:
    ; Write the line of hexadecimal values to stdout:
        mov eax, SYS_WRITE                       ; Specify sys_write call
        mov ebx, STDOUT                          ; Specify File Descriptor 1: Standard output
        mov ecx, HexStr                          ; Pass offset of line string
        mov edx, HEXLEN                          ; Pass size of te line string
        int TRAP                                 ; Make kernel call to display line string
        ;jmp Read                                 ; Loop back and load file buffer again

    Done:
        mov eax, SYS_EXIT                        ; Specify sys_exit call
        mov ebx, 0x00                            ; Specify return value of 0
        int TRAP                                 ; Software interupt needed to have kernel call sys_exit
        ret
        nop
