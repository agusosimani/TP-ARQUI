GLOBAL opcode
GLOBAL zero

section .text

opcode:
    ud2
    ret

zero:
    mov rcx, 0
    div rcx
    ret