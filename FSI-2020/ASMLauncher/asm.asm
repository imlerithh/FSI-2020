.586
.model flat, stdcall
includelib ../Debug/StaticLib.lib
randomness PROTO
transformatio PROTO: DWORD
quadrum PROTO: SDWORD
outInt PROTO:  SDWORD
outChar PROTO: DWORD
outString PROTO: DWORD, :DWORD
outBool PROTO: SDWORD
ExitProcess PROTO : DWORD


.stack 4096
.const
	_L2 dword 'E', 0
	_L7 byte "collapse/chaos", 10, 0
	_L8 dword 1
	_L9 sdword -3
	_L10 sdword -2
	_L11 byte "one", 10, 0
	_L12 sdword 3
	_L13 sdword 2
	_L14 byte "two", 10, 0
	_L15 sdword 9
	_L16 sdword 5
	_L17 sdword 3
	_L18 sdword 10
	_L19 sdword 0
	consoletitle db 'FSI-2020', 0
.data
	a dword 0
	z dword 0
	one sdword 0
	two sdword 0
	counter sdword 0

.code
fa PROC s:sdword
	push _L2
call transformatio
	push eax
	pop s
	mov eax, s
	ret
	mov eax,s
	ret
fa ENDP

main PROC
	push offset _L7
	pop a
	push one
call fa
	push eax
	pop one
	push one
call outInt
	push _L8
	pop z
	push _L9
	pop one
	push one
call outInt
	mov eax, z
	mov ebx, 0
cmp eax, ebx
ja true_if0
jmp continue_if0
true_if0:
	push _L10
call quadrum
	push eax
	pop one
continue_if0:
	push offset consoletitle
	push offset _L11
call outString
	push one
	push _L12
	pop eax
	pop ebx
add eax, ebx
	push eax
	push _L13
	pop eax
	pop ebx
imul ebx
	push eax
	pop one
	push one
call outInt
	push offset consoletitle
	push offset _L14
call outString
	push one
	push _L15
	push _L16
	pop ebx
	pop eax
	mov edx, 0
idiv ebx
	push edx
	pop ebx
	pop eax
sub eax, ebx
	push eax
	pop two
	push two
call outInt
	push offset consoletitle
	push a
call outString
call randomness
	push eax
	pop two
mov ecx, _L17
push _L17
pop counter
inc counter
_for0:
	push two
	push _L18
	pop ebx
	pop eax
	mov edx, 0
idiv ebx
	push eax
	pop two
	push two
call outInt
dec counter
mov ecx, counter
loop _for0
	push _L19
call ExitProcess
main ENDP
end main
