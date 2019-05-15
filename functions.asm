section .rodata
    input_format db '%f', 0
    output_format db '%lf', 10, 0

section .data
    one dq 1.0
    two dq 2.0
    fourteen dq 14.0
    six dq 6.0
    
section .bss
    tmp resq 1

section .text
global f1
f1:
    push ebp
    mov ebp, esp
    finit
    fldl2e
    fld qword[one]
    fld qword[ebp+8]
    fyl2x
    fdivr    
    leave
    ret 


global f2
f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fmul qword[two]
    fchs
    fadd qword[fourteen]
    leave
    ret 


global f3
f3:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fsub qword[two]
    fchs
    fld qword[one]
    fdivr
    fadd qword[six]
    leave
    ret 
    
global d_f1
d_f1:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fld qword[one]
    fdivr
    leave
    ret 

global d_f2
d_f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[two]
    fchs
    leave
    ret 
    
global d_f3
d_f3:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fsub qword[two]
    fchs
    fld qword[one]
    fdivr
    fst qword[tmp]
    fmul qword[tmp]
    leave
    ret 
