#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(){
    _name = "";
    _stamina = 100;
    _strength = 100;
    _smarts = 100;
    _advisor = "None";
    _path_type = 0;
    _minion_points = 20000;
}

Player::Player(string name, string fav_thing, int stamina, int strength, int smarts, int minion_points, string advisor, int path_type){
    _name = name;
    _fav_thing = fav_thing;
    _advisor = advisor;

    //stamina
    if(stamina >= 100){
        _stamina = stamina;
    }
    else{
        _stamina = 100;
    }

    //strength
    if(strength >= 100){
        _strength = strength;
    }
    else{
        _strength = 100;
    }

    //smarts
    if(smarts >= 100){
        _smarts = smarts;
    }
    else{
        _smarts = 100;
    }

    //minion_points
    if(minion_points >= 100){
        _minion_points = minion_points;
    }
    else{
        _minion_points = 100;
    }

    //path_type
    if(path_type == 0 || path_type == 1){
        _path_type = path_type;
    }
    else{
        _path_type = 0;
    }
}

string Player::getName(){
    return _name;
}

string Player::getFavThing(){
    return _fav_thing;
}

int Player::getStamina(){
    return _stamina;
}

int Player::getStrength(){
    return _strength;
}

int Player::getSmarts(){
    return _smarts;
}

int Player::getMinionPoints(){
    return _minion_points;
}

string Player::getAdvisor(){
    return _advisor;
}

int Player::getPath(){
    return _path_type;
}

int Player::getPosition(){
    return _position;
}

void Player::setName(string name){
    _name = name;
}

void Player::setFavThing(string fav_thing){
    _fav_thing = fav_thing;
}

void Player::setStamina(int stamina){
    if(stamina >= 100){
        _stamina = stamina;
    }
    else{
        _stamina = 100;
    }
}

void Player::setStrength(int strength){
    if(strength >= 100){
        _strength = strength;
    }
    else{
        _strength = 100;
    }
} 

void Player::setSmarts(int smarts){
    if(smarts >= 100){
        _smarts = smarts;
    }
    else{
        _smarts = 100;
    }
}

void Player::setMinionPoints(int minion_points){
    if(minion_points >= 100){
        _minion_points = minion_points;
    }
    else{
        _minion_points = 100;
    }
}

void Player::setAdvisor(string advisor){
    _advisor = advisor;
}

void Player::setPath(int path_type){
    if(path_type == 0 || path_type == 1){
        _path_type = path_type;
    }
    else{
        _path_type = 0;
    }
}

void Player::setPosition(int position){
    if(position < 0){
        _position = 0;
    }
    else if(position >= 51){
        _position = 51;
    }
    else{
        _position = position;
    }
}

