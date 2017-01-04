    global main
    extern printf

    segment .bss
    a$1 resq 1
    b$1 resq 1
    c$1 resq 1
    d$1 resq 1
    e$1 resq 1
    b$2 resq 1

    section .text
juicy:
    pop r15
    pop qword[a$1]
    pop qword[b$1]
    pop qword[c$1]
L3:
    push qword[a$1]
    push qword[b$1]
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    push qword[c$1]
    pop rbx
    pop rax
    cmp rax,rbx
    jg L5
    mov rax,0
    jmp L6
L5:
    mov rax,1
L6:
    push rax
    push qword[c$1]
    push qword[a$1]
    pop rbx
    pop rax
    cmp rax,rbx
     je L7
    mov rax,0
    jmp L8
L7:
    mov rax,1
L8:
    push rax
    pop rbx
    pop rax
    and rax,rbx
    push rax
    pop rax
    cmp rax,0
    je L4
    push qword[a$1]
    push qword[c$1]
    pop rbx
    pop rax
    cmp rax,rbx
    jg L9
    mov rax,0
    jmp L10
L9:
    mov rax,1
L10:
    push rax
    pop rax
    cmp rax,0
    je L2
    push qword[c$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[b$1]
L2:
    push qword[d$1]
    push qword[e$1]
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[b$2]
    jmp L3
L4:

    section .data
