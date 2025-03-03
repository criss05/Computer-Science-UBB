bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;h/a + (2 + b) + f/d – g/c 
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 3
    b db 5
    c db 2
    d db 7
    f dw 287
    g dw 300
    h dw 270
    
    
; our code starts here
segment code use32 class=code
    start:
        mov ax,[h] ;ax=270
        div byte [a] ;al=270/3=90
        mov bl,al ;bl=90 (h/a)
        mov ax,[f] ;ax=287
        div byte [d] ;al=287/7=41
        mov cl,al ;cl=41 (f/d)
        mov ax,[g] ;ax=300
        div byte [c] ;al=ax/2=150
        mov dl,al ;dl=150 (g/c)
        mov al,2 ;al=2
        add al,[b] ; al=2+5=7 (2+b)
        add al,bl ;=90+7=97
        add al,cl ;=97+41=138
        sub al,dl ;=138-150=-12
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
