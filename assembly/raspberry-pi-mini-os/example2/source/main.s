.section .init
.global _start
_start:
  ldr r0, =0x20200000                            
  mov r3, #0x1

/* Enable output on the 16th pin */
  mov r1, #1
  lsl r1, #18
  str r1, [r0, #4]

loop$:
  mov r2, #0x3F0000 /* Initialize the time */

wait1$:
  sub r2, #1
  cmp r2, #0
  bne wait1$

  cmp r3, #1
  beq on$
  b off$

on$: 
  /* Turn the pin off to turn LED light on */
  mov r1,#1
  lsl r1,#16
  str r1, [r0, #40]
  mov r3, #0
  b loop$

off$:
  /* Turn the pin on to turn the LED light off */
  mov r1,#1
  lsl r1,#16
  str r1, [r0, #28]
  mov r3, #1
  b loop$
