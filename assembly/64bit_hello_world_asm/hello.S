.data
msg:
    .ascii "Hello, world!\n"
    len =  . - msg
.text
    .global _start
_start:
    movq $len, %rdx
    movq $msg, %rcx
    movq $1,   %rbx
    movq $4,   %rax
    int  $0x80
    movq $0,   %rbx
    movq $1,   %rax
    int  $0x80
