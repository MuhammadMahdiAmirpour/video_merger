#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <windows.h>

typedef long long unsigned int uint64;

// Video resolution
#define W 1796
#define H 738

// Allocate a buffer to store one frame
// each pixel value is represented by 3 bytes (Red, Green, Blue)
// Each image is a 3D array (W x H x 3)

// Array are 32-bit aligned to use with SIMD aligned instruction in SSE2/AVX/etc.
// see https://gcc.gnu.org/onlinedocs/gcc-3.2/gcc/Variable-Attributes.html
unsigned char frame1[H][W][3]         __attribute__((aligned(32))) = {0}; // 32-bit aligned for SSE2/AVX
unsigned char frame2[H][W][3]         __attribute__((aligned(32))) = {0}; // 32-bit aligned for SSE2/AVX
unsigned char frame_out_base[H][W][3] __attribute__((aligned(32))) = {0}; // 32-bit aligned for SSE2/AVX
unsigned char frame_out[H][W][3]      __attribute__((aligned(32))) = {0}; // 32-bit aligned for SSE2/AVX


typedef void MergeFunc(int h,int w,unsigned char frame1[][W][3],unsigned char frame2[][W][3],unsigned char frame_out[][W][3]);

MergeFunc merge_frames;
MergeFunc merge_frames_opt;
MergeFunc merge_frames_asm;
MergeFunc merge_frames_simd;

// MergeFunc merge_frames_SSE2;
// MergeFunc merge_frames_AVX;
// MergeFunc *merge_frames_simd = merge_frames_AVX;



unsigned int lo,hi;             // used to measure   clock cycles
uint64 ticks, start, end;       // used for mesuring clock cycles

void tic() {
  asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));    // inline assembly
  start = ((uint64)hi << 32) | lo;
}

uint64 toc() {
  asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));    // inline assembly
  end = ((uint64)hi << 32) | lo;
  return end-start;
}

int array_diff(unsigned char frame1[][W][3],unsigned char frame2[][W][3]) {
  int n_diff = 0;
  int n_bytes = W*H*3;
  
  unsigned char *array1 = (unsigned char *) frame1;
  unsigned char *array2 = (unsigned char *) frame2;
   
  for (int i = 0; i < n_bytes; i++)
    if (array1[i] != array2[i])
      n_diff++;

  return n_diff;
}

int maximum(int a, int b) {
  return a > b ? a : b;
}

uint64 measure_tics_per_sec() {
  unsigned int lo,hi;             // used to measure   clock cycles
  uint64 start, end;       // used for mesuring clock cycles
    
  asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));    // inline assembly
    start = ((uint64)hi << 32) | lo;
        
    sleep(1);

    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));    // inline assembly
    end = ((uint64)hi << 32) | lo;

    return end-start;
}

int main() {
  int n_bytes = H * W * 3;

  uint64 total_time_c = 0;
  uint64 total_time_c_opt = 0;
  uint64 total_time_asm=0;
  uint64 total_time_simd=0;

  int c_opt_diff = 0;
  int asm_diff   = 0;
  int simd_diff  = 0;
  
  
  uint64 ticks_per_sec = measure_tics_per_sec();
  
  // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
  FILE *pipein1 = popen("ffmpeg -i input1_noisy.mov -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
  FILE *pipein2 = popen("ffmpeg -i input2_noisy.mov -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
  FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1796x738 -r 60 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 output.mp4", "w");
    
  // Process video frames
  while(1) {
    int diff;
    
    // Read a frame from each of the input pipes into the buffers
    int count1 = fread(frame1, 1, n_bytes, pipein1);
    int count2 = fread(frame2, 1, n_bytes, pipein2);

    
    // If we didn't get a frame of video, we're probably at the end
    if (count1 != n_bytes || count2 != n_bytes)
      break;
       

    tic();
    // C-Implementation
    merge_frames(H,W,frame1,frame2,frame_out_base);
    total_time_c += toc();

    tic();
    // C-Implementation (optimized)
    merge_frames_opt(H,W,frame1,frame2,frame_out); 
    total_time_c_opt += toc();

    c_opt_diff = maximum(c_opt_diff, array_diff(frame_out_base, frame_out));
    memset(frame_out, 0, n_bytes);
    
    tic();
    //TODO: write the body of this function in assembly
    merge_frames_asm(H,W,frame1,frame2,frame_out); 
    total_time_asm += toc();

    asm_diff = maximum(asm_diff, array_diff(frame_out_base, frame_out));
    memset(frame_out, 0, n_bytes);

    
    tic();
    //TODO: write the body of this function in assembly
    merge_frames_simd(H,W,frame1,frame2,frame_out);
    total_time_simd += toc();
    
    simd_diff = maximum(simd_diff, array_diff(frame_out_base, frame_out));
    memset(frame_out, 0, n_bytes);

    
    // Write to the output pipes
    fwrite(frame_out_base, 1, n_bytes, pipeout);
    
  }

  
    
  // Flush and close input and output pipes
  fflush(pipein1);
  pclose(pipein1);
  fflush(pipein2);
  pclose(pipein2);
  fflush(pipeout);
  pclose(pipeout);

  char *stats[] = {"PASSED!", "FAILED!"};
  
  printf("total_time (C)     = %f\n", total_time_c   / (double) ticks_per_sec);
  printf("total_time (C-OPT) = %f  (%s: %d of %d bytes incorrect)\n",
	 total_time_c_opt   / (double) ticks_per_sec,
	 stats[c_opt_diff != 0],
	 c_opt_diff, n_bytes);
  
  printf("total_time (ASM)   = %f  (%s: %d of %d bytes incorrect) \n",
	 total_time_asm / (double) ticks_per_sec,
	 stats[asm_diff != 0],
	 asm_diff, n_bytes);
  
  printf("total_time (SIMD)  = %f  (%s: %d of %d bytes incorrect) \n",
	 total_time_simd/ (double) ticks_per_sec,
	 stats[simd_diff != 0],
	 simd_diff, n_bytes);

  

  
  
}


