# Snake Game in C++

This is a classic Snake game implemented in C++ using object-oriented programming techniques. The game runs in a Windows console environment and leverages the Win32 API for console handling. It demonstrates code organization by separating functionality into header and source files using classes and STL containers.

## Features

- **Object-Oriented Design:** Organized into classes such as `Snake`, `Food`, and `SnakeGame` for clear separation of responsibilities.
- **Modular Structure:** Code is split into multiple header (`.h`) and source (`.cpp`) files for easier maintenance and scalability.
- **Console Graphics:** Uses Windows console functions (via `<windows.h>`) to render the game board and elements.
- **Classic Gameplay:** Control the snake with arrow keys, eat food to grow, and avoid collisions with walls or the snake's own body.
- **Dynamic Speed Increase:** The game speed increases as you collect more food, adding to the challenge.
- **Score Tracking:** Displays current score, last score, and best score on the screen.

## Requirements

- **Operating System:** Windows (the code uses Windows-specific APIs).
- **Compiler:** A C++ compiler supporting C++11 or later (e.g., Visual Studio, MinGW).
- **Dependencies:** No external dependencies; uses standard libraries and the Windows API.

## Build and Run Instructions

1. **Clone the Repository:**
   ```bash
   git clone <repository_url>
   cd <repository_directory>

2. **Build the Project:**
   ```bash
   Using Visual Studio: Open the solution/project file and build the project. Must be set to Debug Properties -> C/C++ -> SDL checks -> No (/sdl-).
   Using g++ (MinGW): g++ main.cpp SnakeGame.cpp Food.cpp Snake.cpp -o SnakeGame -std=c++11 -static-libgcc -static-libstdc++
