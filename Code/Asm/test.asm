assume cs:codesg
codesg segment
start:
        mov    ax, 0
        mov    cx, 8
loop1:
        push   cx
        mov    cx, 5
loop2:
        inc    ax
        loop   loop2
        pop    cx
        loop   loop1

        mov    ax, 4c00h
        int    21h
codesg ends 
end start