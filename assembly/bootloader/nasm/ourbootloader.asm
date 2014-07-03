;----------------------------------------------------------------------
; Simple boot program that prints the letter 'H'
;  and then hangs
; Joel Gompert 2001
;
; Disclaimer: I am not responsible for any results of the use of the contents
;   of this file
;----------------------------------------------------------------------
	org 0x7c00	; This is where BIOS loads the bootloader


; Execution begins here
entry:
	jmp short begin ; jump over the DOS boot record data


; --------------------------------------------
;  Boot program code begins here
; --------------------------------------------
; boot code begins at 0x003E
begin:
	mov	ah, 0x0e	; Function to print a character to the screen
	mov	al, 'H'		; Which character to print
	mov	bl, 7		; color/style to use for the character
	int	0x10		; print the character

hang:
	jmp	hang		; just loop forever.

;---------------------------------------------

size	equ	$ - entry
%if size+2 > 512
  %error "code is too large for boot sector"
%endif
	times	(512 - size - 2) db 0

	db	0x55, 0xAA		;2  byte boot signature
