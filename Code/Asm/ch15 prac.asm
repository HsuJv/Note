assume cs:codesg, ss:stacksg, ds:datasg

datasg segment
    db      8 dup(0)
datasg ends

stacksg segment
    db      32 dup(0)
stacksg ends

codesg segment
start:
    mov     ax, 0
    mov     es, ax
    mov     ax, datasg
    mov     ds, ax
    mov     ax, stacksg
    mov     ss, ax
    mov     sp, 32

    push    word ptr    es:[24h]
    push    word ptr    es:[26h]
    pop     word ptr    ds:[2]
    pop     word ptr    ds:[0]  

    mov     word ptr    es:[24h], offset newInt9
    mov     word ptr    es:[26h], cs

    mov     ax, 0b800h
    mov     es, ax
    mov     ah, 'a'
    mov     al, 02h
    mov     es:[160*12+40*2+1], al
lo:
    mov     es:[160*12+40*2], ah
    call    delay
    inc     ah
    cmp     ah, 'z'+1
    jne     lo

    xor     ax, ax
    mov     es, ax
    push    word ptr    ds:[0]
    push    word ptr    ds:[2]
    pop     word ptr    es:[26h]
    pop     word ptr    es:[24h]

    mov     ax, 4c00h
    int     21h

delay:
    push    ax
    push    dx
    xor     ax, ax
    mov     dx, 1000h

de:
    sub     ax, 1
    sbb     dx, 0
    cmp     ax, 0
    jne     de
    cmp     dx, 0
    jne     de

    pop     dx
    pop     ax
    ret


newInt9:
    push    ax
    push    bx
    push    es

    pushf
    pushf
    pop     bx
    and     bh, 11111100b
    push    bx
    popf
    call    dword ptr   ds:[0]

    in      al, 60h
    cmp     al, 1
    jne     newInt9re

    mov     ax, 0b800h
    mov     es, ax
    inc     byte ptr    es:[160*12+40*2+1]

newInt9re:
    pop     es
    pop     bx
    pop     ax
    iret

codesg ends
end start

