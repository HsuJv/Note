assume cs : code

a segment
	db 1, 2, 3, 4, 5, 6, 7, 8
a ends

b segment
	db 1, 2, 3, 4, 5, 6, 7, 8
b ends

d segment
	db 0, 0, 0, 0, 0, 0, 0, 0
d ends

code segment
start:
	mov ax, d
	mov ds, ax  ; ds = d
	xor bx, bx   ; [bx] = [0]
	mov ax, a
	mov es, ax

	mov cx, 8   ; loop for 8 times
s1:
	xor ax, ax
	mov al, es:[bx]
	mov [bx], al
	inc bx
	loop s1      ; end loop1

	mov ax, b
	mov es, ax
	xor bx, bx
	mov cx, 8

s2:
	xor ax, ax
	mov al, es:[bx]
	add [bx], al
	inc bx
	loop s2       ; end loop2

	mov ax, 4c00H
	int 21H

code ends
end start