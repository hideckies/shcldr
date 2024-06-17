; Reference: https://github.com/thefLink/C-To-Shellcode-Examples/blob/master/HelloWorld/adjuststack.asm

extern _Entry
global _AlignStack

section .text

    _AlignStack:
        push esi
        mov  esi, esp
        and  esp, 0FFFFFFF0h
        sub  esp, 020h
        call _Entry
        mov  esp, esi
        pop  esi
        ret
