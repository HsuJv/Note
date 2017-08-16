assume cs:codesg, ds:datasg

datasg segment
    db 'welcome to masm!'
datasg ends

codesg segment
start:
    mov     ax, datasg
    mov     ds, ax
    mov     ax, 0b872h
    mov     es, ax
    mov     si, 0
    mov     di, 72       ;列偏移量
    mov     cx, 16
s:
    mov     ax, 0ca00h
    mov     al, [si]
    mov     es:[di], ax
    add     di, 2
    inc     si

    mov     ax, 4c00h
    int     21h
codesg ends
end start