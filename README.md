# C++ 7-Segment Display Library

A lightweight, hardware-accelerated 7-segment digital clock and display emulator written in C++20 using the **[raylib](https://www.raylib.com/)** graphics framework.

## 🛠 Prerequisites & Dependencies

Before compiling, you must install `raylib` along with its required system windowing and graphics libraries (`X11`, `OpenGL`, etc.).

### 1. Install System Dependencies
Choose the command matching your Linux distribution package manager:

* **Ubuntu / Debian / Linux Mint:**
  ```bash
  sudo apt update
  sudo apt install build-essential git mesa-common-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
  ```

* **Arch Linux / Manjaro:**
  ```bash
  sudo pacman -Syu base-devel git mesa libx11 libxrandr libxi
  ```

### 2. Install Raylib
* **Ubuntu/Debian (Via PPA):**
  ```bash
  sudo add-apt-repository ppa:texus/raylib
  sudo apt install libraylib6-dev
  ```
* **Arch Linux:**
  ```bash
  sudo pacman -S raylib
  ```
* **From Source (If not available in your package manager):**
  ```bash
  git clone https://github.com/raysan5/raylib.git
  cd raylib/src/
  make PLATFORM=PLATFORM_DESKTOP
  sudo make install
  ```

---

## 🚀 Compilation & Build Guide

### Option A: Compiling with Clang++ (Your Default Command)
Ensure you have Clang installed (`sudo apt install clang`). Run your specific compile instruction:

```bash
clang++ -Wall -std=c++20 -stdlib=libc++ DigitialClock.cpp -o clock -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Option B: Compiling with GCC (g++)
If you prefer to use the standard GNU compiler (`sudo apt install g++`), use this optimized alternative command:

```bash
g++ -Wall -std=c++20 DigitialClock.cpp -o clock -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

## 🏃 Running the Application

Once successfully compiled, run the generated binary directly from your terminal shell:

```bash
./clock
```
