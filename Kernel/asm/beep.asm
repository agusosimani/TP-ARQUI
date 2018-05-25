GLOBAL beep

section .text

beep:
        mov al, 182 ;frequency
        out 43h, al
        mov ax, 1193
        out 42h, al
        mov al, ah
        out 42h, al
        in al, 61h ;turn on speaker
        mov al, 03h
        out 61h, al
   loop:
        nop
        jmp loop

        ret