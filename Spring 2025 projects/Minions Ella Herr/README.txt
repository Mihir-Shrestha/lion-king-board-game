--------------------------
HOW TO RUN AND COMPILE
--------------------------
Compile: g++ -Wall -Werror -Wpedantic -Wsign-compare -o myName.exe -std=c++17 Game.cpp Player.cpp Board.cpp GameDriver.cpp
Run: ./myName.exe
--------------------------
DEPENDENCIES
--------------------------
Player.h, Tile.h, Board.h, Game.h, advisors.txt, characters.txt, random_events.txt, riddles.txt
Must be in the same directory as the cpp files in order to compile.
--------------------------
CSCI 1300 Spring 2025 Final Project
Author: Ella Herr
Recitation: 205 - Mihir Shrestha
Date: April 30, 2025
--------------------------
ABOUT THIS PROJECT
--------------------------
This project is an interactive board game designed after the Game of Life.
It also takes inspiration from the Despicable Me movie series.
The user plays as a character choosing between two paths and trying to reach the end of the board. 
As the player moves across the board, they encounter special tiles, challenges, and point opportunities.