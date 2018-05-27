GLOBAL get_x_resolution
GLOBAL get_y_resolution

section .text
get_x_resolution:
    mov ax, [5084h]
    ret

get_y_resolution:
    mov ax, [5086h]
    ret
