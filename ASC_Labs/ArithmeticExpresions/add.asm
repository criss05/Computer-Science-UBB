bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern printf
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 10
    b db 5
    c db 9
    d db 2

;(a+a-c)-(b+b+b+d) 
    
; our code starts here
segment code use32 class=code
    start:
        mov al,[a]
        add al,[a]
        sub al,[c]
        mov bl,[b]
        add bl,[b]
        add bl,[b]
        add bl,[d]
        sub al,bl
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
