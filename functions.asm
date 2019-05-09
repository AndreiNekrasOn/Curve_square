section .rodata
    input_format db '%f', 0
    output_format db '%lf', 10, 0

section .data
    one dq 1.0
    two dq 2.0
    fourteen dq 14.0
    six dq 6.0
    x dq 10.0

section .text
global _f1
_f1:
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


global _f2
_f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fmul qword[two]
    fchs
    fadd qword[fourteen]
    leave
    ret 


global _f3
_f3:
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