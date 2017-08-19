assume cs:codesg
codesg segment
    mov     ax, 4c00h
    int     21h
start:
s:
    nop
    nop
    mov     di, offset s
    mov     si, offset s2
    mov     ax, cs:[si]
    mov     cs:[di], ax     ;把s2中的jmp short s1复制到s的第一条语句
                            ;但是偏移量是offset s1 - offset s2

s0:
    jmp     short   s

s1:
    mov     ax, 0
    int     21h
    mov     ax, 0

s2:
    jmp     short   s1
    nop
codesg ends
end start