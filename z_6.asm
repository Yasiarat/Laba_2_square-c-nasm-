extern io_print_dec
section .data
    one dq 1
    inx dq 0; 
    ipow dq 0;
    three dd 3 

section .text
global f1; 
global f2; 
global f3; 
global main

; функция 2^x+1
f1:
    push ebp; 
    mov ebp, esp; 
    sub esp, 4; 
    
    finit 
    fld qword[ebp+8]; загружаем х
    fld qword[ebp+8]; дважды для сравнения
    frndint; округление x
    
    fcomi; сравниваем x с его округлением
    jle .then
    fisub dword[one]; если закруглили в большую сторону - вычитаем 1
    
.then:
    ;fst dword[inx]; сохраняем целую часть х
    fsub; x - [x]
    fld1; 
    fscale; вычисляет 2^x, где х - целочисленное
    fstp qword[ipow]; сохраняем значение 2^x
    fstp; удаляем 1. Теперь на поверхности лежит x - [x]
    f2xm1; 2^(x - [x]) - 1
    fadd qword[one]; 2^(x - [x])
    
    fadd dword[ipow]; 2^x
    fadd qword[one]; 2^x + 1
    
    
    fstp qword[inx]
    mov eax, dword[inx]; 
    call io_print_dec
    
    
    add esp, 4; 
    leave; 
    ret; 

; x^5  
f2:
    push ebp; 
    mov ebp, esp; 
    sub esp, 4;   
    
    finit 
    fld dword[ebp+8]; загружаем х
    fld dword[ebp+8]; дважды для умножения
    
    xor ebx, ebx; 
    
.loop:
    cmp ebx, 4; 
    je .out
    
    fmul; ST(1) = ST(0) * ST(1);
    
    inc ebx 
    jmp .loop

.out:
    fstp; на поверхности лежит x^5
    add esp, 4; 
    leave; 
    ret;

; (1 - x) / 3       
f3:
    push ebp; 
    mov ebp, esp; 
    sub esp, 4;
    finit
    
    fld dword[one]; 
    fsub dword[ebp+8]; (1 - x)
    fld dword[three]; 
    fdivp; (1 - x) / 3
    
    add esp, 4; 
    leave; 
    ret;
    
main:
    mov ebp, esp; for correct debugging
    mov eax, 3; 
    push eax; 
    call f1
    
    xor eax, eax
    ret