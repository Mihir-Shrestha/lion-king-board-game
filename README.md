# The Circle of Life - A Lion King Themed Board Game 🦁

A C++ console-based board game inspired by Disney's The Lion King, where players navigate through the Pride Lands, face challenges, answer riddles, and compete to become the ultimate lion leader.

## 🎮 Game Overview

In "The Circle of Life," players take on the roles of various Lion King characters and embark on a journey through two different paths:
- **Cub Training Path**: A safer route with training benefits but reduced pride points
- **Straight to the Pride Lands Path**: A more challenging direct route with higher rewards

The goal is to reach the end of the board while accumulating the most Pride Points to win the game.

## 🚀 Features

### Core Gameplay
- **2-4 Player Support**: Multiplayer turn-based gameplay
- **Character Selection**: Choose from various Lion King characters with unique stats
- **Dual Path System**: Two different gameplay experiences
- **Advisor System**: Choose magical advisors with special abilities
- **Colorful Board Display**: Visual representation using ANSI color codes

### Game Mechanics
- **Dice Rolling**: Random movement (1-6 spaces)
- **Tile Effects**: Different colored tiles with unique effects:
  - 🟢 **Green Tiles**: Random events (positive/negative)
  - 🔵 **Blue Tiles**: Peaceful oasis (+200 stats, extra turn)
  - 🩷 **Pink Tiles**: Enrichment land (+300 stats, advisor selection)
  - 🔴 **Red Tiles**: Graveyard (-100 stats, move back 10 spaces)
  - 🤎 **Brown Tiles**: Hyena encounter (-100 stamina, return to last position)
  - 🟣 **Purple Tiles**: Riddle challenges (±500 wisdom)
  - 🟠 **Orange Tiles**: Pride Rock (finish line)
  - ⚪ **Grey Tiles**: Starting position

### Character Progression
- **Stats System**: Stamina, Strength, Wisdom, and Pride Points
- **Advisor Protection**: Some advisors protect against specific negative events
- **Leadership Calculation**: End-game bonus based on accumulated stats

## 📁 Project Structure

```
lion-king-board-game/
├── Game.cpp          # Main game loop and logic
├── Game.h            # Game class header
├── Board.cpp         # Board management and tile effects
├── Board.h           # Board class header
├── Player.cpp        # Player functionality
├── Player.h          # Player class header
├── InputData.cpp     # File I/O operations
├── InputData.h       # Data structures and file reading
└── Tile.h            # Tile structure definition
├── input_files/
│   ├── characters.txt    # Available characters and stats
│   ├── random_events.txt # Random events for green tiles
│   └── riddles.txt       # Riddles for purple tiles
├── game_results.txt      # Generated game results
└── README.md
```

## 🛠️ Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- Standard C++11 or later
- Terminal/Console with ANSI color support (for best visual experience)

## 🔧 Compilation and Setup

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/lion-king-board-game.git
cd lion-king-board-game
```

### 2. Compile the Game
```bash
g++ -std=c++11 -o game Game.cpp Board.cpp Player.cpp InputData.cpp
```

### 3. Prepare Input Files
Ensure the following files exist in an `input_files/` directory:
- `characters.txt`: Character data
- `random_events.txt`: Random events
- `riddles.txt`: Riddles for purple tiles

### 4. Run the Game
```bash
./game
```

## 🎯 How to Play

1. **Game Setup**:
   - Select number of players (2-4)
   - Each player chooses a character and path
   - Cub Training path players select an advisor

2. **Gameplay**:
   - Players take turns in order
   - On your turn, choose from menu options:
     - Check Player Progress
     - Review Character
     - Check Position
     - Review Advisor
     - Move Forward (roll dice and move)

3. **Tile Effects**:
   - Land on different colored tiles for various effects
   - Some tiles provide bonuses, others present challenges
   - Purple tiles require answering riddles correctly

4. **Winning**:
   - Race to reach the orange tile (Pride Rock)
   - Player with the most Pride Points wins
   - Leadership bonus calculated at game end

## 🏗️ Technical Implementation

### Class Architecture
- **Game**: Main game controller and user interface
- **Board**: Manages game board, tile generation, and player movement
- **Player**: Handles player data, stats, and character information
- **InputData**: File I/O operations for game content

### Key Features
- **Dynamic Board Generation**: Randomized tile placement with guaranteed distributions
- **File-Based Content**: Extensible characters, events, and riddles
- **Robust Input Validation**: Handles invalid user inputs gracefully
- **Game State Persistence**: Results saved to file after completion

## 🎨 Visual Features

The game uses ANSI escape codes to create a colorful console experience:
- Colored tiles represent different game effects
- Player positions shown on board
- Multiple players on same tile displayed clearly

## 📊 Game Balance

### Path Differences
- **Cub Training**: 30 green tiles, advisor benefits, -5000 initial pride points
- **Pride Lands**: 20 green tiles, no advisor, +5000 initial pride points

### Stat Management
- Minimum stat values enforced (100 minimum)
- Balanced risk/reward for different tile types
- Strategic advisor selection impacts gameplay

## 🤝 Contributing

This project was developed as part of CSCI1300. Feel free to fork and enhance:
- Add new characters or advisors
- Create additional tile effects
- Implement new game modes
- Improve the user interface

## 📝 Development Notes

- Random seed initialization ensures varied gameplay
- Error handling for file operations and user input
- Memory management with proper vector usage
- Modular design for easy maintenance and extension

## 🎓 Academic Context

This project demonstrates:
- Object-oriented programming principles
- File I/O operations
- Game loop implementation
- Data structure usage
- User input validation
- Random number generation
- Console-based user interface design

## ⚠️ Academic Integrity Notice

**FOR STUDENTS: DO NOT COPY THIS CODE**

This repository contains my completed coursework for CSCI1300. It is shared publicly as part of my portfolio to demonstrate programming skills to potential employers.

### If you are a current student:
- ✅ You may view this code to understand programming concepts
- ✅ You may learn from the implementation approach
- ❌ You may NOT copy, modify, or submit any part of this code
- ❌ You may NOT use this as a starting point for your assignment

### Academic Consequences:
Using this code for your coursework constitutes plagiarism and will result in:
- Automatic course failure
- Academic disciplinary action
- Permanent academic record notation

**Your professors can and will detect copied code.** Modern plagiarism detection tools are sophisticated and will flag similarities.

### For Employers/Recruiters:
This project demonstrates my ability to implement object-oriented programming concepts, file I/O operations, game logic, and user interface design in C++.
---

*Hakuna Matata! Enjoy the game and may the best lion win!* 🦁👑