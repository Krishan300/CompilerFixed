    global main
    extern printf

    segment .bss
    month$1 resq 1
    year$1 resq 1
    day$1 resq 1
    h$1 resq 1
    firstday$1 resq 1
    lastday$1 resq 1
    tmp$1 resq 1
    dday$1 resq 1
    nrows$1 resq 1
    row$1 resq 1
    colday$1 resq 1

    section .text
main:
    mov rax,12
    push rax
    pop qword[month$1]
    mov rax,2016
    push rax
    pop qword[year$1]
    push qword[month$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L31
    mov rax,0
    jmp L32
L31:
    mov rax,1
L32:
    push rax
    push qword[month$1]
    mov rax,2
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L33
    mov rax,0
    jmp L34
L33:
    mov rax,1
L34:
    push rax
    pop rbx
    pop rax
    or rax,rbx
    push rax
    pop rax
    cmp rax,0
    je L2
    push qword[month$1]
    mov rax,12
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[month$1]
    push qword[year$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    sub rax,rbx
    push rax
    pop qword[year$1]
L2:
    mov rax,1
    push rax
    pop qword[day$1]
    push qword[day$1]
    push qword[month$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    mov rax,26
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    mov rax,10
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    push qword[year$1]
    pop rbx
    pop rax
    add rax,rbx
    push rax
    push qword[year$1]
    mov rax,4
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    mov rax,6
    push rax
    push qword[year$1]
    mov rax,100
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    push qword[year$1]
    mov rax,400
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[h$1]
    push qword[h$1]
    push qword[h$1]
    mov rax,7
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    mov rax,7
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    pop rbx
    pop rax
    sub rax,rbx
    push rax
    pop qword[firstday$1]
    push qword[month$1]
    mov rax,12
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jg L35
    mov rax,0
    jmp L36
L35:
    mov rax,1
L36:
    push rax
    pop rax
    cmp rax,0
    je L3
    push qword[month$1]
    mov rax,12
    push rax
    pop rbx
    pop rax
    sub rax,rbx
    push rax
    pop qword[month$1]
    push qword[year$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[year$1]
L3:
    mov rax,0
    push rax
    pop qword[lastday$1]
    push qword[month$1]
    mov rax,4
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L37
    mov rax,0
    jmp L38
L37:
    mov rax,1
L38:
    push rax
    push qword[month$1]
    mov rax,6
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L39
    mov rax,0
    jmp L40
L39:
    mov rax,1
L40:
    push rax
    pop rbx
    pop rax
    or rax,rbx
    push rax
    push qword[month$1]
    mov rax,9
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L41
    mov rax,0
    jmp L42
L41:
    mov rax,1
L42:
    push rax
    pop rbx
    pop rax
    or rax,rbx
    push rax
    push qword[month$1]
    mov rax,11
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L43
    mov rax,0
    jmp L44
L43:
    mov rax,1
L44:
    push rax
    pop rbx
    pop rax
    or rax,rbx
    push rax
    pop rax
    cmp rax,0
    je L4
    mov rax,30
    push rax
    pop qword[lastday$1]
    jmp L5
L4:
    push qword[month$1]
    mov rax,2
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     jne L45
    mov rax,0
    jmp L46
L45:
    mov rax,1
L46:
    push rax
    pop rax
    cmp rax,0
    je L6
    mov rax,31
    push rax
    pop qword[lastday$1]
    jmp L7
L6:
    push qword[year$1]
    call leapyear
    push rax
    pop rax
    cmp rax,0
    je L8
    mov rax,29
    push rax
    pop qword[lastday$1]
    jmp L9
L8:
    mov rax,28
    push rax
    pop qword[lastday$1]
L9:
L7:
L5:
    push qword[month$1]
    call printmonth
    push rax
    pop qword[tmp$1]
    mov rdi,fmt1
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,2
    push rax
    push qword[firstday$1]
    pop rbx
    pop rax
    sub rax,rbx
    push rax
    pop qword[dday$1]
    push qword[firstday$1]
    push qword[lastday$1]
    pop rbx
    pop rax
    add rax,rbx
    push rax
    mov rax,7
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[nrows$1]
    mov rax,1
    push rax
    pop qword[row$1]
L14:
    push qword[row$1]
    push qword[nrows$1]
    pop rbx
    pop rax
    cmp rax,rbx
    jle L47
    mov rax,0
    jmp L48
L47:
    mov rax,1
L48:
    push rax
    pop rax
    cmp rax,0
    je L15
    mov rax,1
    push rax
    pop qword[colday$1]
L12:
    push qword[colday$1]
    mov rax,7
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jle L49
    mov rax,0
    jmp L50
L49:
    mov rax,1
L50:
    push rax
    pop rax
    cmp rax,0
    je L13
    push qword[dday$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jl L51
    mov rax,0
    jmp L52
L51:
    mov rax,1
L52:
    push rax
    push qword[dday$1]
    push qword[lastday$1]
    pop rbx
    pop rax
    cmp rax,rbx
    jg L53
    mov rax,0
    jmp L54
L53:
    mov rax,1
L54:
    push rax
    pop rbx
    pop rax
    or rax,rbx
    push rax
    pop rax
    cmp rax,0
    je L10
    mov rdi,fmt2
    mov rax,0
    push rbp
    call printf
    pop rbp
    jmp L11
L10:
    push qword[dday$1]
    mov rdi,fmt3
    pop rsi
    mov rax,0
    push rbp
    call printf
    pop rbp
L11:
    push qword[colday$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[colday$1]
    push qword[dday$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[dday$1]
    jmp L12
L13:
    mov rdi,fmt4
    mov rax,0
    push rbp
    call printf
    pop rbp
    push qword[row$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    add rax,rbx
    push rax
    pop qword[row$1]
    jmp L14
L15:
    mov rdi,fmt5
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    ret
leapyear:
    pop r15
    pop qword[year$1]
    push qword[year$1]
    mov rax,4
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    mov rax,4
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    push qword[year$1]
    pop rbx
    pop rax
    cmp rax,rbx
     jne L55
    mov rax,0
    jmp L56
L55:
    mov rax,1
L56:
    push rax
    pop rax
    cmp rax,0
    je L16
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L16:
    push qword[year$1]
    mov rax,100
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    mov rax,100
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    push qword[year$1]
    pop rbx
    pop rax
    cmp rax,rbx
     jne L57
    mov rax,0
    jmp L58
L57:
    mov rax,1
L58:
    push rax
    pop rax
    cmp rax,0
    je L17
    mov rax,1
    push rax
    pop rax
    push r15
    ret
L17:
    push qword[year$1]
    mov rax,400
    push rax
    mov rdx,0
    pop rbx
    pop rax
    idiv rbx
    push rax
    mov rax,400
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    push qword[year$1]
    pop rbx
    pop rax
    cmp rax,rbx
     je L59
    mov rax,0
    jmp L60
L59:
    mov rax,1
L60:
    push rax
    pop rax
    cmp rax,0
    je L18
    mov rax,1
    push rax
    pop rax
    push r15
    ret
L18:
    mov rax,0
    push rax
    pop rax
    push r15
    ret
printmonth:
    pop r15
    pop qword[month$1]
    push qword[month$1]
    mov rax,1
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L61
    mov rax,0
    jmp L62
L61:
    mov rax,1
L62:
    push rax
    pop rax
    cmp rax,0
    je L19
    mov rdi,fmt6
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L19:
    push qword[month$1]
    mov rax,2
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L63
    mov rax,0
    jmp L64
L63:
    mov rax,1
L64:
    push rax
    pop rax
    cmp rax,0
    je L20
    mov rdi,fmt7
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L20:
    push qword[month$1]
    mov rax,3
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L65
    mov rax,0
    jmp L66
L65:
    mov rax,1
L66:
    push rax
    pop rax
    cmp rax,0
    je L21
    mov rdi,fmt8
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L21:
    push qword[month$1]
    mov rax,4
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L67
    mov rax,0
    jmp L68
L67:
    mov rax,1
L68:
    push rax
    pop rax
    cmp rax,0
    je L22
    mov rdi,fmt9
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L22:
    push qword[month$1]
    mov rax,5
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L69
    mov rax,0
    jmp L70
L69:
    mov rax,1
L70:
    push rax
    pop rax
    cmp rax,0
    je L23
    mov rdi,fmt10
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L23:
    push qword[month$1]
    mov rax,6
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L71
    mov rax,0
    jmp L72
L71:
    mov rax,1
L72:
    push rax
    pop rax
    cmp rax,0
    je L24
    mov rdi,fmt11
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L24:
    push qword[month$1]
    mov rax,7
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L73
    mov rax,0
    jmp L74
L73:
    mov rax,1
L74:
    push rax
    pop rax
    cmp rax,0
    je L25
    mov rdi,fmt12
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L25:
    push qword[month$1]
    mov rax,8
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L75
    mov rax,0
    jmp L76
L75:
    mov rax,1
L76:
    push rax
    pop rax
    cmp rax,0
    je L26
    mov rdi,fmt13
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L26:
    push qword[month$1]
    mov rax,9
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L77
    mov rax,0
    jmp L78
L77:
    mov rax,1
L78:
    push rax
    pop rax
    cmp rax,0
    je L27
    mov rdi,fmt14
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L27:
    push qword[month$1]
    mov rax,10
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L79
    mov rax,0
    jmp L80
L79:
    mov rax,1
L80:
    push rax
    pop rax
    cmp rax,0
    je L28
    mov rdi,fmt15
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L28:
    push qword[month$1]
    mov rax,11
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L81
    mov rax,0
    jmp L82
L81:
    mov rax,1
L82:
    push rax
    pop rax
    cmp rax,0
    je L29
    mov rdi,fmt16
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L29:
    push qword[month$1]
    mov rax,12
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
     je L83
    mov rax,0
    jmp L84
L83:
    mov rax,1
L84:
    push rax
    pop rax
    cmp rax,0
    je L30
    mov rdi,fmt17
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax,0
    push rax
    pop rax
    push r15
    ret
L30:
    mov rax,1
    push rax
    pop rax
    push r15
    ret

    section .data
    fmt1: db `Su Mo Tu We Th Fr Sa\n`, 0
    fmt2: db `   `, 0
    fmt3: db `%2d `, 0
    fmt4: db `\n`, 0
    fmt5: db `\n`, 0
    fmt6: db `       January\n`, 0
    fmt7: db `      February\n`, 0
    fmt8: db `        March\n`, 0
    fmt9: db `        April\n`, 0
    fmt10: db `         May\n`, 0
    fmt11: db `        June\n`, 0
    fmt12: db `        July\n`, 0
    fmt13: db `       August\n`, 0
    fmt14: db `      September\n`, 0
    fmt15: db `       October\n`, 0
    fmt16: db `      November\n`, 0
    fmt17: db `      December\n`, 0
