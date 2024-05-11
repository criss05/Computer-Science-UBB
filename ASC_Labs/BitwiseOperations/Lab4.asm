bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;Given the word A and the byte B, compute the doubleword C:

    ;the bits 0-3 of C have the value 1
    ;the bits 4-7 of C are the same as the bits 0-3 of A
    ;the bits 8-13 of C have the value 0
    ;the bits 14-23 of C are the same as the bits 4-13 of A
    ;the bits 24-29 of C are the same as the bits 2-7 of B
    ;the bits 30-31 have the value 1


segment data use32 class=data
    a dw 0100110001100011b
    b db 10111011b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        mov ax,[a]
        shl ax,4 ;ax=1100 0110 0011 0000b
        and ax, 0000000011110000b ; ax=0000 0000 0011 0000b
        or ax, 01111b ;ax=0000 0000 0011 1111b
        and ax, 1100000011111111b ;ax=0000 0000 0011 1111b
        mov bx,ax
        mov eax,0
        mov ax,bx             ;eax=0000 0000 0000 0000 00done00 0000 0011 1111b
        mov ebx,0
        mov bx,[a] ;[a]-dword    ebx=0000 0000 0000 0000 0100 1100 0110 0011b
        shl ebx, 10             ;ebx=0000 0001 0011 0001 1000 1100 0000 0000b
        and ebx, 00000000001111111100000000000000b ;ebx=0000 0000 0000 1100 0110 0000 0000 0000b
        or eax,ebx ;eax=0000 0000  done  0000 1100 0110 0000 0011 1111b
        mov ebx, 0      ;ebx = 0000 0000 0000 0000 0000 0000 1011 1011b
        mov bl, [b]     ;ebx = 0000 1011 1000 0000 0000 0000 1011 1011b
        shl ebx, 22     ;ebx = 0010 1110 0000 0000 0000 0000 0000 0000b
        or eax,ebx    ;eax = 00 done  10 1110 0011 0001 1000 0000 0011 1111b
        or eax, 11000000000000000000000000000000b
        mov [c],eax    ;[c] = 1110 1110 0011 0001 1000 0000 0011 1111b
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
