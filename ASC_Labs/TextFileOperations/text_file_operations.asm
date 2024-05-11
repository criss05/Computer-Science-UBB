bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern fopen, printf, scanf, fclose, fprintf,exit  ; tell nasm that exit exists even if we won't be defining it
import fopen msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    output_file db "file.txt", 0
    output_mode db "a", 0
    read_msg db "Give the numbers: ",13,10, 0
    read_var db "%d",0
    number db 0
    file_descriptor dd -1
    sapte db 7
    print_var db "%d",0
    

    ;A file name is given (defined in the data segment). 
    ;Create a file with the given name, then read numbers from the keyboard and write only the numbers divisible by 7 to file, 
    ;until the value '0' is read from the keyboard. 
    
    
; our code starts here
segment code use32 class=code
    start:
        push dword read_msg
        call [printf]
        add esp, 4
    
        push dword output_mode
        push dword output_file
        call [fopen]
        add esp,4*2    
        mov dword[file_descriptor], eax
        
        cmp eax,0
        je end_loop
        read_loop:
            mov dword[file_descriptor], eax
            push dword number
            push dword read_var
            call [scanf]
            add esp, 4*2
            
            mov ax,[number]
            cmp ax,0
            je end_loop
            div byte[sapte]
            cmp ah, 0
            jne end2
            mov edx, [number]
            
            push edx
            push dword print_var
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4*3
            
            mov eax, [file_descriptor]
            end2:
            
            jmp read_loop
        end_loop:
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
