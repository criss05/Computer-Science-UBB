bits 32 
global start        


extern exit, scanf, printf, fopen, fclose,fread, fprintf               
import exit msvcrt.dll  
import scanf msvcrt.dll 
import printf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll   

;Să se scrie un program în limbaj de asamblare care:

    ;citește de la tastatură un număr natural N (0 <= N < 10) și numele unui fișier text;
    ;citește toate numerele întregi din fișierul dat;
    ;afișează pe ecran doar numerele întregi POZITIVE și care au cifra zecilor egală cu N.

;Fișierul text trebuie să existe și va conține doar numere întregi separate prin spații.

;Exemplu:

;Dacă fișierul text conține:

;1121 -27 150 -1122 26 -121 1123 25 -122 1134 -24 123 -1195 73 124 -1126 32 135

;pentru N = 2, se va afișa pe ecran:

;1121 26 1123 25 120 124
segment data use32 class=data
    file_name resb 10
    number dd 0
    number_msg db "Please enter the number: ", 0
    file_msg db "Please enter the file name: ", 0
    number_format db "%d", 0
    digit_format db "%d",0
    file_name_format db "%s",0
    file_descriptor db -1
    file_mode db "r"
    len equ 1
    digit resb len
    space db " ", 0


segment code use32 class=code
    start:
        pusha
        push dword file_msg
        call [printf]
        add esp, 4
        popa
        
        pusha
        push dword file_name
        push dword file_name_format
        call [scanf]
        add esp, 4*2
        popa
         
        pusha
        push dword number_msg
        call [printf]
        add esp, 4
        popa
        
        pusha
        push dword number
        push dword number_format
        call [scanf]
        add esp,4*2
        popa

        pusha
        push file_mode
        push file_name
        call [fopen]
        add esp, 4*2
        mov [file_descriptor], eax
        popa

        cmp dword[file_descriptor], 0
        je final
        start_read:
            push dword [file_descriptor]
            push dword len
            push dword 1
            push digit
            call [fread]
            add esp, 4*4
            
            cmp byte[digit], "0"
            jb not_digit
            cmp byte[digit], "9"
            ja not_digit
                push dword [digit]
                push dword digit_format
                call [printf]
                add esp, 4*2
                
            not_digit:    
            cmp byte[digit], '-'
            jne start_read
                push dword [file_descriptor]
                push dword len
                push dword 1
                push digit
                call [fread]
                add esp, 4*4
                
                cmp byte[digit], ' '
                je start_read
                jmp not_digit
            
            cmp byte[digit], ' '
            jne start_read
                push dword [space]
                push dword digit_format
                call [printf]
                add esp, 4*2
            
            
        final:

        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        push    dword 0      
        call    [exit] 
        