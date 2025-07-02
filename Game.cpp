#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Tile.h"

#include <vector>
#include <ctime>

using namespace std;

int main()
{
    int option;
    int player_count = 2;

    vector <Player> players;

    for (int i = 0; i < player_count; i++)
    {
        cout<<endl;
        cout << "Player "<< i+1 <<":" << endl;
        cout << "---------------------" << endl;
        cout << "Select your character (1|2|3|4|5):" << endl;
        cout << "1. Apollo | Age:5 | Strength:500 | Stamina:500 | Wisdom:1000| Pride Points:20000 (1)" << endl;
        cout << "2. Mane | Age:8 | Strength:900 | Stamina:600 | Wisdom:600| Pride Points:20000 (2)" << endl;
        cout << "3. Elsa | Age:12 | Strength:900 | Stamina:700 | Wisdom:500| Pride Points:20000 (3)" << endl;
        cout << "4. Zuri | Age:7 | Strength:600 | Stamina:500 | Wisdom:900| Pride Points:20000 (4)" << endl;
        cout << "5. Roary | Age:18 | Strength:1000 | Stamina:500 | Wisdom:500| Pride Points:20000 (5)" << endl;
 
        cin >> option;
        while (option < 1 || option > 5)
        {
            cout << "Choose from options (1|2|3|4|5):" << endl;
            cin >> option;
        }
 
        switch (option)
        {
        case 1: // apollo
            players.push_back(Player("Apollo", 5, 500, 500, 1000, 20000));
            break;
        case 2: // mane
            players.push_back(Player("Mane", 8, 900, 600, 600, 20000));
            break;
        case 3: // elsa
            players.push_back(Player("Elsa", 12, 900, 700, 500, 20000));
            break;
        case 4://zuri
            players.push_back(Player("Zuri", 7, 600, 500, 900, 20000));
            break;
        case 5://roary
            players.push_back(Player("Roary", 18, 1000, 500, 500, 20000));
            break;
        }
    }    

    srand(time(0));
    Board board(player_count);
    cout<<"\n----- GAME START -----"<<endl;
    cout<<endl;
    board.displayBoard();

    //make a loop for the game to run on
    int game_end = 0;
    while(!game_end)
    {
        for (int i = 0; i < player_count; i++)
        {
            bool turn_over = false;
            while(!turn_over)
            {
                cout<<endl;
                cout<<"Player "<<i+1<<"'s turn:"<<endl;
                cout<<"1. Check Player Progress"<<endl;
                cout<<"2. Review Character"<<endl;
                cout<<"3. Check Position"<<endl;
                cout<<"4. Review your Advisor"<<endl;
                cout<<"5. Move Forward"<<endl;

                cin >> option;
                while (cin.fail() || option < 1 || option > 5)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Choose from options (1|2|3|4|5):" << endl;
                    cin >> option;
                }

                switch(option)
                {
                case 1: 
                    players[i].checkPlayerProgress();
                    break;
                case 2: 
                    players[i].reviewCharacter();
                    break;
                case 3:
                    board.checkPosition(i+1);
                    break;
                case 4:
                    players[i].reviewAdvisor();
                    break;
                case 5:
                    board.movePlayer(i);
                    board.displayBoard();
                    turn_over = true;
                    break;
                }
            }
        } 
    }

    return 0;
}