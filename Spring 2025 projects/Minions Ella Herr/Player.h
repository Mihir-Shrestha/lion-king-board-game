#include <iostream>

using namespace std;

/*This class defines a player and its stats*/
class Player
{
    public:
        Player();
        Player(string name, string fav_thing, int stamina, int strength, int smarts, int minion_points, string advisor, int path_type);
        string getName(); // returns _name of the player
        string getFavThing(); // returns _fav_thing
        int getStamina(); // returns _stamina of the character
        int getStrength(); // returns the strength of the player
        int getSmarts(); // returns the smarts of the player
        int getMinionPoints(); // returns _minion_points of the player
        string getAdvisor(); // returns name of player's advisor
        int getPath(); // returns path number player chose 1. Mission(0) or 2. Minion Training(1)
        int getPosition(); // returns path position
        void setName(string name); // sets the _name to the value of the provided string parameter
        void setFavThing(string fav_thing); // sets _fav_thing to the value of the provided string parameter
        void setStamina(int stamina); // sets amount of _stamina the player possesses to the given value stamina only if it is > 100, else is not changed
        void setStrength(int strength); // amount of _strength the player possesses to the given value strength only if it is > 100, else is not changed
        void setSmarts(int smarts); // amount of _smarts the player possesses to the given value smarts only if it is > 100, else is not changed
        void setMinionPoints(int minion_points); // sets the amount of _minion_points the player possesses to the given value minion_points only if it is > 100, else is not changed
        void setAdvisor(string advisor); // sets advisor name to player chosen advisor
        void setPath(int path); // set path number to player chosen path
        void setPosition(int position); // sets player position
    

    private:
        string _name;
        string _fav_thing;
        int _stamina;
        int _strength;
        int _smarts;
        int _minion_points;
        string _advisor;
        int _path_type;
        int _position;
};

class Advisor
{
    string advisor;
    string power;
};