#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Riddle+Random.h"

using namespace std;

class Game
{
    public:
        Game();
        Game(Player players[], int num_players, Riddle riddles[]); // default 
        int getNumPlayers(); // returns the current number of players _num_players
        void setPlayersList(Player players[], int num_players); 
        bool setPlayer(int index, Player new_player); // replaces a player object at the specified index in the _players array
        Player getPlayer(string name); // returns an objects from the _players array based on the provided name. if no object matches the name, returns a new blank Player object
        int findPlayer(string name); // returns the index of the player object in the _players array base on the provided name
        void printStats(int); // prints Minion Points and Skill Stats
        
        void MainMenu(); // displays main menu and asks player to choose where to go and based on what number is chosen goes to another function 
        void StartGame(); // gives the background information of the game and asks players to choose characters and paths
        void WhoWin(); // compare player's points once they get to final tile, announces winner, and prints stats in terminal and output file

        void printPlayerStats(); // prints player stats
        void chooseCharacters(string); // makes player choose character and stores Player in _players array
        void choosePaths(string); // makes players choose paths

        int getPlayerIndex(); // returns current index of _players array aka which player's turn it is
        void changePlayerIndex(); // changes player index between 0 and 1

        void whatTileDo(char color); // bunch if-else statements that do things depending on what color is landed on
        void Riddles();
        void Random_Events();

        int getLastSpot();
        void setLastSpot(int last_spot);

    
    private:
        vector<Player> _player_options;
        Player _players[2]; // array storing player objects
        vector<string> _advisor_options;
        int _num_players; // current number of players in the game
        int player_index; // current player we are on in _players array 0 (Player 1) and 1 (Player 2)
        int _last_spot; // used soley for the Brown tile to figure out where the player was before their turn
        Board board;
        Riddle _riddles[27]; // array storing the riddles
        RandomEvents _positive_events[30];
        RandomEvents _negative_events[20];
};