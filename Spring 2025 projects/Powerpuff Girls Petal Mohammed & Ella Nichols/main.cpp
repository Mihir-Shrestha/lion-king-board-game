//Petal Mohammed & Ella Nichols
#include "Board.h"
#include "Game.h"
#include <iostream>
//for rand()
#include <cstdlib> 
//for time()
#include <ctime>   
//for ascii art 
#include <fstream> 
#include <sstream>

using namespace std;

vector<Character> loadCharacters(string filename) {
    vector<Character> characters;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line)) {
        Character c;
        stringstream ss(line);
        string token;

        getline(ss, c.name, '|');
        getline(ss, token, '|'); c.age = stoi(token);
        getline(ss, token, '|'); c.strength = stoi(token);
        getline(ss, token, '|'); c.stamina = stoi(token);
        getline(ss, token, '|'); c.wisdom = stoi(token);
        getline(ss, token, '|'); c.pridePoints = stoi(token);

        characters.push_back(c);
    }

    return characters;
}

struct PlayerWithScore {
    string name;
    string character;
    int pridePoints;
};

void sortPlayersByScore(PlayerWithScore players[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (players[j].pridePoints > players[i].pridePoints) {
                PlayerWithScore temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }
}


int main() {
    //ASCII ART
    ifstream artFile("ascii_art.txt"); 
    //only print if opened
    if (artFile) { 
        string line;
        while (getline(artFile, line)) {
            cout << line << endl;
        }
        artFile.close();
    }

    cout << endl;

    cout << "💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚💗💙💚Welcome to the Powerpuff Pursuit💚💙💗💚💙💗💚💙💗💚💙💗💚💙💗💚💙💗💚💙💗💚💙💗💚💙💗💚💙💗💚💙💗💚💗💙💚💗💙💚" << endl;
    cout << "✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨Let the Pursuit Begin✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨✨" <<endl;
    cout << endl; 

    // generate random number for dice roll 
    srand(time(0)); 

    //CHANGED NOW 3 PLAYERS
    //PROMPT FOR CHARACTER
    int playerCount = 3;
    vector<string> names;
    vector<Character> availableCharacters = loadCharacters("characters.txt");
    vector<Character> selectedCharacters;
    vector<string> selectedPaths;
    vector<Advisor> selectedAdvisors;
    vector<Advisor> availableAdvisors = loadAdvisors("advisors.txt");
    vector<pair<string, string> > finishOrder;
    vector<bool> playerFinished(playerCount, false);



    for (int i = 0; i < playerCount; i++) {
        string name;
        cout << "🌈 💫 Player " << (i + 1) << ", please enter your name: ";
        getline(cin, name);
        names.push_back(name);

        // Show available characters
        cout << endl;
        cout << "🍭 Choose your character 🍭\n";
        cout << "------------------------" << endl;
        for (int j = 0; j < availableCharacters.size(); j++) {
            cout << j + 1 << ". " << availableCharacters[j].name << endl;
        }

    //GAME BUG - game crashes plays itself if anything is entered that isn't on menu 
        /*int choice;
        cout << "Enter number: ";
        cin >> choice;
        cin.ignore();
        */

    int choice;
    while (true) {
        cout << "Enter number: ";
        if (!(cin >> choice)) {
            cout << "❌ Invalid input, please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (choice < 1 || choice > availableCharacters.size()) {
            cout << "❌ Invalid option, please choose between 1 and " << availableCharacters.size() << ".\n";
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }



        // Save selected character
        selectedCharacters.push_back(availableCharacters[choice - 1]);
        availableCharacters.erase(availableCharacters.begin() + (choice - 1));

        // Path selection
        cout << "🍭🌶️💖✨ Sugar, Spice, or everything nice? Choose your destiny! 🍭🌶️💖✨";
        cout << "\n💅💫🎀 Choose your path: 🎮🔥💣\n";
        cout << "\n1. Puff Practice 🧪 (Training - stronger traits, slower start, includes advisor)\n";
        cout << "2. Sugar, Spice and Strategy ⚡ (Faster start, weaker traits, no advisor)\n";
        cout << endl;

        //ANOTHER BUG - WILL ACCEPT ANSWERS OTHER THAN 1 OR 2
        /*int pathChoice;
        cin >> pathChoice;
        cin.ignore();
        */

    int pathChoice;
    while (true) {
        cout << "Enter path choice: ";
        if (!(cin >> pathChoice)) {
            cout << "❌ Invalid input, please select Puff Practice or Sugar, Spice and Strategy.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (pathChoice != 1 && pathChoice != 2) {
            cout << "❌ Invalid option, please select Puff Practice or Sugar, Spice and Strategy.\n";
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }


        string selectedPath;
        if (pathChoice == 1) {
            selectedPath = "Puff Practice";
        } else {
            selectedPath = "Sugar, Spice and Strategy";
        }

    selectedPaths.push_back(selectedPath);

    /// ADVISOR PROMPTING FOR ONLY PUFF PRACTICE
    if (selectedPath == "Puff Practice") {
    cout << "\n🌈 Choose your advisor 🌈\n";
    cout << "--------------------------" << endl;
    for (int k = 0; k < availableAdvisors.size(); k++) {
        cout << k + 1 << ". " << availableAdvisors[k].name << " - " << availableAdvisors[k].ability << endl;
    }

    //ANOTHER BUG, WILL ACCEPT ANSWERS OUTSIDE RANGE
    /*int advisorChoice;
    cout << "Enter number: ";
    cin >> advisorChoice;
    cin.ignore();
    cout << endl;
    */

    int advisorChoice;
    while (true) {
        cout << "Enter number: ";
        if (!(cin >> advisorChoice)) {
            cout << "❌ Invalid input, please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (advisorChoice < 1 || advisorChoice > availableAdvisors.size()) {
            cout << "❌ Invalid choice, please choose between 1 and " << availableAdvisors.size() << ".\n";
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }


    selectedAdvisors.push_back(availableAdvisors[advisorChoice - 1]);
    availableAdvisors.erase(availableAdvisors.begin() + (advisorChoice - 1));
    } else {
        Advisor none = {"None", "No ability"};
        selectedAdvisors.push_back(none);
    }
    cout << endl;

    /// EVERYTHING ELSE BELOW WORKING
    }


    Board game(playerCount);



    // inject names into the player list
    for (int i = 0; i < playerCount; i++) {
        game.setPlayerName(i, names[i]); 
        game.setPlayerCharacter(i, selectedCharacters[i]);
        game.setPlayerPath(i, selectedPaths[i]);
        game.setPlayerAdvisor(i, selectedAdvisors[i]);
    }
    


    int currentPlayer = 0;
   

    // GAME LOOP
    while (finishOrder.size() < playerCount) {
        // ---- Player Turn ----
        //THIS IS AUTO ROLL TAKE OUT
        /*
        cout << names[currentPlayer] << "'s turn. Press Enter to roll.";
        cout<<endl;
        cin.ignore(); // wait for Enter key

        // ---- Roll the die (1–6) ----
        int roll = rand() % 6 + 1;
        cout << "You rolled a " << roll << "!" << endl;
        cout << endl;

        // ---- Move the player forward by roll amount ----
        for (int i = 0; i < roll; i++) {
            game.movePlayer(currentPlayer);
        }

        // ---- Display updated board ----
        game.displayBoard();
        */

       //NEW FOR MENU 
       int menuChoice = 0;

    while (menuChoice != 5) {
        showMainMenu(currentPlayer, game.getPlayers()); // players must be accessible here
        cout << "Choose an option from the menu (1–5): ";
        cin >> menuChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menuChoice == 5) {
            // Player chose to move
            int roll = rand() % 6 + 1;
            cout << "🎲 You rolled a " << roll << "!" << endl;

            for (int i = 0; i < roll; i++) {
                game.movePlayer(currentPlayer);
            }

            game.displayBoard(); // Show updated board after moving
            game.handleTileEvent(currentPlayer);
        }
    }


        // ---- Check for win ----
        if (game.getPlayerPosition(currentPlayer) == 51 && !playerFinished[currentPlayer]) {
            playerFinished[currentPlayer] = true;
            finishOrder.push_back(make_pair(selectedCharacters[currentPlayer].name, names[currentPlayer]));

        cout << selectedCharacters[currentPlayer].name << " finished the game! 🏆" << endl;
    }


    // move to next player
    currentPlayer = (currentPlayer + 1) % game.getPlayerCount();

    }
    cout << "\n📊 Calculating final Pride Points (with trait bonuses)...\n";

    PlayerWithScore finalStats[3]; // adjust if you ever go beyond 3
    
    for (int i = 0; i < playerCount; i++) {
        int finalScore = game.calculateFinalPridePoints(i);
        finalStats[i].name = names[i];
        finalStats[i].character = selectedCharacters[i].name;
        finalStats[i].pridePoints = finalScore;
    }
    
    sortPlayersByScore(finalStats, playerCount);
    
    cout << "🏆 FINAL RANKINGS 🏆" << endl;
    for (int i = 0; i < playerCount; i++) {
        if (i == 0) cout << "🥇 ";
        else if (i == 1) cout << "🥈 ";
        else if (i == 2) cout << "🥉 ";
        else cout << "🔸 ";
        
        cout << finalStats[i].name << " (" << finalStats[i].character << ") — " << finalStats[i].pridePoints << " Pride Points" << endl;
    }
    
}
