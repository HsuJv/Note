assume cs:codesg
codesg segment
start:
        mov     ah, 75
        mov     bh, -6
        add     ah, bh
        mov     ah, -35
        mov     bh, -75
        add     ah, bh
        mov     ah, 120
        mov     bh, 18
        add     ah, bh
        mov     ax, 4c00h
        int     21h
codesg ends 
end start