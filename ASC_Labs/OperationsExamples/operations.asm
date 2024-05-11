bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
  ;pb1   
    a db 10
    b dw 2
    c db 3
    d db 3
    x db 0

  ;pb2     
  ;pb3     
; our code starts here
segment code use32 class=code
    start:
     ;pb1   :   (a+b)*c/d   a,b,c,c -byte   unsigned
        mov al,[a]
        add al,[b]
        mov ah,[c]
        mul AH
        div byte [d]
        mov [x],al
        
        
     ;pb2 :    (a-b*c)/d unsigned
        mov al,[b] ;al=2
        mul [c] ; ax=2*3 =6
        mov bx,ax ;bx=6
        mov al,[a] ;al=10
        mov ah,0 ;ax=10
        sub ax,bx ;ax=10-6= 4
        div byte [d] ;ah=ax%d=1 al=ax/d=1
        
        
     ;pb3 :    (a*b)/d-c signed b-word
        mov al,[a] ;al=a
        cbw  ; ax=a ;we transform a in a word from a byte
        mul [b] ;dx:ax=ax*b  this is the first part of the ecuation
        mov bx,ax ; bx=ax    we move this value so we can transform d in a word (below)
        mov al, [d] ;al=d
        cbw ;ax=d
        mov cx,ax ;we save the value of d in a word space
        mov ax,bx ;ax will have the value it had after the multiplication
        idiv cx ;dx:ax/cx=ax and dx:ax%cx=dx
        mov dx,ax ;dx =(a*b)/d because we are interested just in integer part so the value in dx is not important for now
        mov al, [c]
        cbw ;we transform c from a byte to a word
        sub dx,ax 
        mov [x],dx;we put the final result in x
        
        
     ;pb4  :    a*b*c-d all bytes, signed
        mov al,[a] ; al will have the value of a*b
        imul [b] ;ax=a*b
        mov bx,ax ;bx=a*b
        mov al,[c]
        cbw  ;transform c from byte in word so we can make the multiplication
        imul bx; so dx:ax=ax*bx= a*b*c
        push dx
        push ax
        pop edx ; so now, using the stack, we have a whole dw not 2 halves of words
        mov al,[d]
        cbw    ; ax=d
        cwde   ; eax=d
        sub edx,eax ;edx=a*b*c-d
        
      ;after that we can:
        push edx
        pop ax
        pop dx ; so now the result is in dx:ax
        
      ;if another step is added like (a*b*c-d)/e (e-word):
        idiv word[e]  ;ax=dx:ax /e
        
     
     
     ;pb5 :    a*b-c*d     a,b,c,d -words    unsigned
        mov ax,[a]
        mul word[b] ;dx:ax=a*b   we save in cx:bx so we can do the other multiplication
        mov cx,dx
        mov bx, ax  ; cx:bx=a*b
        mov ax,[c]
        mul word[d] ;dx:ax=c*d
        sub bx,ax ;set cf with 0 or 1 
        sbb cx,dx ;we subtrack with carie flag if it exist
        ;we can do this method or we can use the stack for resolving this, but if we are sub or add in dword we can't use the stack so we need to use this method
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
