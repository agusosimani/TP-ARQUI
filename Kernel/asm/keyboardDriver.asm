section .text
; Port 0x64 (Command Port)
; Port 0x60 (Data Port)
GLOBAL scan_key
GLOBAL keyboard_wait

scan_key:

push rbp
mov rbp, rsp

and al,0h
in al,0x60

mov rsp, rbp
pop rbp
ret


keyboard_wait:

push rbp
mov rbp, rsp
in al, 0x64
and al, 0x01
mov rsp, rbp
pop rbp
ret

