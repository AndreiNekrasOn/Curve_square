%include 'io.inc'

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
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    and esp, -16
    
    mov eax, dword[x]
    mov dword[esp], eax
    mov eax, dword[x+4]
    mov dword[esp+4], eax 
    call f3
        
    mov dword[esp], output_format
    fstp qword[esp+4]
    call printf
    
    leave
    ret
    
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