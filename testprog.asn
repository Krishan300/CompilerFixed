    global main
    extern printf

    segment .bss
    a$1 resq 1
    a$2 resq 1
    b$1 resq 1
    c$1 resq 1

    section .text
main:
    pop qword[a$1]
    mov rax,23
    push rax
    pop qword[a$2]
    mov rax,24
    push rax
    pop qword[b$1]
    push qword[a$2]
    push qword[b$1]
    pop rbx
    pop rax
    imul rbx
    push rax
    mov rax,25
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[c$1]
L2:
    push qword[a$2]
    mov rax,30
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jl L6
    mov rax,0
    jmp L7
L6:
    mov rax,1
L7:
    push rax
    pop rax
    cmp rax,0
    je L3
    push qword[a$2]
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[a$2]
    jmp L2
L3:
    push qword[a$2]
    push qword[c$1]
    mov rax,2
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    mov rax,16
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jl L8
    mov rax,0
    jmp L9
L8:
    mov rax,1
L9:
    push rax
    push qword[a$2]
    mov rax,8
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jge L10
    mov rax,0
    jmp L11
L10:
    mov rax,1
L11:
    push rax
    pop rbx
    pop rax
    and rax,rbx
    push rax
    pop rax
    cmp rax,0
    je L4
    mov rax,5
    push rax
    pop qword[c$1]
    jmp L5
L4:
    push qword[a$2]
    push qword[b$1]
    mov rdi,fmt1
    pop rdx
    pop rsi
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,123456
    push rax
    pop qword[c$1]
L5:

    section .data
    fmt1: db `%ld %ld\n`, 0
