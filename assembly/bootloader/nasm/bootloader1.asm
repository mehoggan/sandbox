;----------------------------------------------------------------------
; A Simple boot program that prints the string 'Hello World'
;----------------------------------------------------------------------
org 0x7c00	 	         	; This is where BIOS loads the bootloader

entry:                          	; Label to Signify entry to program
    jmp short begin 	        	; Jump over the DOS boot record data

; --------------------------------------------
;  Boot program code begins here
; --------------------------------------------
begin:                          	; Label to Signify entry to program
    xor ax, ax                          ; Zero out ax
    mov ds, ax                          ; Set data segment to base of RAM
    mov si, msg                         ; Get pointer to string
    call putstr                         ; Print the message
    jmp hang                            ; Go to infinite loop

msg db 'Hello, World',0x00

putstr:                                 ; Function to print the string
    lodsb                               ; al = [DS:SI]
    or al, al                           ; Set zero flag if al = 0
    jz ret                              ; Jump to end of function if al = 0
    mov ah, 0x0e                        ; Video function 0Eh (print char)
    mov bx, 0x0007                      ; Color
    int 0x10
    jmp putstr
ret:
    retn

hang:
	jmp	hang			; just loop forever.

;---------------------------------------------
; Write Zeros up to end of program - 2 then boot signature
;---------------------------------------------
size	equ	$ - entry
	times	(512 - size - 2) db 0
	db	0x55, 0xAA		;2  byte boot signature
