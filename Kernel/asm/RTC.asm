GLOBAL get_hour
GLOBAL get_minutes
GLOBAL get_seconds

section .text

get_data:

	mov al, 0Bh
	out 70h, al
	in al, 71h
	or al, byte 00000100b
	out 71h, al

	out 70h, al
	in  al, 71h

	movzx rax, al
	ret

get_hour:
	mov al, 4
	call get_data
	ret

get_minutes:
	mov al, 2
	call get_data
	ret

get_seconds:
	mov al, 0
	call get_data
	ret