# Console Chess Game in C++

A fully functional console-based Chess game developed in C++ using Object-Oriented Programming. This project allows two players to play Chess in the terminal with proper turn management, legal move validation, check/checkmate detection, stalemate detection, and save/load functionality.

---

## Project Overview

Console Chess Game in C++ is a complete two-player Chess simulator that runs in the command-line interface. It was developed as a learning project to demonstrate Object-Oriented Programming concepts, clean code structure, file handling, and game logic implementation.

The game validates moves according to Chess rules and prevents players from making illegal moves, including moves that would leave their own king in check.

---
## Project Structure

Chess-Game/
├── main.cpp              # Complete source code
├── chess_save.txt        # Auto-generated save file
├── README.md             # Project documentation
└── Project Report.pdf    # Optional project report

---

## Features

- Complete movement logic for all Chess pieces
- Pawn movement with first double-step move
- Diagonal pawn captures
- Check detection
- Checkmate detection
- Stalemate detection
- Legal move validation
- Prevents moves that leave the king in check
- Turn-based gameplay
- Save and load game functionality
- ASCII-based Chess board display
- Algebraic notation input
- Input validation with helpful error messages
- Simple and clean console interface

---

## Technologies Used

- C++
- Object-Oriented Programming
- Standard Template Library
- File Handling
- Console Input/Output

---

## How to Play

Players enter moves using algebraic board coordinates.

Example moves:

```text
e2 e4
g1 f3
e7 e5
b8 c6
