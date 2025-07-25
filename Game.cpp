#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "InputData.h"

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
        cout << endl;
        cout << "Player " << i + 1 << ":" << endl;
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
                cout << endl;
                cout << "Player " << i + 1 << "'s turn:" << endl;
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
                    cout << "Choose from options (1|2|3|4|5):" << endl;
                    cin >> option;
                }

                switch (option)
                {
                case 1:
                    players[i].checkPlayerProgress();
                    break;
                case 2:
                    players[i].reviewCharacter();
                    break;
                case 3:
                    board.checkPosition(i);
                    break;
                case 4:
                    players[i].reviewAdvisor();
                    break;
                case 5:
                    board.movePlayer(i);
                    cout << endl;
                    board.displayBoard();
                    turn_over = true;
                    break;
                }
            }
        }
    }

    return 0;
}