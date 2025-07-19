# -MULTITHREADED-FILE-COMPRESSION-TOOL

company: CODTECH IT SOLUTIONS

NAME: CHETAN DADASO INDALKAR

*INTERN ID * : CT08DL911

DOMAIN : C++ DEVLOPMENT

DURATION: 4 WEEKS

MENTOR: NEELA SANTOSH


A high-performance file compression and decompression tool developed in C++, using multithreading to significantly speed up processing on large files. This tool is designed to demonstrate the power of concurrency in file operations using compression algorithms such as zlib.

---

## 🚀 Features

- ✅ Compress and decompress files using multithreading
- ✅ Utilizes `zlib` for fast and efficient data compression
- ✅ Supports large files by splitting them into blocks
- ✅ Boosts performance by leveraging all CPU cores
- ✅ Clean, modular, and cross-platform C++ code (tested on Windows via MSYS2/MinGW)

---

## 🧠 How It Works

### Compression
1. The input file is split into multiple blocks.
2. Each block is assigned to a separate thread.
3. Threads compress blocks in parallel using zlib.
4. All compressed blocks are written sequentially to an output `.cmp` file.

### Decompression
1. The compressed file is read and split based on metadata (e.g., block sizes).
2. Each block is decompressed in its own thread.
3. Original blocks are reassembled to reconstruct the original file.

---

## 🛠️ Requirements

- C++11 or newer
- [zlib](https://www.zlib.net/)
- CMake or g++/clang++ with threading support

#OUTPUT :- 

<img width="973" height="531" alt="Image" src="https://github.com/user-attachments/assets/a466b576-8074-419d-b1d6-3c3306b987e0" />
<img width="1019" height="562" alt="Image" src="https://github.com/user-attachments/assets/4a28da37-470a-4bd1-b244-aec7291ee889" />

## 🧪 Build Instructions

### 🔧 MSYS2 / MinGW (Windows)


# Install zlib if not present
pacman -S mingw-w64-x86_64-zlib

# Compile
g++ -std=c++11 -pthread main.cpp -lz -o compressor
