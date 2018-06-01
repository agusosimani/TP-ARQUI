GLOBAL beepOn
GLOBAL beepOff

section .text

beepOn:
        mov al, 182 ;frequency
        out 43h, al
        mov ax, 1193
        out 42h, al
        mov al, ah
        out 42h, al
        in al, 61h ;turn on speaker
        mov al, 03h
        out 61h, al
        ret
beepOff:
        in al, 61h
      	mov al, 00h
      	out 61h,al
        ret
        
loop:
        nop
        jmp loop
        ret
