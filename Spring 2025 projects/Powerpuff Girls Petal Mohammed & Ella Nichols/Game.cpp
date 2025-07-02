//Petal Mohammed & Ella Nichols
#include "Player.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

vector<Advisor> loadAdvisors(string filename) {
    vector<Advisor> advisors;
    ifstream file(filename);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        Advisor a;
        stringstream ss(line);
        getline(ss, a.name, '|');
        getline(ss, a.ability);
        advisors.push_back(a);
    }
    return advisors;
}

vector<RandomEvent> loadRandomEvents(string filename) {
    vector<RandomEvent> events;
    ifstream file(filename);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        RandomEvent e;
        stringstream ss(line);
        string token;

        getline(ss, e.description, '|');
        getline(ss, token, '|'); e.pathType = stoi(token);
        getline(ss, token, '|'); e.advisorID = stoi(token);
        getline(ss, token, '|'); e.pridePoints = stoi(token);

        events.push_back(e);
    }

    return events;
}

vector<Riddle> loadRiddles(string filename) {
    vector<Riddle> riddles;
    ifstream file(filename);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        Riddle r;
        stringstream ss(line);
        getline(ss, r.question, '|');
        getline(ss, r.answer);
        riddles.push_back(r);
    }

    return riddles;
}


void showMainMenu(int currentPlayerIndex, vector<Player> players) {
    int choice = 0;
    do {
        cout << "\n🌟 MAIN MENU for " << players[currentPlayerIndex].name << " (" << players[currentPlayerIndex].character.name << ") 🌟\n";
        cout << "1. Check Player Progress\n";
        cout << "2. Review Character\n";
        cout << "3. Check Position\n";
        cout << "4. Review Your Advisor\n";
        cout << "5. Move Forward (Roll Dice)\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "\n📊 Pride Points: " << players[currentPlayerIndex].character.pridePoints << endl;
                cout << "💪 Strength: " << players[currentPlayerIndex].character.strength << endl;
                cout << "⚡ Stamina: " << players[currentPlayerIndex].character.stamina << endl;
                cout << "🧠 Wisdom: " << players[currentPlayerIndex].character.wisdom << endl;
                break;

            case 2:
                cout << "\n🎭 Character: " << players[currentPlayerIndex].character.name << endl;
                cout << "📅 Age: " << players[currentPlayerIndex].character.age << endl;
                break;

            case 3:
                cout << "\n📍 You are on tile " << players[currentPlayerIndex].position << endl;
                break;

            case 4:
                cout << "\n🧙 Advisor: " << players[currentPlayerIndex].advisor.name << endl;
                cout << "✨ Ability: " << players[currentPlayerIndex].advisor.ability << endl;
                break;

            case 5:
                cout << "\n🎲 Preparing to roll...\n";
                break;

            default:
                cout << "❌ Invalid choice. Try again.\n";
        }

    } while (choice != 5);
}
