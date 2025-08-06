#ifndef PLAYER_H
#define PLAYER_H

#include <string>
class Player
{
private:
    std::string _player_name;
    std::string _name;
    int _age;
    int _stamina;
    int _strength;
    int _wisdom;
    int _pride_points;
    std::string _advisor;
    bool _reached_end;

public:
    Player(std::string _player_name, int _path_index, std::string name, int age, int stamina, int strength, int wisdom, int pride_points, std::string advisor = "None", bool reached_end = false);
    void checkPlayerProgress();
    void reviewCharacter();
    std::string getPlayerName() const;
    std::string getName() const;
    int getAge() const;
    int getStamina() const;
    int getStrength() const;
    int getWisdom() const;
    int getPridePoints() const;
    std::string getAdvisor() const;
    void setStamina(int value);
    void setStrength(int value);
    void setWisdom(int value);
    void setPridePoints(int value);
    void setAdvisor(std::string advisor);
    int calculateLeadershipToPride();
    bool hasPlayerReachedEnd() const;
    void setPlayerEndGame();
};

#endif