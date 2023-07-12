%define h rdi
%define w rsi
%define frame1 rdx
%define frame2 rcx
%define frame_out r8

section .text

global merge_frames_asm

; void merge_frames(int h,int w, unsigned char frame1[][w][3],unsigned char frame2[][w][3],unsigned char frame_out[][w][3])

merge_frames_asm:

    push rbp
    mov rbp, rsp

    push rbx
    push r12
    push r13
    push r14
    push r15

        xor r14, r14
        xor r12, r12 ; y = 0
    .Ly:
        cmp r12, h ; y < h
        jge .Lend ; end of the program if y >= h

        xor r13, r13 ; x = 0
    .Lx:
        cmp r13, w ; x < w
        jge .Lnext_y ; y++ if x >= w

        ; calculate offsets for frame1[y][x][0], frame2[y][x][0], and frame_out[y][x][0]
        ;mov rax, r12 ; move y to rax
        ;mul w ; multiply y with w
        ;add rax, r13 ; add the x to result 
        ;mov rbx, 3 ; multiply the result with 3 (red, blue, green)
        ;mul rbx
        ;mov r14, rax

        ; red pixel
        xor rbx, rbx ; in order to burn the gunk
        xor rax, rax ; in order to burn the gunk
        mov bl, [frame1 + 1 * r14] ; get the pixel from array1 to do operation with it
        mov al, [frame2 + 1 * r14] ; get the pixel from array2 to do operation with it
        add bx, ax ; add pixel values together
        cmp bx, 255
        jg .Lred_max
    .Lred_add:
        mov [frame_out + 1 * r14], bl ; put the output to the frame_out
        jmp .Lred_end
    .Lred_max:
        mov BYTE [frame_out + 1 * r14], 255 ; put the output to the frame_out
    .Lred_end:
        
        ; green pixel
        ; calculate offsets for frame1[y][x][1], frame2[y][x][1], and frame_out[y][x][1]
        inc r14 ; after red pixel here goes green pixel
        xor rbx, rbx ; in order to burn the gunk
        xor rax, rax ; in order to burn the gunk
        mov bl, [frame1 + 1 * r14] ; get the pixel from array1 to do operation with it
        mov al, [frame2 + 1 * r14] ; get the pixel from array2 to do operation with it
        add bx, ax ; add pixel values together
        cmp bx, 255
        jg .Lgreen_max
    .Lgreen_add:
        mov [frame_out + 1 * r14], bl ; put the output to the frame_out
        jmp .Lgreen_end
    .Lgreen_max:
        mov BYTE [frame_out + 1 * r14], 255 ; put the output to the frame_out
    .Lgreen_end:

        ; blue pixel
        ; calculate offsets for frame1[y][x][2], frame2[y][x][2], and frame_out[y][x][2]
        inc r14 ; after green pixel here goes blue pixel
        xor rbx, rbx ; in order to burn the gunk
        xor rax, rax ; in order to burn the gunk
        mov bl, [frame1 + 1 * r14] ; get the pixel from array1 to do operation with it
        mov al, [frame2 + 1 * r14] ; get the pixel from array2 to do operation with it
        add bx, ax ; add pixel values together
        cmp bx, 255
       jg .Lblue_max
    .Lblue_add:
        mov [frame_out + 1 * r14], bl ; put the output to the frame_out
        jmp .Lblue_end
    .Lblue_max:
        mov BYTE [frame_out + 1 * r14], 255 ; put the output to the frame_out 
    .Lblue_end: 

        inc r14
    .Lnext_x:
        inc r13 ; increase x -> x++
        jmp .Lx

    .Lnext_y:
        inc r12 ; increase y -> y++
        jmp .Ly

    .Lend:

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx

    pop rbp

	ret
