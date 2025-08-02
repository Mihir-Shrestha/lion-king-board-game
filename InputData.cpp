#include "InputData.h"

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
        getline(ss, token);
        c.pride_points = stoi(token);

        characters.push_back(c);
    }
    return characters;
}

RandomEvent read_random_events_from_file(string filename)
{
    RandomEvent random_events;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return random_events;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty() || line.substr(0, 2) == "//") // Skip empty lines and comments
            continue;

        stringstream ss(line);

        Event event;
        string token;

        getline(ss, event.description, '|');
        getline(ss, token, '|');
        event.path_type = stoi(token);
        getline(ss, token, '|');
        event.advisor = stoi(token);
        getline(ss, token);
        event.pride_points = stoi(token);

        if (event.pride_points < 0)
        {
            random_events.negative_events.push_back(event);
        }
        else
        {
            random_events.positive_events.push_back(event);
        }
    }
    return random_events;
}

vector<Riddles> read_riddles_from_file(string filename)
{
    vector<Riddles> riddles;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return riddles;
    }

    string line;
    getline(file, line); // to skip the first header line in the file

    while (getline(file, line))
    {
        stringstream ss(line);
        Riddles riddle;
        getline(ss, riddle.question, '|');
        getline(ss, riddle.answer);

        riddles.push_back(riddle);
    }
    return riddles;
}
