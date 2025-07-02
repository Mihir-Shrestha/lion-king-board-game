#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player
{
    private:
        string _name;
        int _age;
        int _stamina;
        int _strength;
        int _wisdom;
        int _pride_points;
        string _advisor;

    public:
        Player(string name, int age, int stamina, int strength, int wisdom, int pride_points, string advisor = "");
        void checkPlayerProgress();
        void reviewCharacter();
        // void checkPosition();        creating this function in board class instead
        void reviewAdvisor();
        // void moveForward();          this will go in board class as well
        string getName() const;
        int getAge() const;
        int getStamina() const;
        int getStrength() const;
        int getWisdom() const;
        int getPridePoints() const;
        void setStamina(int value);
        void setStrength(int value);
        void setWisdom(int value);
        void setPridePoints(int value);
        void leadershipToPride();
        // void useAbility();
};

#endif