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
    static const int _MAX_PLAYERS = 4;
    int _player_count;
    std::vector<int> _player_paths;
    std::vector<bool> _board_active = {false, false}; // Two paths: 0 for Cub training, 1 for Lion training
    Tile _tiles[2][_BOARD_SIZE];
    int _player_position[_MAX_PLAYERS];
    int _player_last_position[_MAX_PLAYERS];
    void displayTile(int player_index, int pos);
    void initializeTiles(int path_index);
    bool isAnyoneOnTile(int pos);
    bool isPlayerOnTile(int player_index, int pos);

public:
    Board(int player_count);
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    bool isPathActive(int path_index);
    void setPathActive(int path_index);
    int getPlayerPath(int player_index);
    void setPlayerPath(int player_index, int path_index);
    void movePlayer(int player_index);
    int getPlayerPosition(int player_index) const;
    void setPlayerPosition(int player_index, int position);
    int getPlayerLastPosition(int player_index) const;
    char getTileColor(int player_index, int position) const;
    Player applyTileEffect(Player player, char tile_color, int player_index, std::vector<Riddles> riddles, RandomEvent random_events);
    bool playerReachedEnd(int player_index) const;
};

#endif