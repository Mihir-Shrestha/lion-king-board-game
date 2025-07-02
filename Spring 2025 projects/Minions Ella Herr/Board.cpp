#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()
#include "Player.h"

using namespace std;

#include "Board.h"
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m" /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

void Board::initializeBoard(){
    // Seed random number generator in your main function once
    void srand(unsigned seed);
    srand(time(0));
    for (int i = 0; i < 2; i++){
        initializeTiles(i); // This ensures each lane has a unique tile distribution
    }
}

void Board::initializeTiles(int track_index){
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for(int i = 0; i < total_tiles; i++){
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        }
        else if(i == 0){
            // Set the first tile as Grey
            temp.color = 'Y';
        }
        else if(track_index == 0){
            if((green_count < 21) && ((rand() % (total_tiles - i)) < (21 - green_count))){ //Ask about 21 vs 20 for green tiles????
                temp.color = 'G';
                green_count++;
            }
            else if((0 < i)&&(i < 26)){
                int color_choice = (rand() % 100);

                if((0 <= color_choice)&&(color_choice < 25)){
                    temp.color = 'R'; // Red
                }
                else if((25 <= color_choice)&&(color_choice < 50)){
                    temp.color = 'N'; // Brown
                }
                else if((50 <= color_choice)&&(color_choice < 70)){
                    temp.color = 'P'; // Pink
                }
                else if((70 <= color_choice)&&(color_choice < 75)){
                    temp.color = 'B'; // Blue
                }
                else if((75 <= color_choice)&&(color_choice < 100)){
                    temp.color = 'U'; // Purple
                }
            }
            else if((26 <= i)&&(i < 52)){
                int color_choice = (rand() % 100);

                if((0 <= color_choice)&&(color_choice < 15)){
                    temp.color = 'R'; // Red
                }
                else if((15 <= color_choice)&&(color_choice < 30)){
                    temp.color = 'N'; // Brown
                }
                else if((30 <= color_choice)&&(color_choice < 50)){
                    temp.color = 'P'; // Pink
                }
                else if((50 <= color_choice)&&(color_choice < 75)){
                    temp.color = 'B'; // Blue
                }
                else if((75 <= color_choice)&&(color_choice < 100)){
                    temp.color = 'U'; // Purple
                }
            }
        }
        else if(track_index == 1){
            if((green_count < 31) && ((rand() % (total_tiles - i)) < (31 - green_count))){ //Ask about 31 vs 30 for green tiles????
                temp.color = 'G';
                green_count++;
            }
            else if((0 < i)&&(i < 26)){
                int color_choice = (rand() % 100);

                if((0 <= color_choice)&&(color_choice < 20)){
                    temp.color = 'R'; // Red
                }
                else if((20 <= color_choice)&&(color_choice < 40)){
                    temp.color = 'N'; // Brown
                }
                else if((40 <= color_choice)&&(color_choice < 55)){
                    temp.color = 'P'; // Pink
                }
                else if((55 <= color_choice)&&(color_choice < 80)){
                    temp.color = 'B'; // Blue
                }
                else if((80 <= color_choice)&&(color_choice < 100)){
                    temp.color = 'U'; // Purple
                }
            }
            else if((26 <= i)&&(i < 52)){
                int color_choice = (rand() % 100);

                if((0 <= color_choice)&&(color_choice < 20)){
                    temp.color = 'R'; // Red
                }
                else if((20 <= color_choice)&&(color_choice < 40)){
                    temp.color = 'N'; // Brown
                }
                else if((40 <= color_choice)&&(color_choice < 55)){
                    temp.color = 'P'; // Pink
                }
                else if((55 <= color_choice)&&(color_choice < 70)){
                    temp.color = 'B'; // Blue
                }
                else if((70 <= color_choice)&&(color_choice < 100)){
                    temp.color = 'U'; // Purple
                }
            }
        }

    // Assign the tile to the board for the specified lane
    _tiles[track_index][i] = temp;
    }
}


Board::Board()
{
    _player_count = 1;
    // Initialize player position
    _player_position[0] = 0;
    // Initialize tiles
    initializeTiles(0);
}

Board::Board(int player_count){
    if (player_count > _MAX_PLAYERS){
        _player_count = _MAX_PLAYERS;
    }
    else{
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count; i++){
        _player_position[i] = 0;
    }

    // Initialize tiles
    initializeBoard();
}


bool Board::isPlayerOnTile(int pos, int track_index, Player player){ // player_index here is actual player
    if ((player.getPosition() == pos)&&(player.getPath() == track_index)){
        return true;
    }
    return false;
}


void Board::displayTile(int pos, int track_index, Player player1, Player player2){ // player_index here is track number
    // string space = " ";
    string color = "";
    
    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>
    // Determine color to display
    if (_tiles[track_index][pos].color == 'R'){
        color = RED;
    }
    else if (_tiles[track_index][pos].color == 'G'){
        color = GREEN;
    }
    else if (_tiles[track_index][pos].color == 'B'){
        color = BLUE;
    }
    else if (_tiles[track_index][pos].color == 'U'){
        color = PURPLE;
    }
    else if (_tiles[track_index][pos].color == 'N'){
        color = BROWN;
    }
    else if (_tiles[track_index][pos].color == 'P'){
        color = PINK;
    }
    else if (_tiles[track_index][pos].color == 'O'){
        color = ORANGE;
    }
    else if (_tiles[track_index][pos].color == 'Y'){
        color = GREY;
    }

    if (isPlayerOnTile(pos, track_index, player1)&&(isPlayerOnTile(pos, track_index, player2))){
        cout << color << "|1+2|" << RESET; // This is where players are on same tile
    }
    else if(isPlayerOnTile(pos, track_index, player1)){
        cout << color << "|1|" << RESET; 
    }
    else if(isPlayerOnTile(pos, track_index, player2)){
        cout << color << "|2|" << RESET; 
    }
    else{
    cout << color << "| |" << RESET;
    }
}


void Board::displayTrack(int track_index, Player player1, Player player2){
    for (int i = 0; i < _BOARD_SIZE; i++){
        displayTile(i, track_index, player1, player2);
    }
    cout << endl;
}


void Board::displayBoard(int track_index, Player player1, Player player2){
    for (int i = 0; i < 2; i++){
        displayTrack(i, player1, player2);

        if (i == 0) {
            cout << endl; // Add an extra line between the two lanes
        }
    }

}

bool Board::movePlayer(int player_index){ // actually index of player here
// Increment player position
    int spinner = (rand() % 6) + 1;

    _player_position[player_index] = _player_position[player_index] + spinner; 
    cout << "You spun a " << spinner << "! You've moved " << spinner << " spaces!" << endl;
    if (_player_position[player_index] == _BOARD_SIZE - 1){
        // Player reached last tile
        return true;
    }
    return false;
    // Code smth with if(movePlayer == true){ stop }!!!
}

int Board::getPlayerPosition(int player_index) const{ // This simply returns the tile number the player is on
    if (player_index >= 0 && player_index <= _player_count){
        return _player_position[player_index];
    }
    return -1;
}

void Board::setPlayerPosition(int player_index, int pos){
    if(pos < 0){
        pos = 0;
        _player_position[player_index] = pos;
    }
    else if(pos > 51){
        pos = 51;
        _player_position[player_index] = pos;
    }
    else if (player_index >= 0 && player_index <= _player_count){
        _player_position[player_index] = pos;
    }
}

char Board::getColor(int track_index, int pos){ // Soley for whatTileDo() in Game.cpp to see what color tile is so we can do what that tile does
    char color;
    if (_tiles[track_index][pos].color == 'R'){
        color = 'R';
    }
    else if (_tiles[track_index][pos].color == 'G'){
        color = 'G';
    }
    else if (_tiles[track_index][pos].color == 'B'){
        color = 'B';
    }
    else if (_tiles[track_index][pos].color == 'U'){
        color = 'U';
    }
    else if (_tiles[track_index][pos].color == 'N'){
        color = 'N';
    }
    else if (_tiles[track_index][pos].color == 'P'){
        color = 'P';
    }
    else if (_tiles[track_index][pos].color == 'O'){
        color = 'O';
    }
    else if (_tiles[track_index][pos].color == 'Y'){
        color = 'Y';
    }

    return color;
}