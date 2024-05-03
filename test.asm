extern io_print_dec
section .data
    a dq 1.5
section .text
global main
main:
    mov ebp, esp; for correct debugging
    fld qword[a]; 
    frndint; 
    fstp qword[a]
    mov eax, [a]
    call io_print_dec
    xor eax, eax
    ret