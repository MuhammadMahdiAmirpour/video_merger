%define height rdi
%define width rsi
%define frame1 rdx
%define frame2 rax
; actually frame2 is rcx but we move it to the rax register so we can use loop instruction
%define frame_out r8

section .text

; void merge_frames(int h,int w, unsigned char frame1[][w][3],unsigned char frame2[][w][3],unsigned char frame_out[][w][3]){
global merge_frames_simd

merge_frames_simd:

  push rbp
  mov rbp, rsp

  mov rax, rcx

  pxor mm1, mm1
  pxor mm2, mm2
  movd mm1, height
  movd mm2, width
  pmuludq mm1, mm2
  mov rcx, 3
  movd mm2, rcx
  pmuludq mm1, mm2
  psrlq mm1, 3
  movd rcx, mm1

loop:

  movq mm0, [frame1]
  paddusb mm0, [frame2]
  movq [frame_out], mm0

  add frame1, 8
  add frame2, 8
  add frame_out, 8

  loop loop

  pop rbp
  ret
