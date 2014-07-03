# Author: Susam Pal <http://susam.in/>

.code16
.section .text
.globl _start
_start:
  mov $0xb800, %ax
  mov %ax, %ds
  movb $'B', %ds:0x00
  movb $0x1e, %ds:0x01
idle:
  jmp idle 
