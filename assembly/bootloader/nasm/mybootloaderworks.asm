;----------------------------------------------------------------------
; A Simple boot program that prints the string 'Hello World'
; Author: Matthew Hoggan 2012
;----------------------------------------------------------------------
org 0x7c00	 	         	; This is where BIOS loads the bootloader

entry:                          	; Label to Signify entry to program
    xor ax, ax                          ; Clear out the ax register
    mov ds, ax                          ; Set data segment to 0x00
    mov si, msg                         ; Get pointer to string

;----------------------------------------------------------------------
; We need al = [DS:SI]
;----------------------------------------------------------------------
loop:                                   ; Top of loop to iterate over string
    mov al, [si]                        ; Move contents of pointer to al
    inc si                              ; Increment Source Index
    or al, al                           ; Check if character pointed to is Zero
    jz hang                             ; Zero signifies end of string
    call print_char                     ; Print current char in al
    jmp loop                            ; Repeat

msg db 'Hello World!!!',0x00            ; Output string for bios

; --------------------------------------------
; Function to print char
; assume caller has placed char in al
; --------------------------------------------
print_char:
    mov	ah, 0x0e			; Function to print a character to the screen
    mov	bl, 7				; color/style to use for the character
    int	0x10				; print the character
    ret                                 ; return to caller

hang:
	jmp	hang			; just loop forever.

;---------------------------------------------
; Write Zeros up to end of program - 2 then boot signature
;---------------------------------------------
size	equ	$ - entry
	times	(512 - size - 2) db 0
	db	0x55, 0xAA		;2  byte boot signature
