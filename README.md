<!-- Header -->
<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=0,2,3,5,6&height=180&section=header&text=Video%20Merger&fontSize=36&fontAlignY=35&animation=twinkling"/>
</div>

# Video Merger

This repository contains the final project of my assembly course at university. The project is a video merger implemented using C and Assembly, supporting both 32-bit and 64-bit architectures. It demonstrates the practical application of assembly programming in multimedia processing.

## 🛠️ Technologies Used

- **C**: Core implementation and high-level operations
- **Assembly (NASM)**: Low-level optimizations for both 32-bit and 64-bit architectures
- **CMake**: Build system configuration
- **Make**: Build automation

## 📚 Project Description

The Video Merger project is designed to merge two video files into a single output file, implementing efficient video processing techniques using both C and Assembly language. The project showcases the integration of low-level assembly programming with higher-level C code for optimal performance.

## 🎯 Features

- **Dual Architecture Support**: 
  - 32-bit implementation (`merge_32`)
  - 64-bit implementation (`merge_64`)
- **Efficient Video Processing**: Optimized video merging using assembly language
- **Flexible Build System**: CMake-based build configuration with architecture selection
- **Linux Platform Support**: Specifically designed for Linux operating systems

## 🏗️ Project Structure

```
video_merger/
├── main.c                 # Main program entry point
├── main_win.c            # Windows-specific main file
├── merge.c               # Core merging functionality
├── merge_opt.c           # Optimized merging operations
├── merge_asm_32.asm     # 32-bit assembly implementation
├── merge_asm_64.asm     # 64-bit assembly implementation
├── merge_simd_32.asm    # 32-bit SIMD optimizations
├── merge_simd_64.asm    # 64-bit SIMD optimizations
├── CMakeLists.txt       # CMake build configuration
├── Makefile             # Make build rules
└── README.md
```

## 🔧 Setup and Installation

### Prerequisites

- **GCC Compiler**: For C code compilation
- **NASM**: For assembly code compilation
- **CMake**: Version 3.10 or higher
- **For 32-bit builds**: 
  ```bash
  sudo apt-get install gcc-multilib
  sudo apt-get install lib32gcc-dev
  ```

### Building the Project

1. **Clone the Repository**
   ```bash
   git clone https://github.com/MuhammadMahdiAmirpour/video_merger.git
   cd video_merger
   ```

2. **Create Build Directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure Build**
   
   For 32-bit build:
   ```bash
   cmake -DARCH_32=ON ..
   ```
   
   For 64-bit build:
   ```bash
   cmake -DARCH_64=ON ..
   ```

   Or use the interactive CMake interface:
   ```bash
   ccmake ..  # Requires cmake-curses-gui package
   ```

4. **Compile**
   ```bash
   make
   ```

### Running the Program

For 32-bit version:
```bash
./merge_32 input1_noisy.mov input2_noisy.mov output.mov
```

For 64-bit version:
```bash
./merge_64 input1_noisy.mov input2_noisy.mov output.mov
```

## 📊 Performance

The project implements optimizations at both C and Assembly levels:
- SIMD instructions for parallel processing
- Architecture-specific optimizations (32-bit and 64-bit)
- Efficient memory handling and data processing

## 👨‍💻 Author

**Muhammad Mahdi Amirpour**
- GitHub: [@MuhammadMahdiAmirpour](https://github.com/MuhammadMahdiAmirpour)

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

<div align="center">
  <sub>Built with ❤️ by Muhammad Mahdi Amirpour</sub>
</div>

<!-- Footer -->
<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=0,2,3,5,6&height=100&section=footer"/>
</div>
