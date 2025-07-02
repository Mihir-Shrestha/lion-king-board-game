//Petal Mohammed & Ella Nichols
#include "Board.h"
#include <iostream>

using namespace std;


#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

void Board::initializeBoard()
{
    // Seed random number generator in your main function once
    // CHANGED from 2, so no longer hard coded 
    for (int i = 0; i < _player_count; i++)
    {
        initializeTiles(i);  // This ensures each lane has a unique tile distribution
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void Board::initializeTiles(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'Y';
        } 
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 5;
            switch (color_choice)
            {
                case 0:
                    temp.color = 'B'; // Blue
                    break;
                case 1:
                    temp.color = 'P'; // Pink
                    break;
                case 2:
                    temp.color = 'N'; // Brown
                    break;
                case 3:
                    temp.color = 'R'; // Red
                    break;
                case 4:
                    temp.color = 'U'; // Purple
                    break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}


// Board::Board()
// {
//     _player_count = 1;

//     // Initialize player position
//     _player_position[0] = 0;

//     // Initialize tiles
//     initializeTiles();
// }

Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player position
   for (int i = 0; i < _player_count; i++) {
        string name = "Player " + to_string(i + 1);  // temporary name, replace later
        _players.push_back(Player(name));
    }
    // Initialize tiles

    initializeBoard();
}

bool Board::isPlayerOnTile(int player_index, int pos)
{
    return _players[player_index].position == pos;
}

void Board::displayTile(int player_index, int pos)
{
    // string space = "                                       ";
    string color = "";
    int player = isPlayerOnTile(player_index, pos);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[player_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[player_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[player_index][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[player_index][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[player_index][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[player_index][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[player_index][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[player_index][pos].color == 'Y')
    {
        color = GREY;
    }

     if (player == true)
    {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    }
    else
    {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int player_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(player_index, i);
    }
    cout << endl;
}

//WORKING DO NOT CHANGE
void Board::displayBoard()
{
    // changed for 3 players
    for (int i = 0; i < _player_count; i++)
    {
        // label the tracks for clarity too 
        cout << _players[i].name << "'s track:\n";
        displayTrack(i);
        // add an extra line between the two lanes for neatness
            cout << endl;  
    }
}

//WORKING - DO NOT CHANGE 
// function to move the player forward
bool Board::movePlayer(int player_index) {
    // if the player's current position is less than the final tile index
    if (_players[player_index].position < _BOARD_SIZE - 1) {
        // increment the player's position by 1
        _players[player_index].position++;
        // return true (movement happened)
        return true;
    }
    else {
        // ELSE return false (player is already at the end)
        return false;
    }
}


//WORKING - DO NOT CHANGE
//return the current tile position of the given player 
int Board::getPlayerPosition(int player_index) const {
    //if player index is valid (greater or equal to 0 and less than total player count)
    if (player_index >= 0 && player_index < _player_count) {
        //return the players current position from the player position array
        return _players[player_index].position;
    }
    //this will indicate it is invalid 
    return -1;
}
//ADDED FOR 3 PLAYERS
int Board::getPlayerCount() const {
    return _player_count;
}

void Board::setPlayerCharacter(int index, Character character) {
    if (index >= 0 && index < _players.size()) {
        _players[index].character = character;
    }
}

void Board::setPlayerName(int index, string name) {
    if (index >= 0 && index < _players.size()) {
        _players[index].name = name;
    }
}

void Board::setPlayerPath(int index, string path) {
    if (index >= 0 && index < _players.size()) {
        _players[index].pathChoice = path;

        if (path == "Puff Practice") {
            _players[index].character.pridePoints -= 5000;
            _players[index].character.stamina += 500;
            _players[index].character.strength += 500;
            _players[index].character.wisdom += 1000;

            _players[index].staminaBoost = 500;
            _players[index].strengthBoost = 500;
            _players[index].wisdomBoost = 1000;
            _players[index].pridePointAdjustment = -5000;
        }
        else if (path == "Sugar, Spice and Strategy") {
            _players[index].character.pridePoints += 5000;
            _players[index].character.stamina += 200;
            _players[index].character.strength += 200;
            _players[index].character.wisdom += 200;

            _players[index].staminaBoost = 200;
            _players[index].strengthBoost = 200;
            _players[index].wisdomBoost = 200;
            _players[index].pridePointAdjustment = 5000;
        }
    }
}

void Board::setPlayerAdvisor(int index, Advisor advisor) {
    if (index >= 0 && index < _players.size()) {
        _players[index].advisor = advisor;
        _players[index].hasAdvisor = (advisor.name != "None");
    }
}

void Board::handleTileEvent(int playerIndex) {
    int pos = _players[playerIndex].position;
    char tileColor = _tiles[playerIndex][pos].color;

    if (tileColor == 'G') {
        cout << "🌿 You landed on a grassy tile!\n";
    
        // 50% chance of event
        int chance = rand() % 2;
        if (chance == 0) {
            cout << "🌈 Phew! Nothing happened this time.\n";
            return;
        }
    
        vector<RandomEvent> events = loadRandomEvents("random_events.txt");
    
        Player p = _players[playerIndex];
        int path = (p.pathChoice == "Puff Practice") ? 0 : 1;
        int advisorMatch = 0;
        if (p.advisor.name == "The Mayor of Townsville") advisorMatch = 1;
        else if (p.advisor.name == "Miss Keane") advisorMatch = 2;
        else if (p.advisor.name == "Miss Sara Bellum") advisorMatch = 3;
        else if (p.advisor.name == "Mask Scara") advisorMatch = 4;
        else if (p.advisor.name == "Fuzzy Lumpkins") advisorMatch = 5;
    
        vector<RandomEvent> valid;
        for (int i = 0; i < events.size(); i++) {
            if (events[i].pathType == 2 || events[i].pathType == path) {
                valid.push_back(events[i]);
            }
        }
    
        if (valid.size() > 0) {
            int r = rand() % valid.size();
            RandomEvent chosen = valid[r];
    
            cout << "🌀 EVENT: " << chosen.description << endl;
    
            if (chosen.advisorID == advisorMatch && chosen.pridePoints < 0) {
                cout << "🛡️ Your advisor protected you from this negative event!\n";
            } else {
                p.character.pridePoints += chosen.pridePoints;
                _players[playerIndex].character.pridePoints = p.character.pridePoints;
                cout << "📊 Pride Points updated by " << chosen.pridePoints << ". New total: " << p.character.pridePoints << endl;
            }
        }
    }
    
    else if (tileColor == 'B') {
        cout << "💧 Oasis found! +200 to Stamina, Strength, Wisdom. You get an extra turn!\n";
        _players[playerIndex].character.stamina += 200;
        _players[playerIndex].character.strength += 200;
        _players[playerIndex].character.wisdom += 200;

        // Display the board and let them roll again
        displayBoard();
        int roll = rand() % 6 + 1;
        cout << "🎲 Rolling again! You rolled a " << roll << "!\n";
        for (int i = 0; i < roll; i++) {
            movePlayer(playerIndex);
        }
        displayBoard();
        handleTileEvent(playerIndex); 
    }
    else if (tileColor == 'P') {
        cout << "🎀 Counseling session! +300 to traits. You may change advisors.\n";
        _players[playerIndex].character.stamina += 300;
        _players[playerIndex].character.strength += 300;
        _players[playerIndex].character.wisdom += 300;

        // Prompt advisor change
        if (_players[playerIndex].hasAdvisor) {
            cout << "🌟 You already have an advisor (" << _players[playerIndex].advisor.name << ").\n";
            cout << "Would you like to change your advisor? (yes/no): ";
            string response;
            getline(cin, response);
            if (response == "yes") {
                vector<Advisor> advisors = loadAdvisors("advisors.txt");
                cout << "Choose a new advisor:\n";
                for (int i = 0; i < advisors.size(); i++) {
                    cout << i + 1 << ". " << advisors[i].name << " - " << advisors[i].ability << endl;
                }
                int newChoice;
                cin >> newChoice;
                cin.ignore();
                setPlayerAdvisor(playerIndex, advisors[newChoice - 1]);
                cout << "✅ Advisor updated to " << advisors[newChoice - 1].name << "!\n";
            }
        } else {
            vector<Advisor> advisors = loadAdvisors("advisors.txt");
            cout << "Choose your advisor:\n";
            for (int i = 0; i < advisors.size(); i++) {
                cout << i + 1 << ". " << advisors[i].name << " - " << advisors[i].ability << endl;
            }
            int choice;
            cin >> choice;
            cin.ignore();
            setPlayerAdvisor(playerIndex, advisors[choice - 1]);
            cout << "✅ Advisor set to " << advisors[choice - 1].name << "!\n";
        }
    }
    else if (tileColor == 'R') {
        cout << "🪦 Graveyard! Move back 10 tiles and lose 100 traits.\n";
        _players[playerIndex].position -= 10;
        if (_players[playerIndex].position < 0) {
            _players[playerIndex].position = 0;
        }
        _players[playerIndex].character.stamina -= 100;
        _players[playerIndex].character.strength -= 100;
        _players[playerIndex].character.wisdom -= 100;
        if (_players[playerIndex].character.stamina < 100) _players[playerIndex].character.stamina = 100;
        if (_players[playerIndex].character.strength < 100) _players[playerIndex].character.strength = 100;
        if (_players[playerIndex].character.wisdom < 100) _players[playerIndex].character.wisdom = 100;
    }
    else if (tileColor == 'N') {
        cout << "😈 It's a full-blown hyena hullabaloo in Townsville! You’re dragged back to your last position and lose 300 stamina.\n";
        _players[playerIndex].position -= 1; // Go back to previous
        if (_players[playerIndex].position < 0) _players[playerIndex].position = 0;
        _players[playerIndex].character.stamina -= 300;
        if (_players[playerIndex].character.stamina < 100) _players[playerIndex].character.stamina = 100;
    }
    else if (tileColor == 'U') {
        cout << "🧠 A challenge appears! Solve a riddle to gain wisdom!\n";

        vector<Riddle> riddles = loadRiddles("riddles.txt");
        if (riddles.size() == 0) {
            cout << "⚠️ No riddles available.\n";
            return;
        }

        int randIndex = rand() % riddles.size();
        Riddle chosen = riddles[randIndex];

        cout << "❓ RIDDLE: " << chosen.question << endl;
        cout << "💬 Your answer: ";
        string response;
        getline(cin, response);

        // convert both to lowercase to accept answers like "Class" or "class"
        for (int i = 0; i < response.size(); i++) response[i] = tolower(response[i]);
        for (int i = 0; i < chosen.answer.size(); i++) chosen.answer[i] = tolower(chosen.answer[i]);

        if (response == chosen.answer) {
            cout << "✅ Correct! You gain +500 Wisdom!\n";
            _players[playerIndex].character.wisdom += 500;
        } else {
            cout << "❌ Incorrect. The correct answer was: " << chosen.answer << endl;
        }

    }
    else if (tileColor == 'O') {
        cout << "🦁 Welcome to Pride Rock! Final stats will be calculated here!\n";
        // Step 4 will handle final stat conversion
    }
    else if (tileColor == 'Y') {
        cout << "🕊️ Starting tile - no event triggered.\n";
    }
}

vector<Player> Board::getPlayers() const {
    return _players;
}

int Board::calculateFinalPridePoints(int playerIndex) {
    Player p = _players[playerIndex];
    int bonus = (p.character.stamina / 100 + p.character.strength / 100 + p.character.wisdom / 100) * 1000;
    return p.character.pridePoints + bonus;
}


