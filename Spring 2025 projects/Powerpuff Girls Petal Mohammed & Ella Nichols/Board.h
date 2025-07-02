//Petal Mohammed & Ella Nichols
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
using namespace std;

class Board
{
private:
static const int _BOARD_SIZE = 52;
//updated this to 3 for extra credit 
static const int _MAX_PLAYERS = 3;
Tile _tiles[_MAX_PLAYERS][_BOARD_SIZE];
int _player_count;
//int _player_position[_MAX_PLAYERS];
void displayTile(int player_index, int pos);
void initializeTiles(int player_index);
bool isPlayerOnTile(int player_index, int pos);
vector<Player> _players;


public:
Board();
Board(int player_count);
void displayTrack(int player_index);
void initializeBoard();
void displayBoard();
//move the player on the board 
bool movePlayer(int player_index);
int getPlayerPosition(int player_index) const;
// ADDED IN FOR 3 PLAYERS
int getPlayerCount() const;
void setPlayerName(int index, string name);
void setPlayerCharacter(int index, Character character);
void setPlayerPath(int index, string path);
void setPlayerAdvisor(int index, Advisor advisor);
void handleTileEvent(int playerIndex);
vector<Player> getPlayers() const;
// Calculation
int calculateFinalPridePoints(int playerIndex);

};
#endif
