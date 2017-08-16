assume cs:codesg, ds:datasg, ss:stacksg

datasg segment
    db      'Welcome to masm!', 0
datasg ends

stacksg segment
    db      10 dup(0)
stacksg ends

codesg segment
start:
    mov     ax, datasg
    mov     ds, ax
    mov     ax, stacksg
    mov     ss, ax
    mov     ax, 0b800h
    mov     es, ax
    mov     dh, 8
    mov     dl, 3
    mov     cl, 2
    mov     si, 0
    call    print
    mov     ax, 4c00h
    int     21h

print:
;在第dh行，dl列打印ds:si指向的字符串
;无返回值
    xor     ax, ax
    mov     al, dh
    sub     ax, 1
    mov     bl, 0a0h
    mul     bl
    xor     dh, dh
    add     dx, dx
    add     ax, dx      
    sub     ax, 2   ;要打印的第一个字符的offset
    mov     bx, ax      
    mov     ah, cl
    xor     cx, cx
trans:      
    mov     cl, [si]
    jcxz    re
    mov     al, [si]
    mov     es:[bx], ax
    add     bx, 2
    inc     si
    loop    trans
re:
    ret


codesg ends
end start