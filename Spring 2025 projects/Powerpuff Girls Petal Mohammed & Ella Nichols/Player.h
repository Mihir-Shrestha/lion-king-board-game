//Petal Mohammed & Ella Nichols
#ifndef PLAYER_H
#define PLAYER_H
#include "Game.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Player {
    string name;
    int position;
    Character character;
    string pathChoice;

    int staminaBoost;
    int strengthBoost;
    int wisdomBoost;
    int pridePointAdjustment;

    Advisor advisor;
    bool hasAdvisor;

    Player(string n) {
    name = n;
    position = 0;
    pathChoice = "";
    staminaBoost = 0;
    strengthBoost = 0;
    wisdomBoost = 0;
    pridePointAdjustment = 0;
    advisor.name = "None";
    advisor.ability = "No ability";
    hasAdvisor = false;

}

};

#endif
