.586
.model flat, stdcall
includelib kernel32.lib
includelib msvcrt.lib
includelib libucrt.lib
WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
SetConsoleTitleA PROTO : DWORD
GetStdHandle PROTO : DWORD

.code

outString PROC uses eax ebx ecx edi esi,
					   pstr: dword, ptitle: dword

	push ptitle
	call SetConsoleTitleA

	push -11
	call GetStdHandle

	mov esi, pstr
	mov edi, -1
	count:
	inc edi
	cmp byte ptr [esi +  edi], 0
	jne count

	push 0
	push 0
	push edi
	push pstr
	push eax
	call WriteConsoleA

	ret
outString ENDP
end