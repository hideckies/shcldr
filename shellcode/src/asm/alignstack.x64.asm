; Reference: https://github.com/thefLink/C-To-Shellcode-Examples/blob/master/HelloWorld/adjuststack.asm

extern Entry
global AlignStack

section .text

    AlignStack:
        push rsi
        mov  rsi, rsp
        and  rsp, 0FFFFFFFFFFFFFFF0h
        sub  rsp, 020h
        call Entry
        mov  rsp, rsi
        pop  rsi
        ret
