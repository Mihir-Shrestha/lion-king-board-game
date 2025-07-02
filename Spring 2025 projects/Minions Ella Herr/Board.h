#include <iostream>

using namespace std;

#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

class Board
{
    public:
        Board();
        Board(int player_count);
        void displayTrack(int track_index, Player player1, Player player2);
        void initializeBoard();
        void displayBoard(int track_index, Player player1, Player player2);
        bool movePlayer(int player_index);
        int getPlayerPosition(int player_index) const;
        void setPlayerPosition(int player_index, int pos);
        char getColor(int track_index, int pos);
        
    private:
        static const int _BOARD_SIZE = 52;
        Tile _tiles[2][_BOARD_SIZE];
        static const int _MAX_PLAYERS = 2;
        int _player_count;
        int _player_position[_MAX_PLAYERS];
        void displayTile(int pos, int track_index, Player player1, Player player2);
        void initializeTiles(int track_index);
        bool isPlayerOnTile(int pos, int track_index, Player player);
};
#endif
