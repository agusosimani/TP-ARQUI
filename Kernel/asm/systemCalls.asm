GLOBAL systemCallHandler
extern systemCallDispatcher

section .text

systemCallHandler:
    push rbp
    mov rbp, rsp

    call systemCallDispatcher

    mov rsp, rbp
    pop rbp

    iretq