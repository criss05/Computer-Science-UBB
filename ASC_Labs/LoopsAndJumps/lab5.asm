bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

          ;Two byte strings S1 and S2 are given, having the same length. 
          ;Obtain the string D so that each element of D represents the maximum of the corresponding elements from S1 and S2. 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 db 1,3,6,2,3,7
    len equ $-s1
    s2 db 6,3,8,1,2,5
    d times len db 0

; our code starts here
segment code use32 class=code
    start:
        mov edi,0 ;index for s1 and s2
        mov ecx,len ;length of s1 and s2
        jecxz final
            repeta:
                mov al,[s1+edi]
                mov bl,[s2+edi]
                cmp al,bl
                jg mai_mare
                    mov byte[d+edi],bl
                    jmp final_jump
                mai_mare:    
                    mov byte[d+edi], al
                final_jump
                inc edi
            loop repeta
            final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
