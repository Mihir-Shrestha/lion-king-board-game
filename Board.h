#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include "Player.h"
#include "InputData.h"
#include <vector>

class Board
{
private:
    static const int _BOARD_SIZE = 52;
    static const int _MAX_PLAYERS = 2;
    Tile _tiles[2][_BOARD_SIZE];
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    int _player_last_position[_MAX_PLAYERS];
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index);
    bool isPlayerOnTile(int player_index, int pos);

public:
    Board();
    Board(int player_count);
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    void movePlayer(int player_index);
    int getPlayerPosition(int player_index) const;
    void setPlayerPosition(int player_index, int position);
    int getPlayerLastPosition(int player_index) const;
    char getTileColor(int player_index, int position) const;
    Player applyTileEffect(Player player, char tile_color, int player_index, std::vector<Riddles> riddles, RandomEvent random_events);
};

#endif