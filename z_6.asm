extern io_print_dec
section .data
    inx dq 0; 
    ipow dq 0;
    three dq 3.0 

section .text
global f1; 
global f2; 
global f3; 
global main

; функция 2^x+1 функция работает с модулями!!!
f1:
    push ebp; 
    mov ebp, esp; 
    sub esp, 4; 
    
    finit 
    ;fld qword[ebp+8]; st(0) = x      загружаем х
    fldpi; загружаем х              
    fld st0; st(0) = st(1) = x      дважды для сравнения
    frndint; ST(0)=[ST(0)]      округление x
    
    fcomi; сравниваем x с его округлением
    jge .then
    fld1
    fsub; если закруглили в большую сторону - вычитаем 1
    
.then:
    fxch
    fsub st1; x - [x]
    fxch
    fld1; 
    fscale; вычисляет 2^x, где х - целочисленное
    fstp qword[ipow]; сохраняем значение 2^x
    fxch
    f2xm1; 2^(x - [x]) - 1
    fld1
    fadd; 2^(x - [x])
    
    fadd qword[ipow]; 2^x
    fld1
    fadd ; 2^x + 1
    
    
    fstp qword[inx]

   
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
    ;fldpi
    fld st0; дважды для умножения
    
    fmul st0, st1; x^2
    fmul st0, st1; x^3
    fmul st0, st1; x^4
    fmulp; x^5

    add esp, 4; 
    leave; 
    ret;

; (1 - x) / 3       
f3:
    push ebp; 
    mov ebp, esp; 
    sub esp, 4;
    finit
    
    ;fldpi
    fld qword[ebp+8]; (1 - x)
    fld1; 
    
    fxch
    fsub
    fld qword[three]; 
    fdivp; (1 - x) / 3
    
    add esp, 4; 
    leave; 
    ret;
    
main:
    mov ebp, esp; for correct debugging
     
    call f1
    
    xor eax, eax
    ret
