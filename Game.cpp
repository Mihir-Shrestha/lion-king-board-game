#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "InputData.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
    srand(time(0));

    cout << "\nWelcome to The Circle of Life - A Lion King Themed Board Game!" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "\nIn this game, you'll take on the role of a character from the Lion King universe." << endl;
    cout << "Navigate the board, answer riddles, and face random events as you journey through the wild." << endl;
    cout << "Your goal is to collect Pride Points and survive the challenges of the savanna!" << endl;
    cout << "\nOnce all players reach the end of the board, the player with the most Pride Points wins the game!" << endl;
    cout << "\nGet ready to test your luck, strategy, and knowledge in the Circle of Life." << endl;
    cout << "\nLet the adventure begin!" << endl;
    cout << "\n--------------------------------------------------------------" << endl;

    int player_count = 2;
    cout << "\nSelect the number of players (2-4): ";
    cin >> player_count;
    while (cin.fail() || player_count < 2 || player_count > 5)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nPlease enter a valid number of players (2-5):" << endl;
        cin >> player_count;
    }

    Board board(player_count);

    cout << "\nYou have selected " << player_count << " players." << endl;

    cout << "\nEach player will choose a character with unique attributes. The characters are as follows:" << endl;

    int option;
    vector<Player> players;
    vector<Character> character_list = read_characters_from_file("input_files/characters.txt");
    RandomEvent random_events = read_random_events_from_file("input_files/random_events.txt");
    vector<Riddles> riddles = read_riddles_from_file("input_files/riddles.txt");

    for (int i = 0; i < player_count; i++)
    {
        string player_name;
        cout << "\nEnter name of Player " << i + 1 << ": ";
        cin >> player_name;

        cout << "\nPlayer " << i + 1 << " / " << player_name << endl;
        cout << "---------------------" << endl;

        int index = 1;
        for (auto character : character_list)
        {
            cout << index << ". " << character.name << " | Age:" << character.age << " | Strength:" << character.strength
                 << " | Stamina:" << character.stamina << " | Wisdom:" << character.wisdom
                 << " | Pride Points:" << character.pride_points << endl;
            index++;
        }
        cout << "\nSelect your character (1-" << character_list.size() << "): ";

        cin >> option;
        while (cin.fail() || option < 1 || option > character_list.size())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nChoose from options (1-" << character_list.size() << "): " << endl;
            cin >> option;
        }
        int path_index;
        cout << "\nChoose your path:" << endl;
        cout << "1. Cub Training (Assigned advisor, -5000 Pride Points,+500 Stamina, +500 Strength and +1000 Wisdom Points )" << endl;
        cout << "2. Straight to the Pride Lands (No advisor, +5000 Pride Points, +200 Stamina, +200 Strength and +200 Wisdom Points )" << endl;
        cin >> path_index;

        while (cin.fail() || path_index < 1 || path_index > 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nChoose from options (1|2): " << endl;
            cin >> path_index;
        }

        board.setPathActive(path_index - 1);
        board.setPlayerPath(i, path_index - 1);

        Character selected_character = character_list[option - 1];

        string selected_advisor = "None";
        if (path_index == 1)
        {
            selected_character.pride_points -= 5000;
            selected_character.stamina += 500;
            selected_character.strength += 500;
            selected_character.wisdom += 1000;

            vector<pair<string, string>> advisors = {
                {"Rafiki", "Invisibility - Become un-seen"},
                {"Nala", "Night Vision - Clearly see in darkness"},
                {"Sarabi", "Energy Manipulation - Shape and control the properties of energy"},
                {"Zazu", "Weather Control - Influence and manipulate weather patterns"},
                {"Sarafina", "Super Speed - Run 4x faster than the maximum speed of a lion"}};

            cout << "\nChoose an advisor for your character:" << endl;
            for (int i = 0; i < advisors.size(); i++)
            {
                cout << i + 1 << ". " << advisors[i].first << " - " << advisors[i].second << endl;
            }

            int option;
            cin >> option;

            while (cin.fail() || option < 1 || option > 5)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Choose from options (1|2|3|4|5):" << endl;
                cin >> option;
            }

            switch (option)
            {
            case 1:
                selected_advisor = "Rafiki";
                break;
            case 2:
                selected_advisor = "Nala";
                break;
            case 3:
                selected_advisor = "Sarabi";
                break;
            case 4:
                selected_advisor = "Zazu";
                break;
            case 5:
                selected_advisor = "Sarafina";
                break;
            }
            cout << "\nYou have chosen " << selected_advisor << " as your advisor." << endl;
        }
        else if (path_index == 2)
        {
            selected_character.pride_points += 5000; // Straight to the Pride Lands path
            selected_character.stamina += 200;
            selected_character.strength += 200;
            selected_character.wisdom += 200;
        }

        players.push_back(Player(player_name, path_index, selected_character.name, selected_character.age,
                                 selected_character.strength, selected_character.stamina, selected_character.wisdom, selected_character.pride_points, selected_advisor));

        character_list.erase(character_list.begin() + option - 1);
    }

    cout << "\n----- GAME START -----" << endl;
    board.displayBoard();

    // Main game loop
    bool game_end = false;
    while (!game_end)
    {
        for (int i = 0; i < player_count; i++)
        {
            // Skip the turn if the player has already reached the end
            if (players[i].hasPlayerReachedEnd())
                continue;

            bool turn_over = false;
            while (!turn_over)
            {
                cout << "\n----- Player " << i + 1 << "'s turn: -----" << endl;
                cout << "1. Check Player Progress" << endl;
                cout << "2. Review Character" << endl;
                cout << "3. Check Position" << endl;
                cout << "4. Review your Advisor" << endl;
                cout << "5. Move Forward" << endl;

                cin >> option;
                while (cin.fail() || option < 1 || option > 5)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\nChoose from options (1|2|3|4|5):" << endl;
                    cin >> option;
                }

                switch (option)
                {
                case 1:
                {
                    players[i].checkPlayerProgress();
                    break;
                }
                case 2:
                {
                    players[i].reviewCharacter();
                    break;
                }
                case 3:
                {
                    int pos = board.getPlayerPosition(i);
                    cout << "\nPlayer " << i + 1 << " is on tile " << pos + 1 << endl;
                    break;
                }
                case 4:
                {
                    cout << "Advisor: " << players[i].getAdvisor() << endl;
                    break;
                }
                case 5:
                {
                    int current_player_position = board.getPlayerPosition(i);
                    char current_tile_color = board.getTileColor(i, current_player_position);

                    // move player forward, apply tile effects and its effect on player position
                    board.movePlayer(i);

                    int new_player_position = board.getPlayerPosition(i);
                    char new_tile_color = board.getTileColor(i, new_player_position);

                    players[i] = board.applyTileEffect(players[i], new_tile_color, i, riddles, random_events);

                    if (new_tile_color == 'R') // Red tile means move back 10 tiles
                    {
                        board.setPlayerPosition(i, new_player_position - 10);
                        board.displayBoard();
                        turn_over = true;
                    }
                    else if (new_tile_color == 'N') // Brown tile means move player back to the last position;
                    {
                        int last_position = board.getPlayerLastPosition(i);
                        board.setPlayerPosition(i, last_position);
                        board.displayBoard();
                        turn_over = true;
                    }
                    else if (new_tile_color == 'B') // If Blue tile, player gets an extra turn
                    {
                        cout << endl;
                        board.displayBoard();
                        cout << "You get an extra turn!" << endl;
                    }
                    else
                    {
                        cout << endl;
                        board.displayBoard();
                        turn_over = true;
                    }
                    break;
                }
                }
            }
            // Check if the player has reached the end of the board
            if (board.playerReachedEnd(i))
            {
                cout << "\n Congratulations Player " << i + 1 << "! You have reached the end of the board ..." << endl;
                players[i].setPlayerEndGame();
                players[i].calculateLeadershipToPride();
                break;
            }
        }

        // Check if all players have reached the end
        bool all_reached_end = true;
        for (auto player : players)
        {
            if (!player.hasPlayerReachedEnd())
            {
                all_reached_end = false;
                break;
            }
        }
        if (all_reached_end)
        {
            game_end = true;
            cout << "\n----- All players have reached the end! -----\n"
                 << endl;
        }
    }

    // Determine the winner based on pride points
    int max_pride_points = -1;
    int winner_index = -1;

    for (int i = 0; i < player_count; i++)
    {
        if (players[i].getPridePoints() > max_pride_points)
        {
            max_pride_points = players[i].getPridePoints();
            winner_index = i;
        }
    }
    cout << "Game Results:" << endl;
    cout << "-----------------" << endl;
    cout << "Winner: Player " << winner_index + 1 << " (" << players[winner_index].getName() << ")" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < player_count; i++)
    {
        cout << "Player " << i + 1 << ": " << players[i].getName() << endl;
        cout << "Age: " << players[i].getAge() << endl;
        cout << "Stamina: " << players[i].getStamina() << endl;
        cout << "Strength: " << players[i].getStrength() << endl;
        cout << "Wisdom: " << players[i].getWisdom() << endl;
        cout << "Pride Points: " << players[i].getPridePoints() << endl;
        cout << "Advisor: " << players[i].getAdvisor() << endl;
        cout << "-----------------" << endl;
    }

    cout << "\n----- GAME OVER -----\n"
         << endl;

    // Write game results to a file
    ofstream results_file("game_results.txt");
    if (results_file.is_open())
    {
        results_file << "Game Results:" << endl;
        results_file << "-----------------" << endl;
        results_file << "Winner: Player " << winner_index + 1 << " (" << players[winner_index].getName() << ")" << endl;
        results_file << "-----------------" << endl;
        for (int i = 0; i < player_count; i++)
        {
            results_file << "Player " << i + 1 << ": " << players[i].getName() << endl;
            results_file << "Age: " << players[i].getAge() << endl;
            results_file << "Stamina: " << players[i].getStamina() << endl;
            results_file << "Strength: " << players[i].getStrength() << endl;
            results_file << "Wisdom: " << players[i].getWisdom() << endl;
            results_file << "Pride Points: " << players[i].getPridePoints() << endl;
            results_file << "Advisor: " << players[i].getAdvisor() << endl;
            results_file << "-----------------" << endl;
        }
    }
    return 0;
}