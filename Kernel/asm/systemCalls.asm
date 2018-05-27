GLOBAL systemCallHandler
extern systemCallDispatcher

section .text

systemCallHandler:
    push rbp
    mov rbp, rsp

    call systemCallHandler

    mov rsp, rbp
    pop rbp

    iretq