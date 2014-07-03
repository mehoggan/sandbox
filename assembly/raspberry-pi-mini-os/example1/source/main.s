.section .init
.global _start
_start:
  ldr r0, =0x20200000                            

  /* Enable output on the 16th pin */
  mov r1, #1
  lsl r1, #18
  str r1, [r0, #4]
  
  /* Turn the pin off to turn LED light on */
  mov r1,#1
  lsl r1,#16
  str r1, [r0, #40]

loop$: 
  /* Keep the system running */
  b loop$
