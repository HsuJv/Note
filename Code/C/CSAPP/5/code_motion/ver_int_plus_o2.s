    .file   "ver.c"
    .section    .text.unlikely,"ax",@progbits
.LCOLDB0:
    .text
.LHOTB0:
    .p2align 4,,15
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
    movq    %rdi, %rbp
    movl    $8, %edi
    subq    $8, %rsp
    .cfi_def_cfa_offset 32
    call    malloc
    testq   %rax, %rax
    je  .L4
    testq   %rbp, %rbp
    movq    %rax, %rbx
    movq    %rbp, (%rax)
    jle .L5
    movl    $8, %esi
    movq    %rbp, %rdi
    call    calloc
    testq   %rax, %rax
    je  .L8
.L3:
    movq    %rax, 8(%rbx)
    movq    %rbx, %rax
.L2:
    addq    $8, %rsp
    .cfi_remember_state
    .cfi_def_cfa_offset 24
    popq    %rbx
    .cfi_def_cfa_offset 16
    popq    %rbp
    .cfi_def_cfa_offset 8
    ret
    .p2align 4,,10
    .p2align 3
.L5:
    .cfi_restore_state
    xorl    %eax, %eax
    jmp .L3
    .p2align 4,,10
    .p2align 3
.L4:
    xorl    %eax, %eax
    jmp .L2
.L8:
    movq    %rbx, %rdi
    call    free
    xorl    %eax, %eax
    jmp .L2
    .cfi_endproc
.LFE38:
    .size   new_ver, .-new_ver
    .section    .text.unlikely
.LCOLDE0:
    .text
.LHOTE0:
    .section    .text.unlikely
.LCOLDB1:
    .text
.LHOTB1:
    .p2align 4,,15
    .globl  get_vec_element
    .type   get_vec_element, @function
get_vec_element:
.LFB39:
    .cfi_startproc
    xorl    %eax, %eax
    testq   %rsi, %rsi
    js  .L10
    cmpq    (%rdi), %rsi
    jge .L10
    movq    8(%rdi), %rax
    movq    (%rax,%rsi,8), %rax
    movq    %rax, (%rdx)
    movl    $1, %eax
    ret
    .p2align 4,,10
    .p2align 3
.L10:
    rep ret
    .cfi_endproc
.LFE39:
    .size   get_vec_element, .-get_vec_element
    .section    .text.unlikely
.LCOLDE1:
    .text
.LHOTE1:
    .section    .text.unlikely
.LCOLDB2:
    .text
.LHOTB2:
    .p2align 4,,15
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
    .section    .text.unlikely
.LCOLDE2:
    .text
.LHOTE2:
    .section    .text.unlikely
.LCOLDB3:
    .text
.LHOTB3:
    .p2align 4,,15
    .globl  combine1
    .type   combine1, @function
combine1:
.LFB41:
    .cfi_startproc
    movq    $0, (%rsi)  ; *dest = 0
    xorl    %edx, %edx  ; %rdx = 0
    xorl    %eax, %eax  ; %rax = 0
    cmpq    $0, (%rdi)  ; if v->len <= 0 return
    jle .L14
    .p2align 4,,10
    .p2align 3
.L19:
    testq   %rax, %rax  ; if %rax < 0 jump .L16
    js  .L16
    movq    8(%rdi), %rcx ; %rcx = v->data
    movq    (%rcx,%rax,8), %rcx     ; %rcx = v->data[i]
.L16:
    addq    %rcx, %rdx  ; %rdx += %rcx
    addq    $1, %rax    ; %rax += 1 /* %rax correspond to  i */
    movq    %rdx, (%rsi); *dest = %rdx
    cmpq    %rax, (%rdi); if i < v->len jump .L19
    jg  .L19
.L14:
    rep ret
    .cfi_endproc
.LFE41:
    .size   combine1, .-combine1
    .section    .text.unlikely
.LCOLDE3:
    .text
.LHOTE3:
    .section    .text.unlikely
.LCOLDB4:
    .text
.LHOTB4:
    .p2align 4,,15
    .globl  combine2
    .type   combine2, @function
combine2:
.LFB42:
    .cfi_startproc
    movq    (%rdi), %r8 ; %r8 = v->len
    xorl    %edx, %edx  ; %rdx = 0
    xorl    %eax, %eax  ; %rax = 0
    movq    $0, (%rsi)  ; *dest = 0
    testq   %r8, %r8    ; if %r8(v->len) <= 0 return
    jle .L21
    .p2align 4,,10
    .p2align 3
.L26:
    testq   %rax, %rax  ; if %rax(i) < 0 jump .L23
    js  .L23
    cmpq    %rax, (%rdi); if %rax(i) >= v->len jump .L23
    jle .L23
    movq    8(%rdi), %rcx ; %rcx = v->data
    movq    (%rcx,%rax,8), %rcx ; %rcx = v->data[i]
.L23:
    addq    $1, %rax ; %rax += 1
    addq    %rcx, %rdx  ; %rdx += v->data[i]
    cmpq    %rax, %r8   
    movq    %rdx, (%rsi); *dest = %rdx
    jne .L26            ; if i != %r8(v->len) jump .L26
.L21:
    rep ret
    .cfi_endproc
.LFE42:
    .size   combine2, .-combine2
    .section    .text.unlikely
.LCOLDE4:
    .text
.LHOTE4:
    .ident  "GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
    .section    .note.GNU-stack,"",@progbits
