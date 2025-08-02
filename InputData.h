#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

struct Character
{
    std::string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pride_points;
};

struct Event
{
    std::string description;
    int path_type;    // 0 for cub training, 1 for straight to the pride lands
    int advisor;      // 0 for none, 1-5 for different advisors
    int pride_points; // positive or negative points
};

struct RandomEvent
{
    std::vector<Event> positive_events;
    std::vector<Event> negative_events;
};

struct Riddles
{
    std::string question;
    std::string answer;
};

std::vector<Character> read_characters_from_file(std::string filename);
RandomEvent read_random_events_from_file(std::string filename);
std::vector<Riddles> read_riddles_from_file(std::string filename);

#endif