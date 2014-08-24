.section .init
.global _start

/*
 * Calculate a physical address from a peripheral address
 * r1[input]  <-- Peripheral address
 * r0[output] --> Physical address
 */
per_to_phy$:
  push{lr}
  sub r0,r1,0xF2000000                 // diff = per - base_per
  add r0,r0,0x20000000                 // ret = diff + base_phy
  pop{pc}

/*
 * Enable the output on the nth GPIO pin
 * r1[input]  <-- GPIO pin
 */
enable_gpio_pin$:
  push{r0,r1,r2,lr}
  
  pop{r2,r1,r0,pc}

/*
 * Keep the system running
 */
loop$:
  b loop$

_start:
  mov r1,=0x7E200000                   // This is the peripheral addr
  bl per_to_phy                        // Branch with link
  bl enable_output_on_gpio_pin
  b loop



