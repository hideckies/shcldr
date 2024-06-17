; Reference: https://github.com/thefLink/C-To-Shellcode-Examples/blob/master/HelloWorld/adjuststack.asm

extern Entry
global AlignStack

section .text

    AlignStack:
        push esi
        mov  esi, esp
        and  esp, 0FFFFFFF0h
        sub  esp, 020h
        call Entry
        mov  esp, esi
        pop  esi
        ret
