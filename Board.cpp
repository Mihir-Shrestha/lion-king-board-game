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

#include <iostream>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <map>

using namespace std;

void Board::initializeBoard()
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i); // This ensures each lane has a unique tile distribution
    }
}

void Board::initializeTiles(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1)
        {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        }
        else if (i == 0)
        {
            // Set the first tile as Grey for "Pride Rock"
            temp.color = 'Y';
        }
        else
        {
            if (player_index == 0)
            {
                if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count))
                {
                    temp.color = 'G'; // Green tile
                    green_count++;
                }
                else
                {
                    int val = rand() % 100;
                    if (i < total_tiles / 2)
                    {
                        if (val < 20)
                            temp.color = 'R'; // Red tile
                        else if (val < 40)
                            temp.color = 'N'; // Brown tile
                        else if (val < 55)
                            temp.color = 'P'; // Pink tile
                        else if (val < 80)
                            temp.color = 'B'; // Blue tile
                        else if (val < 100)
                            temp.color = 'U'; // Purple tile
                    }
                    else
                    {
                        if (val < 20)
                            temp.color = 'R';
                        else if (val < 40)
                            temp.color = 'N';
                        else if (val < 55)
                            temp.color = 'P';
                        else if (val < 70)
                            temp.color = 'B';
                        else if (val < 100)
                            temp.color = 'U';
                    }
                }
            }
            else if (player_index == 1)
            {
                if (green_count < 20 && (rand() % (total_tiles - i) < 20 - green_count))
                {
                    temp.color = 'G';
                    green_count++;
                }
                else
                {
                    int val = rand() % 100;
                    if (i < total_tiles / 2)
                    {
                        if (val < 25)
                            temp.color = 'R';
                        else if (val < 50)
                            temp.color = 'N';
                        else if (val < 70)
                            temp.color = 'P';
                        else if (val < 75)
                            temp.color = 'B';
                        else if (val < 100)
                            temp.color = 'U';
                    }
                    else
                    {
                        if (val < 15)
                            temp.color = 'R';
                        else if (val < 30)
                            temp.color = 'N';
                        else if (val < 50)
                            temp.color = 'P';
                        else if (val < 75)
                            temp.color = 'B';
                        else if (val < 100)
                            temp.color = 'U';
                    }
                }
            }
        }
        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}

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
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize tiles
    initializeBoard();
}

bool Board::isPlayerOnTile(int player_index, int pos)
{
    if (_player_position[player_index] == pos)
    {
        return true;
    }
    return false;
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

void Board::displayBoard()
{
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
            cout << "\nCub Training" << endl;
        else
            cout << "\nStraight to the Pride Lands" << endl;
        displayTrack(i);
    }
    cout << endl;
}

void Board::movePlayer(int player_index)
{
    // Store the last position before moving
    _player_last_position[player_index] = _player_position[player_index];

    // Increment player position based on dice roll
    int dice_roll = rand() % 6 + 1;
    _player_position[player_index] += dice_roll;

    cout << "\nYou rolled a " << dice_roll << endl;

    // if (_player_position[player_index] == _BOARD_SIZE - 1)
    // {
    //     // Player reached last tile
    //     return true;
    // }
    // return false;
}

int Board::getPlayerPosition(int player_index) const
{
    if (player_index >= 0 && player_index <= _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}

void Board::setPlayerPosition(int player_index, int position)
{
    if (position < 0)
    {
        _player_position[player_index] = 0; // Ensure position does not go below 0
    }
    else if (position >= _BOARD_SIZE)
    {
        _player_position[player_index] = _BOARD_SIZE - 1; // Ensure position does not exceed board size
    }
    else
    {
        _player_position[player_index] = position; // Set the player to the specified position
    }
}

int Board::getPlayerLastPosition(int player_index) const
{
    if (player_index >= 0 && player_index < _MAX_PLAYERS)
    {
        return _player_last_position[player_index];
    }
    return -1; // Return -1 if the player index is invalid
}

char Board::getTileColor(int player_index, int position) const
{
    if (position >= 0 && position < _BOARD_SIZE)
    {
        return _tiles[player_index][position].color;
    }
    return ' '; // Return a space if the position is invalid
}

Player Board::applyTileEffect(Player player, char tile_color, int player_index, vector<Riddles> riddles, RandomEvent random_events)
{
    switch (tile_color)
    {
    case 'G':
    {
        cout << "\nYou landed on a Green tile!" << endl;

        int event_occurs = rand() % 2; // 0 for no event, 1 for event
        if (event_occurs == 0)
        {
            cout << "\nNothing happens..." << endl;
        }
        else
        {
            map<string, int> advisors = {// Advisor names and their corresponding indices
                                         {"None", 0},
                                         {"Rafiki", 1},
                                         {"Nala", 2},
                                         {"Sarabi", 3},
                                         {"Zazu", 4},
                                         {"Sarafina", 5}};

            cout << "\nThere is an event on this tile!" << endl;

            int event_type = rand() % 2; // 0 for negative event, 1 for positive event
            if (event_type == 0)
            {
                int rand_neg = rand() % random_events.negative_events.size();
                while (random_events.negative_events[rand_neg].path_type != player_index)
                {
                    rand_neg = rand() % random_events.negative_events.size();
                }
                cout << "\n"
                     << random_events.negative_events[rand_neg].description << endl;

                // Check if advisor's protection is applicable
                if (random_events.negative_events[rand_neg].advisor != advisors[player.getAdvisor()])
                {
                    int to_deduct_pride_points = random_events.negative_events[rand_neg].pride_points;

                    cout << "\nYou lose " << to_deduct_pride_points << " pride points" << endl;

                    player.setPridePoints(to_deduct_pride_points);
                }
                else
                {
                    cout << "\nYour advisor protected you from this event!" << endl;
                }
            }
            else
            {
                // Apply positive event effects to the player
                int rand_pos = rand() % random_events.positive_events.size();
                while (random_events.positive_events[rand_pos].path_type != player_index)
                {
                    rand_pos = rand() % random_events.positive_events.size();
                }
                cout << "\n"
                     << random_events.positive_events[rand_pos].description << endl;

                int to_increase_pride_points = random_events.positive_events[rand_pos].pride_points;

                cout << "\nYou gain " << to_increase_pride_points << " pride points" << endl;

                player.setPridePoints(to_increase_pride_points);
            }
        }

        break;
    }

    case 'B':
    {
        cout << "\nYou landed on a Blue tile!" << endl;

        cout << "\nYou've found a peaceful oasis! Take a deep breath and relax. You gain 200 Stamina, Strength and Wisdom points. You also gain an extra turn to move forward." << endl;

        player.setStamina(200);
        player.setStrength(200);
        player.setWisdom(200);

        break;
    }

    case 'P':
    {
        cout << "\nYou landed on a Pink tile!" << endl;

        cout << "\nWelcome to the land of enrichment! You gain 300 Stamina, Strength and Wisdom points. You also get to choose or change your current Advisor." << endl;

        player.setStamina(300);
        player.setStrength(300);
        player.setWisdom(300);

        vector<pair<string, pair<int, string>>> advisors = {
            {"None", {0, "No special abilities"}},
            {"Rafiki", {1, "Invisibility - Become un-seen"}},
            {"Nala", {2, "Night Vision - Clearly see in darkness"}},
            {"Sarabi", {3, "Energy Manipulation - Shape and control the properties of energy"}},
            {"Zazu", {4, "Weather Control - Influence and manipulate weather patterns"}},
            {"Sarafina", {5, "Super Speed - Run 4x faster than the maximum speed of a lion"}}};

        string current_advisor = player.getAdvisor();

        if (current_advisor == "None")
        {
            cout << "\nYou currently have no advisor. Choose one from the list below:" << endl;

            cout << endl;
            for (auto advisor : advisors)
            {
                if (advisor.first == "None")
                    continue; // Skip the "None" advisor
                cout << advisor.second.first << ". " << advisor.first << " | " << advisor.second.second << endl;
            }

            int option;
            cin >> option;

            while (option < 1 || option > advisors.size() - 1)
            {
                cout << "Choose from options (1|2|3|4|5):" << endl;
                cin >> option;
            }

            switch (option)
            {
            case 1:
                player.setAdvisor("Rafiki");
                break;
            case 2:
                player.setAdvisor("Nala");
                break;
            case 3:
                player.setAdvisor("Sarabi");
                break;
            case 4:
                player.setAdvisor("Zazu");
                break;
            case 5:
                player.setAdvisor("Sarafina");
                break;
            }

            cout << "You have chosen " << player.getAdvisor() << " as your advisor." << endl;
        }
        else
        {
            cout << "\nYou currently have " << player.getAdvisor() << " as your advisor." << endl;
            cout << "\nWould you like to change your advisor? (y/n)" << endl;

            char option;
            cin >> option;
            while (option != 'y' && option != 'n')
            {
                cout << "\nPlease enter 'y' or 'n':" << endl;
                cin >> option;
            }

            if (option == 'y')
            {
                cout << "\nChoose one from the list below." << endl;

                for (auto advisor : advisors)
                {
                    if (advisor.first == "None")
                        continue; // Skip the "None" advisor
                    cout << advisor.second.first << ". " << advisor.first << " | " << advisor.second.second << endl;
                }

                int option;
                cin >> option;

                while (option < 1 || option > advisors.size() - 1)
                {
                    cout << "\nChoose from options (1|2|3|4|5):" << endl;
                    cin >> option;
                }

                switch (option)
                {
                case 1:
                    player.setAdvisor("Rafiki");
                    break;
                case 2:
                    player.setAdvisor("Nala");
                    break;
                case 3:
                    player.setAdvisor("Sarabi");
                    break;
                case 4:
                    player.setAdvisor("Zazu");
                    break;
                case 5:
                    player.setAdvisor("Sarafina");
                    break;
                }

                cout << "\nYou have chosen " << player.getAdvisor() << " as your new advisor." << endl;
            }
            else if (option == 'n')
            {
                cout << "\nYou have chosen to keep your current advisor." << endl;
            }
        }

        break;
    }

    case 'R':
    {
        cout << "\nYou landed on a Red tile!" << endl;

        cout << "\nUh-oh, you have stumbled into the Graveyard! You lose 100 Stamina, Strength and Wisdom points. You also go back 10 spaces." << endl;

        player.setStamina(-100);
        player.setStrength(-100);
        player.setWisdom(-100);

        break;
    }

    case 'N':
    {
        cout << "\nYou landed on a Brown tile!" << endl;

        cout << "\nThe Hyenas are on the prowl! They drag you back to where you were last. You also lose 100 Stamina points." << endl;

        player.setStamina(-100);

        break;
    }

    case 'U':
    {
        cout << "\nYou landed on a Purple tile!" << endl;

        cout << "\nTime for a test of wits! You gain or lose 500 Wisdom points depending on whether your answer is right or wrong." << endl;

        int riddle_index = rand() % riddles.size();
        cout << "\nRiddle: " << riddles[riddle_index].question << endl;

        string answer;
        cout << "\nYour answer: ";
        cin >> answer;

        if (answer == riddles[riddle_index].answer)
        {
            cout << "\nCorrect answer! You gain 500 Wisdom points." << endl;
            player.setWisdom(500);
        }
        else
        {
            cout << "\nIncorrect answer! You lose 500 Wisdom points." << " The right answer was: " << riddles[riddle_index].answer << endl;
            player.setWisdom(-500);
        }

        break;
    }
    }
    return player;
}