<!-- Header -->
<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=0,2,3,5,6&height=180&section=header&text=Video%20Merger&fontSize=36&fontAlignY=35&animation=twinkling&fontColor=FFFFFF"/>
</div>

# Video Merger

This repository contains the final project of my assembly course at university. The project, called Video Merger, is implemented using C, Assembly, Makefile, and CMake. It is designed to merge two video files on Linux systems.

## 🛠️ Technologies Used

- **C**
- **Assembly**
- **Makefile**
- **CMake**

## 📚 Project Description

The Video Merger project is designed to merge two video files into a single output file. This project demonstrates the use of low-level programming with C and Assembly, as well as build automation using Makefile and CMake. Currently, it only supports Linux operating systems.

## 🎯 Objective

The main objective of this project is to merge two video files efficiently and demonstrate the application of assembly language in a practical project.

## 🚀 Features

- **Efficient Video Merging**: Merge two video files into a single output file.
- **Low-Level Programming**: Utilize both C and Assembly for performance optimization.
- **Build Automation**: Use Makefile and CMake for easy project compilation and management.
- **Linux Support**: Specifically designed to work on Linux operating systems.

## 🏗️ Project Structure

```
video_merger/
├── src/
│   ├── main.c
│   ├── video_merger.asm
│   └── utils.c
├── include/
│   ├── video_merger.h
│   └── utils.h
├── build/
├── Makefile
├── CMakeLists.txt
└── README.md
```

## 🔧 Setup and Installation

### Prerequisites

- **GCC Compiler**: Ensure GCC is installed on your system.
- **NASM Assembler**: Install NASM for assembly code compilation.
- **CMake**: Ensure CMake is installed for building the project.

### Building the Project

1. **Clone the Repository**
   ```bash
   git clone https://github.com/MuhammadMahdiAmirpour/video_merger.git
   cd video_merger
   ```

2. **Using Makefile**
   ```bash
   make
   ```

3. **Using CMake**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

### Running the Program

1. **Execute the Binary**
   ```bash
   ./video_merger <input_video1> <input_video2> <output_video>
   ```

## 📊 Performance

The project leverages both C and Assembly to achieve efficient video merging. The use of low-level programming ensures optimal performance and resource utilization.

## 🙌 Contributions

Contributions to this project are welcome. Feel free to open issues and submit pull requests.

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## 👨‍💻 Author

**Muhammad Mahdi Amirpour**
- GitHub: [@MuhammadMahdiAmirpour](https://github.com/MuhammadMahdiAmirpour)

---

<div align="center">
  <sub>Built with ❤️ by Muhammad Mahdi Amirpour</sub>
</div>

<!-- Footer -->
<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=0,2,3,5,6&height=100&section=footer"/>
</div>
