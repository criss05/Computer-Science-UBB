bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf, fprintf, fopen, fclose, compare             
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

;Read a string of unsigned numbers in base 10 from keyboard. 
;Determine the minimum value of the string and write it in the file min.txt (it will be created) in 16  base.

segment data use32 class=data
    number dd 0
    message db "Give the numbers: ",13, 10, 0
    format db "%d", 0
    file_mode db "w", 0
    file_name db "min.txt", 0
    file_descriptor dd -1
    print_format db "%x", 0

; our code starts here
segment code use32 class=code
    start:
        push dword message
        call [printf]
        add esp, 4
        
        mov ebx, -1
        
        reading:
            push dword number
            push dword format
            call [scanf]
            add esp,4*2
        
            cmp dword[number], -1
            je end_loop
        
            push dword [number]
            call compare
            add esp,4
        
        jmp reading
        
        end_loop:
 
        push file_mode
        push file_name
        call [fopen]
        add esp, 4*2
        mov [file_descriptor], eax
        
        cmp eax, 0
        je no_file
        
        push dword ebx
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        no_file:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
