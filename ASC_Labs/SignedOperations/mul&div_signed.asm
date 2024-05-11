bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 05h
    b dw 123h
    c db 33h
    x dq 234h
    
  ;x-(a*a+b)/(a+c/a) = 9343h       signed

; our code starts here
segment code use32 class=code
    start:
        mov al, byte[a]   ;al=a =5
        imul byte[a]      ;ax=a*a =19
        add ax,word[b]    ;ax=a*a+b =13C
        mov cx,ax         ;cx=13C     ax in free to use again
        ;a*a+b = AA23       done in cx
        
        mov al,byte[c]    ;al =33
        cbw               ;ax =33
        idiv byte[a]      ;al=c/a =F
        add al,byte[a]    ;al=a+c/a =F
        mov bl,al         ;bl=F
        ;a+c/a = 51            done in bl
        
        mov ax,cx         ;ax=a*a+b
        idiv bl           ;al=(a*a+b)/(a+c/a)         al=ax/bl   =a*a+b(word) / a+c/a(byte)   =13C/F   
        cbw               ;ax=(a*a+b)/(a+c/a)
        cwde              ;eax=(a*a+b)/(a+c/a)
        cdq               ;edx:eax=(a*a+b)/(a+c/a)
        mov ebx, dword[x] ;The first part
        mov ecx, dword[x+4] ;ecx:ebx=x
        sub ebx,eax
        sbb ecx,edx
        ;the result is in ecx:ebx
        

        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
