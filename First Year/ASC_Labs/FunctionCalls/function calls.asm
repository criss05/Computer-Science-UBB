  bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program

extern printf, scanf, exit               ; tell nasm that exit exists even if we won't be defining it
import printf msvcrt.dll
import scanf msvcrt.dll
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    read_prop db "Give the number in base 10: ",13, 10, 0
    read_var db "%d", 0
    print_prop db "The number %d in  base 16 is %x", 13, 10, 0
    number db 0

    ;Read a number in base 10 from the keyboard and display the value of that number in base 16 
    
    
; our code starts here
segment code use32 class=code
    start:
        push read_prop
        call [printf]
        add esp, 4
        push number
        push read_var
        call [scanf]
        add esp, 8
        
        push dword[number]
        push dword[number]
        push print_prop
        call [printf]
        add esp, 4*3
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
