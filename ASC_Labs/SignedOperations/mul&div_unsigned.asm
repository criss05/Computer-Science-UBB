bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 10h
    b dw 1234h
    c db 93h
    x dq 9234Fh
    
  ;x-(a*a+b)/(a+c/a) = 9228Bh       unsigned
; our code starts here
segment code use32 class=code
    start:
        mov al, byte[a]
        mul byte[a]         ;ax=a*a
        add ax,word[b]      ;ax=a*a+b
        mov cx,ax
        ;a*a+b = 1334       done in cx
        
        mov ax,0
        mov al, byte[c]     ;ax=c
        div byte[a]         ;al=c/a
        add al,byte[a]      ;al=a+c/a
        mov bl,al
        ;a+c/a = 19            done in bl
        
        mov ax,cx         ;ax=a*a+b
        div bl            ;al=(a*a+b)/(a+c/a)
        mov bl,al
        mov eax,0
        mov al,bl
        mov edx,0          ;edx:eax=(a*a+b)/(a+c/a)
        mov ebx, dword[x]
        mov ecx, dword[x+4] ;ecx:ebx=x
        sub ebx,eax
        sub ecx,edx
        ;the result is in ecx:ebx
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
