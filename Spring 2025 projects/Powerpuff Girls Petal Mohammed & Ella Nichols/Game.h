//Petal Mohammed & Ella Nichols
#ifndef GAME_H
#define GAME_H
#include "Player.h"


#include <string>
using namespace std;

struct Character {
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
};

struct Advisor {
    string name;
    string ability;
};

struct RandomEvent {
    string description;
    int pathType;      // 0 = Puff Practice, 1 = Sugar, Spice..., 2 = both
    int advisorID;     // 0 = none, 1 = Mayor, 2 = Keane, etc.
    int pridePoints;   // may be negative or positive
};

struct Riddle {
    string question;
    string answer;
};


class Player;

void showMainMenu(int currentPlayerIndex, vector<Player> players);
vector<Advisor> loadAdvisors(string filename);
vector<RandomEvent> loadRandomEvents(string filename);
vector<Riddle> loadRiddles(string filename);




#endif
