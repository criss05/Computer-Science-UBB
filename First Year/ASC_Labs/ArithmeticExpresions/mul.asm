bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;300-[5*(d-2*a)-1] 
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 20
    d dw 270

; our code starts here
segment code use32 class=code
    start:
        mov al,2; al=2
        mul byte [a]; ax=al*20=2*20
        neg ax; ax=-40
        add ax,[d];ax=270-40=230
        mov bx,5;bx=5
        mul bx;eax=5*230=1150
        dec eax;eax=1150-1
        neg eax;eax=-1149
        mov ecx,300;ecx=300
        add eax,ecx;eax=300-1149
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
