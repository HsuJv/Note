assume cs:codesg, ds:datasg, ss:stacksg

datasg segment
    db     '1975','1976','1977','1978','1979','1980','1981','1982','1983'
    db     '1984','1985','1986','1987','1988','1989','1990','1991','1992'
    db     '1993','1994','1995'    ; 21年
    dd      16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065 
    dd      97479, 140417, 197514, 345980, 590827, 803530, 1183000, 1843000, 2759000
    dd      3753000, 4649000, 5937000    ; 21年内的总收入
    dw      3, 7, 9, 12, 28, 38, 130, 220, 476
    dw      778, 1001, 1442, 2258, 2793, 4037, 5635, 8226, 11542
    dw      14430, 15257, 17800  ; 21年雇佣员工数
datasg ends

table segment
    db      21  dup('year summ ne ?? ')
table ends

stacksg segment
    dd      0, 0, 0
stacksg ends

codesg segment
start:
    mov     ax, datasg
    mov     ds, ax
    mov     ax, table
    mov     es, ax
    mov     ax, stacksg
    mov     ss, ax
    mov     sp, 6
    mov     si, 84      ; 指向总收入
    mov     di, 168     ; 指向总人数
    mov     bp, 0       ; bp = 0, 用于指向目标内存
    mov     cx, 21
l1:
    push    cx
    mov     cx, 4
    push    si
    xor     si, si
l2:
    mov     al, [bx+si]
    mov     es:[bp+si], al
    inc     si
    loop    l2      ; l2完成年份的复制

    pop     si
    add     bp, 5   ; bp = 5
    mov     ax, [si]
    mov     es:[bp], ax
    add     si, 2
    mov     dx, [si]
    mov     es:[bp+2], dx
    add     si, 2
    add     bp, 8   ; bp = 13
    div     word ptr    [di]
    mov     es:[bp], ax
    mov     word ptr    ax, [di]
    sub     bp, 3   ; bp = 10
    mov     es:[bp], ax
    add     di, 2
    add     bp, 6   ; bp = 16
    pop     cx
    add     bx, 4
    loop    l1

    mov     ax, 4c00h
    int     21h
codesg ends
end start
