#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

struct Character
{
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
};
vector<Character> read_characters_from_file(string filename);

#endif