assume cs:codesg, ss:stacksg

stacksg segment
    dw      10 dup(0)
stacksg ends

codesg segment
start:
    mov     ax, stacksg
    mov     ss, ax
    mov     ax, 4240h
    mov     dx, 000fh
    mov     cx, 0ah
    call    divdw
    mov     ax, 4c00h
    int     21h

divdw:
;进行不会溢出的除法运算, 被除数为dword, 除数为word
;结果为dword
;输入: ax = 被除数的低16位, dx = 被除数的高16位
;cx = 除数
;返回: ax = 商的低16位, dx = 商的高16位
;cx = 余数
    push    ax
    mov     ax, dx
    xor     dx, dx
    div     cx
    pop     bx
    push    ax
    mov     ax, bx
    div     cx
    mov     cx, dx
    pop     dx
    ret

codesg ends
end start