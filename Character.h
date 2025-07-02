#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

struct Character
{
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
};

vector<Character> read_characters_from_file(string filename)
{
    vector<Character> characters;
    
    ifstream file(filename);

    if(!file.is_open())
    {
        cerr<<"Error opening file: "<<filename<<endl;
        return characters;
    }


    string line;
    getline(file, line); //to skip the first header line in the file

    while(getline(file, line))
    {
        stringstream ss(line);
        string token;
        Character c;

        getline(ss, c.name, '|');
        getline(ss, token, '|');
        c.age = stoi(token);
        getline(ss, token, '|');
        c.strength = stoi(token);
        getline(ss, token, '|');
        c.stamina = stoi(token);
        getline(ss, token, '|');
        c.wisdom = stoi(token);
        getline(ss, token, '|');
        c.pridePoints = stoi(token);

        characters.push_back(c);
    }
     
}

#endif