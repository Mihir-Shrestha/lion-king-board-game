#include "Player.h"

#include <iostream>
#include <string>

using namespace std;

Player::Player(string _player_name, int _path_index, string name, int age, int stamina, int strength, int wisdom, int pride_points, string advisor, bool reached_end)
{
    _player_name = _player_name;
    _path_index = _path_index;
    _name = name;
    _age = age;
    _stamina = stamina;
    _strength = strength;
    _wisdom = wisdom;
    _pride_points = pride_points;
    _advisor = advisor;
    _reached_end = reached_end;
}

void Player::checkPlayerProgress()
{
    cout << endl;
    cout << "Stamina: " << _stamina << endl;
    cout << "Strength: " << _strength << endl;
    cout << "Wisdom: " << _wisdom << endl;
    cout << "Pride Points: " << _pride_points << endl;
    cout << endl;
}

void Player::reviewCharacter()
{
    cout << endl;
    cout << "Character: " << _name << endl;
    cout << "Age: " << _age << endl;
}

string Player::getPlayerName() const
{
    return _player_name;
}

string Player::getName() const
{
    return _name;
}

int Player::getAge() const
{
    return _age;
}

int Player::getStamina() const
{
    return _stamina;
}

int Player::getStrength() const
{
    return _strength;
}

int Player::getWisdom() const
{
    return _wisdom;
}

int Player::getPridePoints() const
{
    return _pride_points;
}

string Player::getAdvisor() const
{
    return _advisor;
}

void Player::setStamina(int value)
{
    _stamina += value;
    if (_stamina < 100)
        _stamina = 100;
}

void Player::setStrength(int value)
{
    _strength += value;
    if (_strength < 100)
        _strength = 100;
}

void Player::setWisdom(int value)
{
    _wisdom += value;
    if (_wisdom < 100)
        _wisdom = 100;
}

void Player::setPridePoints(int value)
{
    _pride_points += value;
    if (_pride_points < 100)
        _pride_points = 100;
}

void Player::setAdvisor(string advisor)
{
    _advisor = advisor;
}

int Player::calculateLeadershipToPride()
{
    int stamina = getStamina();
    int strength = getStrength();
    int wisdom = getWisdom();
    int pride_points = getPridePoints();

    _pride_points += (stamina + strength + wisdom) / 100 * 1000;

    return _pride_points;
}

bool Player::hasPlayerReachedEnd() const
{
    return _reached_end;
}

void Player::setPlayerEndGame()
{
    _reached_end = true;
}
