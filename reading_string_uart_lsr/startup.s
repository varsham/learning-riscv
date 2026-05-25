.section .text
.global _start

_start:
    la sp, stack_top
    call main
    j .

.section .bss
.space 1024

stack_top:
