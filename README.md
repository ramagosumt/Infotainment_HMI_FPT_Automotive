
# WeatherApp_MVVM — Automotive HMI, AR HUD & Custom Qt Editor Prototype

This project is a personal practice prototype simulating an **automotive HMI system** with **AR HUD features** on a windshield, combined with a custom-built **ImGUI-like editor** entirely made with Qt. The project structure and workflow are designed to mirror real-world development processes from my time collaborating with **FPT Automotive**.

---

## ✨ Project Purpose

- Practice technical workflows for **automotive HUD, AR interfaces**, and **in-vehicle HMI design**.
- Gain experience producing customer-facing technical documentation:
  - **SRS** (Software Requirements Specification)
  - **SAD** (Software Architecture Document)
- Prototype interactive automotive UIs using:
  - Weather and media information displays
  - AR-inspired HUD visualizations
  - A custom Qt-based editor, inspired by **ImGUI**, for real-time HUD adjustments

---

## 🛠️ Technologies Used

- **Qt 6 & Qt Quick (QML)** for modern, cross-platform UI
- **C++** for ViewModel, state management, and logic
- **SCXML & State Machines** for system state handling
- **Qt Resource System (qrc)** for embedding images, fonts, and assets
- **MVVM Pattern** for clean separation of logic and UI
- **Custom ImGUI-style Editor** built from scratch using pure Qt and QML

---

## 📦 Features

- Weather panel showing province, temperature, condition, windspeed
- Media player interface with source, song, and artist details
- Self-contained HUD editor window for real-time UI adjustments, inspired by ImGUI
- AR-inspired HUD visual elements designed for potential future windshield projections
- Fully self-contained binary with all assets embedded via Qt's resource system

---

## 📁 Folder Structure (Simplified)

```
├── Headers/       # C++ header files
├── Sources/       # C++ source files
│   ├── QML/       # QML files for UI and editor
├── Resources/     # Embedded images, fonts, and assets
├── CMakeLists.txt # Build configuration
└── README.md
```

---

## 🚧 Notes

This is a technical learning project. Focus is on system structure, UI logic, and workflow simulation — not polished visuals or full automotive feature completeness.

---

## 📖 Acknowledgements

Developed independently as part of my effort to better understand automotive software development, AR HUD technology, and customer collaboration processes, inspired by my work with **FPT Automotive**.

---

## 😎 Bonus: Why ImGUI-style Editor?

I wanted full control over HUD configuration without relying on external libraries. The editor window is built entirely with Qt Quick and mimics the lightweight, immediate-style behavior of **ImGUI**, allowing real-time tweaks of system visuals during development.
