# MINI SHELL // C++20 CLI

![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Compiler](https://img.shields.io/badge/Compiler-g%2B%2B-A8B9CC?style=for-the-badge)
![Status](https://img.shields.io/badge/Build-Active%20v0.2-00FF88?style=for-the-badge)

> **Born not to be average.** A lightweight, terminal-native command shell written in modern C++20 using `std::filesystem` for direct directory navigation, filesystem manipulation, and dynamic prompt state management.

---

## 🚀 Vision & Overview

**MINI SHELL** is a low-overhead command-line interface built to practice real systems-level filesystem control and process state management in C++20 without external frameworks or legacy C hacks. 

It handles stateful execution across commands: automatically discovering the host environment's home path, validating targeted filesystem nodes, writing data to disk, and dynamically rendering the interactive shell prompt as you traverse system directories.

---

## ✨ Features

- 🏠 **Automated Environment Resolution:** Resolves user home directory dynamically via system `$HOME` environment variables with fallback verification.
- 📂 **Directory Navigation (`cd`):** Navigates file trees with full pre-execution checks (`filesystem::exists` and `filesystem::is_directory`).
- 🔄 **Home Reset (`set-home`):** Instantly teleports process scope back to initial `$HOME` directory and syncs shell prompt.
- 📝 **File Generation & I/O (`open`):** Spawns output file streams (`std::ofstream`) and writes user content directly to disk.
- 🧹 **Screen Control (`clear`):** Flushes terminal viewport via native system process calls.
- 🛡️ **Robust Parsing:** Reads and breaks command lines using string streams (`std::istringstream`), preventing empty inputs from crashing execution.

---

## 🏗️ Architecture & Call Graph

```text
                        [ Program Entry: main() ]
                                   │
                    ┌──────────────┴──────────────┐
                    │  getHome()                  │
                    │  ├── Reads getenv("HOME")   │
                    │  └── Validates home path    │
                    └──────────────┬──────────────┘
                                   │
                 ┌─────────────────┴─────────────────┐
                 ▼                                   ▼
      [ Dynamic Shell Loop ]                [ std::cin Line Parsing ]
                 │                                   │
                 ├───────────────────────────────────┘
                 │
                 ├── "cd <path>"   ──▶ open_folder(arg, home)
                 │                        ├── fs::exists() validation
                 │                        ├── fs::is_directory() check
                 │                        └── fs::current_path(target)
                 │
                 ├── "open <file>" ──▶ write_file(filename)
                 │                        └── std::ofstream creation
                 │
                 ├── "set-home"    ──▶ fs::current_path(home)
                 │                        └── Reset dynamic prompt
                 │
                 ├── "clear"       ──▶ clearTerm()
                 │                        └── system("clear")
                 │
                 └── Unknown Cmd   ──▶ Console warning & continue
```

---

## 🧩 Key Functions Breakdown

| Function Signature | Description |
|---|---|
| `filesystem::path getHome()` | Queries system environment for `$HOME`, confirms validity, or falls back to execution path. |
| `string open_folder(const string &arg, const filesystem::path &home)` | Checks target availability, changes current working directory, and returns updated dynamic prompt string. |
| `void write_file(string &filename)` | Initializes standard output file stream (`std::ofstream`) for creating/overwriting files. |
| `void clearTerm()` | Invokes terminal system clear procedure to reset buffer view. |

---

## ⚙️ Compilation & Running

Requires a C++20 compliant compiler (`g++ 10+` or `clang 11+`).

### Build
```bash
g++ -std=c++20 -Wall -Wextra main.cpp -o mini_shell
```

### Launch
```bash
./mini_shell
```

---

## 👨‍💻 Author

**ScuizzyBytes (Миша)**  
*Systems-level development, C++20 engineering, and Linux kernel fundamentals.*
