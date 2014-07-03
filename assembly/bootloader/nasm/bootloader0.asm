;----------------------------------------------------------------------
; A Simple boot program that prints the letter 'Hello World'
; Author: Matthew Hoggan 2012
;----------------------------------------------------------------------
	org 0x7c00	        ; This is where BIOS loads the bootloader

entry:                          ; Label to Signify entry to program
	jmp short begin         ; Jump over the DOS boot record data

; --------------------------------------------
;  Boot program code begins here
; --------------------------------------------
begin:                          ; Label to Signify entry to program

        ;-------------------------------------
        ; Print H
        ;-------------------------------------
	mov	ah, 0x0e	; Function to print a character to the screen
	mov	al, 'H'		; Which character to print
	mov	bl, 7		; color/style to use for the character
	int	0x10		; print the character

        ;-------------------------------------
        ; Print e
        ;-------------------------------------
	mov	ah, 0x0e	; Function to print a character to the screen
	mov	al, 'e'		; Which character to print
	mov	bl, 7		; color/style to use for the character
	int	0x10		; print the character

        ;-------------------------------------
        ; Print l
        ;-------------------------------------
	mov	ah, 0x0e	; Function to print a character to the screen
	mov	al, 'l'		; Which character to print
	mov	bl, 7		; color/style to use for the character
	int	0x10		; print the character

        ;-------------------------------------
        ; Print l
        ;-------------------------------------
	mov	ah, 0x0e	; Function to print a character to the screen
	mov	al, 'l'		; Which character to print
	mov	bl, 7		; color/style to use for the character
	int	0x10		; print the character

        ;-------------------------------------
        ; Print o
        ;-------------------------------------
	mov	ah, 0x0e	; Function to print a character to the screen
	mov	al, 'o'		; Which character to print
	mov	bl, 7		; color/style to use for the character
	int	0x10		; print the character

hang:
	jmp	hang		; just loop forever.

;---------------------------------------------

size	equ	$ - entry
	times	(512 - size - 2) db 0
	db	0x55, 0xAA		;2  byte boot signature
