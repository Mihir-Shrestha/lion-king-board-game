#include <Character.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

vector<Character> read_characters_from_file(string filename)
{
    vector<Character> characters;

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return characters;
    }

    string line;
    getline(file, line); // to skip the first header line in the file

    while (getline(file, line))
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
    return characters;
}