	.file	"assembly.cpp"
	.intel_syntax noprefix
	.section	.rodata
.LC0:
	.string	"%s\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	and	esp, -16
	sub	esp, 32
	mov	DWORD PTR [esp+28], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR [esp+28]
	sal	eax, 2
	add	eax, DWORD PTR [ebp+12]
	mov	edx, DWORD PTR [eax]
	mov	eax, DWORD PTR stdout
	mov	DWORD PTR [esp+8], edx
	mov	DWORD PTR [esp+4], OFFSET FLAT:.LC0
	mov	DWORD PTR [esp], eax
	call	fprintf
	add	DWORD PTR [esp+28], 1
.L2:
	mov	eax, DWORD PTR [esp+28]
	cmp	eax, DWORD PTR [ebp+8]
	setl	al
	test	al, al
	jne	.L3
	mov	eax, 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.5 20110214 (Red Hat 4.4.5-6)"
	.section	.note.GNU-stack,"",@progbits
