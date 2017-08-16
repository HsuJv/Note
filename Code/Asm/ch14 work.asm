assume cs:codesg

codesg segment
start:
    mov     al, 08h
    out     70h, al
    in      al, 71h     ;获得月份的bcd码
    mov     ah, al
    mov     cl, 4
    shr     ah, cl
    and     al, 00001111b
    add     ax, 3030h
    mov     dh, al
    mov     dl, ah
    mov     ah, 02h 
    int     21h
    mov     dl, dh
    int     21h
    mov     ah, 4ch
    mov     al, 00
    int     21h
codesg ends
end start