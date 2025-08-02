#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "InputData.h"

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int main()
{
    int option;
    int player_count = 2;

    vector<Player> players;
    vector<Character> character_list = read_characters_from_file("input_files/characters.txt");
    RandomEvent random_events = read_random_events_from_file("input_files/random_events.txt");
    vector<Riddles> riddles = read_riddles_from_file("input_files/riddles.txt");

    for (int i = 0; i < player_count; i++)
    {
        cout << "\nPlayer " << i + 1 << ":" << endl;
        cout << "---------------------" << endl;
        cout << "Select your character (1|2|3|4|5):" << endl;

        int index = 1;
        for (auto character : character_list)
        {
            cout << index << ". " << character.name << " | Age:" << character.age << " | Strength:" << character.strength
                 << " | Stamina:" << character.stamina << " | Wisdom:" << character.wisdom
                 << " | Pride Points:" << character.pride_points << endl;
            index++;
        }

        cin >> option;
        while (option < 1 || option > 5)
        {
            cout << "Choose from options (1|2|3|4|5):" << endl;
            cin >> option;
        }

        Character selected_character = character_list[option - 1];

        players.push_back(Player(selected_character.name, selected_character.age, selected_character.strength,
                                 selected_character.stamina, selected_character.wisdom, selected_character.pride_points));

        character_list.erase(character_list.begin() + option - 1);
    }

    srand(time(0));
    Board board(player_count);
    cout << "\n----- GAME START -----" << endl;
    cout << endl;
    board.displayBoard();

    // make a loop for the game to run on
    int game_end = 0;
    while (!game_end)
    {
        for (int i = 0; i < player_count; i++)
        {
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
        }
    }
    return 0;
}