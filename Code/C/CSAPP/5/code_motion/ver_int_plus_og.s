    .file   "ver.c"
    .text
    .globl  new_ver
    .type   new_ver, @function
new_ver:
.LFB38:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    pushq   %rbx
    .cfi_def_cfa_offset 24
    .cfi_offset 3, -24
    subq    $8, %rsp
    .cfi_def_cfa_offset 32
    movq    %rdi, %rbp
    movl    $8, %edi
    call    malloc
    testq   %rax, %rax
    je  .L4
    movq    %rax, %rbx
    movq    %rbp, (%rax)
    testq   %rbp, %rbp
    jle .L5
    movl    $8, %esi
    movq    %rbp, %rdi
    call    calloc
    testq   %rax, %rax
    jne .L3
    movq    %rbx, %rdi
    call    free
    movl    $0, %eax
    jmp .L2
.L5:
    movl    $0, %eax
.L3:
    movq    %rax, 8(%rbx)
    movq    %rbx, %rax
    jmp .L2
.L4:
    movl    $0, %eax
.L2:
    addq    $8, %rsp
    .cfi_def_cfa_offset 24
    popq    %rbx
    .cfi_def_cfa_offset 16
    popq    %rbp
    .cfi_def_cfa_offset 8
    ret
    .cfi_endproc
.LFE38:
    .size   new_ver, .-new_ver
    .globl  get_vec_element
    .type   get_vec_element, @function
get_vec_element:
.LFB39:
    .cfi_startproc
    testq   %rsi, %rsi
    js  .L9
    cmpq    (%rdi), %rsi
    jge .L10
    movq    8(%rdi), %rax
    movq    (%rax,%rsi,8), %rax
    movq    %rax, (%rdx)
    movl    $1, %eax
    ret
.L9:
    movl    $0, %eax
    ret
.L10:
    movl    $0, %eax
    ret
    .cfi_endproc
.LFE39:
    .size   get_vec_element, .-get_vec_element
    .globl  vec_length
    .type   vec_length, @function
vec_length:
.LFB40:
    .cfi_startproc
    movq    (%rdi), %rax
    ret
    .cfi_endproc
.LFE40:
    .size   vec_length, .-vec_length
    .globl  combine1
    .type   combine1, @function
combine1:
.LFB41:
    .cfi_startproc
    pushq   %r12
    .cfi_def_cfa_offset 16
    .cfi_offset 12, -16
    pushq   %rbp
    .cfi_def_cfa_offset 24
    .cfi_offset 6, -24
    pushq   %rbx
    .cfi_def_cfa_offset 32
    .cfi_offset 3, -32
    subq    $16, %rsp
    .cfi_def_cfa_offset 48
    movq    %rdi, %r12
    movq    %rsi, %rbp
    movq    %fs:40, %rax
    movq    %rax, 8(%rsp)
    xorl    %eax, %eax
    movq    $0, (%rsi)
    movl    $0, %ebx
    jmp .L13
.L14:
    movq    %rsp, %rdx
    movq    %rbx, %rsi
    movq    %r12, %rdi
    call    get_vec_element
    movq    (%rsp), %rax
    addq    %rax, 0(%rbp)
    addq    $1, %rbx
.L13:
    movq    %r12, %rdi
    call    vec_length  ; CALL WITHIN LOOP
    cmpq    %rax, %rbx
    jl  .L14
    movq    8(%rsp), %rax
    xorq    %fs:40, %rax
    je  .L15
    call    __stack_chk_fail
.L15:
    addq    $16, %rsp
    .cfi_def_cfa_offset 32
    popq    %rbx
    .cfi_def_cfa_offset 24
    popq    %rbp
    .cfi_def_cfa_offset 16
    popq    %r12
    .cfi_def_cfa_offset 8
    ret
    .cfi_endproc
.LFE41:
    .size   combine1, .-combine1
    .globl  combine2
    .type   combine2, @function
combine2:
.LFB42:
    .cfi_startproc
    pushq   %r13
    .cfi_def_cfa_offset 16
    .cfi_offset 13, -16
    pushq   %r12
    .cfi_def_cfa_offset 24
    .cfi_offset 12, -24
    pushq   %rbp
    .cfi_def_cfa_offset 32
    .cfi_offset 6, -32
    pushq   %rbx
    .cfi_def_cfa_offset 40
    .cfi_offset 3, -40
    subq    $24, %rsp
    .cfi_def_cfa_offset 64
    movq    %rdi, %r13
    movq    %rsi, %rbp
    movq    %fs:40, %rax
    movq    %rax, 8(%rsp)
    xorl    %eax, %eax
    call    vec_length ; CALL OUTSIDE THE LOOP
    movq    %rax, %r12
    movq    $0, 0(%rbp)
    movl    $0, %ebx
    jmp .L18
.L19:
    movq    %rsp, %rdx
    movq    %rbx, %rsi
    movq    %r13, %rdi
    call    get_vec_element
    movq    (%rsp), %rax
    addq    %rax, 0(%rbp)
    addq    $1, %rbx
.L18:
    cmpq    %r12, %rbx
    jl  .L19
    movq    8(%rsp), %rax
    xorq    %fs:40, %rax
    je  .L20
    call    __stack_chk_fail
.L20:
    addq    $24, %rsp
    .cfi_def_cfa_offset 40
    popq    %rbx
    .cfi_def_cfa_offset 32
    popq    %rbp
    .cfi_def_cfa_offset 24
    popq    %r12
    .cfi_def_cfa_offset 16
    popq    %r13
    .cfi_def_cfa_offset 8
    ret
    .cfi_endproc
.LFE42:
    .size   combine2, .-combine2
    .ident  "GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
    .section    .note.GNU-stack,"",@progbits
