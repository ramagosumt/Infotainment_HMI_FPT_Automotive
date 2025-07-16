# WeatherApp_MVVM — Automotive HMI, AR HUD & Custom Qt Editor Prototype

This project is a personal prototype simulating an **automotive HMI system** with **AR HUD features** designed for windshield projection, combined with a fully custom **ImGUI-inspired editor** built entirely with Qt. The project structure and workflow are modeled after real-world processes from my collaboration with **FPT Automotive**.

---

## ✨ Project Purpose

- Practice development workflows for **automotive HUDs**, **AR interfaces**, and **in-vehicle HMI design**  
- Prototype interactive automotive UI elements including weather, media, and video streaming  
- Gain experience producing professional technical documentation:  
  - **SRS** (Software Requirements Specification)  
  - **SAD** (Software Architecture Document)  
- Simulate customer-facing development pipelines used in the automotive industry  

---

## 🛠️ Technologies Used

- **Qt 6 & Qt Quick (QML)** — Modern, cross-platform UI  
- **C++** — ViewModel, system logic, and state management  
- **SCXML & Qt State Machines** — Reliable state control for system logic  
- **Qt Resource System (qrc)** — Embedded assets and fonts  
- **MVVM Pattern** — Clean separation of logic, data, and UI  
- **Custom ImGUI-style Editor** — Built entirely with Qt and QML for real-time HUD adjustments  
- **FFmpeg Integration** — Video decoding for AR HUD streaming simulation  

---

## 📦 Key Features

### 🔧 Core System Features

- Self-contained, real-time HUD **editor** for UI adjustments during runtime  
- AR-inspired HUD visuals designed for potential windshield projection  
- Fully packaged binary with all assets embedded via Qt's resource system  

---

### ☁️ Weather System

- Displays current **province**, **temperature**, **weather condition**, and **windspeed**  
- Supports both **current** and **destination** locations  
- Dynamic state handling with **SCXML-powered system**  
- Clean MVVM structure with fully exposed C++ logic to QML  
- Fully interactive via editor with real-time weather adjustments  

---

### 🎵 Media System

- Simulated **media player** panel showing:  
  - **Source name** (e.g., USB, Bluetooth)  
  - **Song title**  
  - **Artist details**  
- Editor support for live modification of media information during development  

---

### 📹 Streaming & AR HUD Simulation

- Integrated **FFmpeg-based video decoding pipeline**  
- Simulates real-time video streaming for AR HUD visualization  
- MVVM structure separating logic, state, and UI  
- Foundation for testing AR windshield projections or camera feeds  
- Streaming logic entirely implemented in C++ and exposed to QML  

---

## 📁 Folder Structure (Simplified)

```
├── Headers/           # C++ header files
├── Sources/           # C++ source files
│   ├── QML/           # QML files for UI and editor
├── Plugins/           # Third-party libraries (e.g., FFmpeg)
├── Resources/         # Embedded images, fonts, and assets
├── CMakeLists.txt     # Build configuration
└── README.md
```

---

## 🔌 FFmpeg Setup (Required for Streaming)

This project uses FFmpeg for video decoding. Due to size and licensing, FFmpeg binaries are not committed directly. Please follow the steps below to enable streaming support:

### 📥 Step 1: Download the FFmpeg Plugin Folder

Download from this Google Drive folder:  
➡️ [Download `Plugins/ffmpeg/`](https://drive.google.com/drive/folders/1A8O1zK8L6aH4mVjb2OzUNdu9SA5hp5Dg?usp=drive_link)

It contains all required `.dll` and `.dll.a` files:
- `avcodec-61.dll`, `avformat-61.dll`, `avutil-59.dll`, etc.
- `libavcodec.dll.a`, `libavformat.dll.a`, etc.

---

### 📁 Step 2: Move It Into Your Project

After downloading, place the folder like this:

```
<cloned_repo>/
├── Plugins/
│   └── ffmpeg/
│       ├── bin/
│       │   ├── avcodec-61.dll
│       │   └── ...
│       └── lib/
│           ├── libavcodec.dll.a
│           └── ...
```

---

### ⚡ Optional: PowerShell Automation (Windows)

If you want to automate the move:

```powershell
# Run this in the root of your project after downloading FFmpeg
Move-Item -Path "C:\Path\To\Downloaded\ffmpeg" -Destination ".\Plugins\ffmpeg"
```

---

## 🚧 Project Notes

This is a **technical learning prototype**. Focus is on system structure, UI logic, and workflow simulation — **not** polished visuals or complete automotive feature sets.  

---

## 😎 Why a Custom ImGUI-style Editor?

To retain full control over HUD configuration without third-party dependencies. The editor is built entirely with **Qt Quick**, mimicking the lightweight, immediate-style behavior of **ImGUI**, enabling real-time HUD tweaks during development.  

---

## 🙏 Acknowledgements

Developed independently as part of my initiative to deepen expertise in automotive software, AR HUD technologies, and customer-aligned development, inspired by my work at **FPT Automotive**.
