bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

    ;A string of doublewords is given. 
    ;Order in decreasing order the string of the low words (least significant) from these doublewords. 
    ;The high words (most significant) remain unchanged. 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir DD 12345678h, 1256ABCDh, 12AB4344h
    len equ ($-sir)/4
    sir_nou times len DD 0

; our code starts here
segment code use32 class=code
    start:
        mov esi,sir
        mov ecx, len-1
        jecxz end_1
        cld
            first_for:
                lodsw  ;ax = 5678h  esi+2
                push ecx
                mov edi,esi
                add esi,2
                jecxz end_2
                    second_for:
                        mov bx,[edi+2] ;bx = ABCDh
                        cmp ax,bx
                        jae no_swap
                            add edi,2
                            stosw   ;[edi] = 5678h   edi+2    al doilea numar va fi 1256 5678h
                            mov ax,bx   ;ax = ABCDh
                            mov [esi-4], bx ;primul numar va fi 1234 ABCDh
                            jmp no_inc
                        no_swap:
                            add edi,4  ;daca nu se face interschimbare se trece la umratorul element 
                            no_inc:
                    loop second_for
                end_2:
                pop ecx
            loop first_for
        end_1:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
