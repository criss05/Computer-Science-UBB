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
    c dd 937A3h
    d dq 1234Fh

    
;(c+c-a)-(d+d)-b = 101664h        unsigned   
    
; our code starts here
segment code use32 class=code
    start:
        mov ebx,dword[c]    ;ebx = c
        add ebx,dword[c]    ;ebx = c+c
        mov eax,0           ;convert a from byte in dword
        mov al,[a]          ;eax = a
        sub ebx,eax         
        ;c+c-a done    in ebx
        clc
        mov eax,dword [d]     ;eax will have the value of the firts part in d
        mov edx,dword [d+4]   ;edx will have the value of the second part in d
        add eax,dword [d]     ;eax will have the value of the firts part in the sum
        adc edx, dword[d+4]   ;edx:eax will have now the whole sum with carie if it exist
        ;d+d done        in edx:eax
        clc
        mov ecx,0               ;ecx:ebx=c+c-a 
        sub ebx,eax             ;the firts part of sub
        sbb ecx,edx             ;the second part with the borow if this exist
        mov edx,ecx             ;move from ecx:ebx in edx:eax
        mov eax,ebx             
        ;(c+c-a)-(d+d) done        in eax:edx
     
        mov ebx,0               ;I clear ebx so I can convert b into dword
        mov ecx,0               ;I clear ecx so I can convert b into quad
        mov bx,word[b]          ;ecx:ebx = b the value of b
        sub eax,ebx             ;the fisrt part of the ecuation
        sbb edx,ecx             ;the whole ecuation 
        ;the ecuation done    in edx:eax
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
