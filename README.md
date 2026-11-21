# MINI SHELL // C++20 CLI

![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Compiler](https://img.shields.io/badge/Compiler-g%2B%2B-A8B9CC?style=for-the-badge)
![Status](https://img.shields.io/badge/Build-Active%20v0.1-00FF88?style=for-the-badge)

> **Born not to be average.** A lightweight, terminal-native command shell written in modern C++20 using `std::filesystem` for direct directory navigation and dynamic prompt updates.

---

## The Vision

**MINI SHELL** is a fast, no-bloat command-line interface built to practice real systems-level filesystem control in C++20 without heavy frameworks or legacy C hacks. It reads commands from `stdin`, parses arguments with `std::istringstream`, validates target paths on disk, and updates the live prompt as you move across directories.

---

## Architecture & Functions

The entire shell runs through **2 functions** backed by `<iostream>`, `<sstream>`, `<string>`, and `<filesystem>`:

```text
[stdin / getline]
       │
       ▼
    main() ──▶ std::istringstream (parses cmd & arg)
       │
       ├── "cd <path>"  ──▶ open_folder(arg)
       │                        ├── fs::exists()
       │                        ├── fs::is_directory()
       │                        └── fs::current_path(target)
       │
       ├── "set-home"   ──▶ resets prompt to "MINI SHELL ~! "
       └── other        ──▶ prints unknown command notice
