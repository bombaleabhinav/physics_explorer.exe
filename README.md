# 🔬 Physics Concept Explorer - Visual Simulator

> **FOP Mini Project** | C Programming | Multiple Modules | **No Headers Architecture**

---

## 📋 Project Overview

A modular Physics simulation system split into separate functional components. The project emphasizes visual feedback through ASCII animations/graphs and clear UI separation.

---

## 🏗️ Project Structure

This project follows a "No Headers" approach where each module is a standalone `.c` file, coordinated by `main.c`.

| File | Module | Description |
|---|--------|--------------|
| **`main.c`** | Controller | Unified menu, animations, and coordination |
| **`projectile.c`** | Projectile Motion | Launch simulators with trajectory graphs |
| **`ohms.c`** | Resistor Network | Series/Parallel equivalent resistance simulator |
| **`shm.c`** | SHM Visualizer | Sine wave generator for harmonic motion |
| **`wave.c`** | Interference | Wave superposition and interference patterns |
| **`refraction.c`** | Optics | Snell's Law and Total Internal Reflection simulator |

---

## ✨ Features & Improvements

1.  **Modular Design**: Every physics concept has its own `.c` file.
2.  **No Header Files**: Prototypes are used directly in `main.c` for linking.
3.  **UI/UX**:
    *   **ANSI Colors**: Vivid Cyan, Green, Yellow, and Red highlights.
    *   **Animations**: Loading dots and clear transitions.
    *   **ASCII Art**: Trajectory graphs, step waves, and circuit diagrams.
4.  **Optimized Ohm's Law**: Focused specifically on Series and Parallel resistor networks as requested.

---

## 🚀 How to Compile & Run

### Using GCC:
```bash
gcc main.c projectile.c ohms.c shm.c wave.c refraction.c -o physics_explorer.exe -lm
./physics_explorer.exe
```

---

## 📊 Summary of Modules

*   **Projectile**: Calculates range, height, and time with a 2D plot.
*   **Resistors**: Handles $N$ resistors in series or parallel configurations.
*   **SHM**: Displays a scrolling sine wave based on user-defined amplitude/frequency.
*   **Waves**: Shows constructive/destructive interference between two user-defined waves.
*   **Optics**: Calculates refraction angles and detects total internal reflection cases.
