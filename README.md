# GAT150 – Introduction to Game Programming

**Course**: GAT150 – Introduction to Game Programming (Summer 2025, Sprint Two)  
**Repository**: Builds upon the engine completed in CSC196 (C++ Programming II).

---

## 📖 Description

GAT150 is both a lightweight game engine and a simple platformer demo, created as part of the **GAT150 course**.  

It demonstrates key game programming concepts such as rendering, input handling, physics, and entity management. The engine is built in **C++** with support from modern libraries like **SDL3** and **Box2D**, making it a strong foundation for further projects.

---

## ✨ Features

### Core Features
- **Engine Architecture**
  - Modular design for rendering, input, and physics
  - Scene and resource management
- **Rendering**
  - 2D sprite rendering using **SDL3** and **SDL3_image**
- **Physics**
  - Integrated **Box2D** physics engine for collisions and platforming mechanics
- **Input Handling**
  - Keyboard support:
    - `A` → Move Left  
    - `D` → Move Right  
    - `SPACE` → Jump  

### Planned / Extra Features
- Audio support via **FMOD** (currently integrated but not yet used)
- Data-driven configuration with **rapidjson**
- Future sound effects and background music
- Potential UI overlays and particle effects

---

## 🖼️ Screenshots

![Gameplay Screenshot](<img width="1997" height="1598" alt="Screenshot 2025-09-04 221932" src="https://github.com/user-attachments/assets/dff36ab8-1439-4801-aa4e-65f8d1112e3d" />)  
*Player (green block) navigating floating platforms with physics-based jumping and movement.*

---

## 🎥 Gameplay Video

<video src="Screen%20Recording%202025-09-04%20222751.mp4" controls width="720"></video>  

*(If GitHub does not preview the video in-browser, it can still be downloaded and viewed locally.)*

---

## ⚙️ Build & Run Instructions

### Prerequisites
- **C++17 or newer compiler** (MSVC, GCC, or Clang)
- **CMake 3.x+**
- **External libraries**:
  - [SDL3](https://github.com/libsdl-org/SDL)  
  - [SDL3_image](https://github.com/libsdl-org/SDL_image)  
  - [Box2D](https://github.com/erincatto/box2d)  
  - [FMOD](https://www.fmod.com/) (optional, not yet active)  
  - [rapidjson](https://github.com/Tencent/rapidjson)  

### Building
```bash
git clone https://github.com/TwistedFury/GAT150.git
cd GAT150
mkdir build && cd build
cmake ..
cmake --build .
```

# Running
## on Linux / macOS
```bash
./GAT150
```

## on Windows
```bash
GAT150.exe
```

# Credit
Created by Cody Owens for the GAT150 – Introduction to Game Programming course (Summer 2025).
For questions or feedback, please open an issue on [GitHub](https://github.com/TwistedFury/GAT150)
