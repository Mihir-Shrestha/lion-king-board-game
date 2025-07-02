#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "Game.h"

using namespace std;

Game::Game(){
    _num_players = 0;
    player_index = 0;
    board = Board(2);
}

Game::Game(Player players[], int num_players, Riddle riddles[]){

    if((num_players < 2)||(num_players > 2)){
        num_players = 2;
    }
    _num_players = num_players;

    for(int index1 = 0; index1 < _num_players; index1++){
        _players[index1] = players[index1];
    }

    for(int index2 = 0; index2 < 27; index2++){
        _riddles[index2] = _riddles[index2];
    }
}

int Game::getNumPlayers(){
    return _num_players;
}

void Game::setPlayersList(Player players[], int num_players){
    for(int index = 0; (index < num_players)&&(index < 2); index++){
        _players[index] = players[index];
    }

    if(num_players > 2){
        _num_players = 2;
    }
    else{
        _num_players = num_players;
    }
}


bool Game::setPlayer(int index, Player new_player){
    if((index < 2)&&(index >= 0)){
        _players[index] = new_player;
        return true;
    }
    else{
        return false;
    }
} 
        
Player Game::getPlayer(string name){
    for(int index = 0; index < _num_players; index++){
        if(_players[index].getName() == name){
            return _players[index];
        }
    }
    return Player();
}

int Game::findPlayer(string name){
    for(int index = 0; index < _num_players; index++){
        if(_players[index].getName() == name){
            return index;
        }
    }
    return -1;
} 

void Game::printStats(int index){ // prints character's current Minion Points and Skills Points
    cout << _players[index].getName() << "'s Current Stats" << endl;
    cout << "Minion Points: " << _players[index].getMinionPoints() << endl;
    cout << "Stamina: " << _players[index].getStamina() << endl;
    cout << "Strength: " << _players[index].getStrength() << endl;
    cout << "Smarts: " << _players[index].getSmarts() << endl;
}

/*Gives the background information of the game and asks players to choose characters and paths*/
void Game::StartGame(){

    cout << "Welcome to the Minion Game!!" << endl;
    cout << endl;
    cout << "Gru is looking for a new head minion to keep things moving in the lab when he is away as things got a little out of hand last time he left. The minions will go through a series of tests that will assess their skills of stamina, strength and smarts. To prepare for these tests, players will either go through Minion Training or go on a Mission. Along the way, they'll make strategic decisions, face unexpected challenges, and collect Minion Points as they grow and refine their Skills. The player who earns the most Minion Points by demonstrating they have what it takes to lead the minions in the lab and on missions will be chosen as the Head Minion!" << endl;
    cout << endl;
    cout << "Let's get started! Press enter to continue." << endl;
    cin.get(); // This allows us to pause and cin enter when ready to continue
    cout << endl;

    chooseCharacters("characters.txt");
    choosePaths("advisors.txt");
    cout << "Let the games begin!" << endl;
    board.displayBoard(0, _players[0], _players[1]);
    cout << endl;
}

void Game::MainMenu(){ // display's main menu and asks player to choose where to go and based on what number is chosen goes to another function 
    
    if((_players[0].getPosition() == 51)&&(_players[1].getPosition() == 51)){
        return;
    }
    else if(_players[getPlayerIndex()].getPosition() == 51){
        changePlayerIndex();
        MainMenu();
    }
    else{
        int choice;
            
        cout << "Main Menu: Player " << player_index + 1 << " choose an option to continue :)" << endl;
        cout << "1. Check Player Progress" << endl; // review Minoion Points and Skill Stats
        cout << "2. Review Character" << endl; // check character name and favorite thing
        cout << "3. Check Position" << endl; // display board to check current position
        cout << "4. Review Advisor" << endl; // check who your current advisor is
        cout << "5. Move Forward" << endl; // spin virtual spinner

        cin >> choice; // player choice
        cout << endl;

        if ((choice < 1) || (choice > 5)){
            while((choice < 1) || (choice > 5)){
                cout << "Invalid input. Please select a valid option." << endl;
                MainMenu();
            }
        }
        else{
            switch(choice){
                case 1: // Check Player Progress (minion points and skill stats)
                    printStats(getPlayerIndex());
                    cout << endl;
                    MainMenu();

                case 2: // Review Character (name and favorite thing or fun fact)
                    int fav_or_fun;
                    cout << "Choose an option to continue:" << endl;
                    cout << "1. Your Character's Favorite Thing" << endl;
                    cout << "2. Fun Fact About Your Character" << endl;
                    cin >> fav_or_fun;
                    if((fav_or_fun != 1)&&(fav_or_fun != 2)){
                        while((fav_or_fun != 1)&&(fav_or_fun != 2)){
                            cout << "Invalid input. Please select a valid option." << endl;
                            cin >> fav_or_fun;
                        }
                    }
                    cout << endl;

                    switch(fav_or_fun){
                        case 1:
                            cout << "Your Minion is " << _players[getPlayerIndex()].getName();
                            if((_players[getPlayerIndex()].getName()== "Bob")||(_players[getPlayerIndex()].getName()== "Stuart")||(_players[getPlayerIndex()].getName()== "Otto")){
                                cout << ", and his favorite thing is his " << _players[getPlayerIndex()].getFavThing() << "." << endl;
                            }
                            else if((_players[getPlayerIndex()].getName()== "Kevin")||(_players[getPlayerIndex()].getName()== "Dave")){
                                cout << ", and his favorite thing is " << _players[getPlayerIndex()].getFavThing() << "." << endl;
                            }
                            break;
                        case 2:
                            cout << "Your Minion is " << _players[getPlayerIndex()].getName()  << ", and a fun fact about him is that ";
                            if(_players[getPlayerIndex()].getName() == "Bob"){
                                cout << "his favorite animal is a rat named Poochy." << endl;
                            }
                            else if(_players[getPlayerIndex()].getName() == "Kevin"){
                                cout << "he has old British man hobbies (cricket and golf)." << endl;
                            }
                            else if(_players[getPlayerIndex()].getName() == "Stuart"){
                                cout << "he once got a snow globe from the Queen of England." << endl;
                            }
                            else if(_players[getPlayerIndex()].getName() == "Dave"){
                                cout << "he is good at video games." << endl;
                            }
                            else if(_players[getPlayerIndex()].getName() == "Otto"){
                                cout << "he has 12 sprouts of hair." << endl;
                            }
                            break;
                    }
                    cout << endl;
                    MainMenu();

                case 3: // Check Position
                    cout << "Player " << player_index + 1 << " you are currently on tile " << board.getPlayerPosition(player_index) << "." << endl;
                    board.displayBoard(_players[getPlayerIndex()].getPath(), _players[0], _players[1]);
                    cout << endl;
                    MainMenu();

                case 4: // Review Advisor
                    if(_players[getPlayerIndex()].getAdvisor() == "None"){
                        cout << "You do not have an advisor at the moment. You need to land on pink tile to choose an advisor." << endl;
                    }
                    else{ // Secondary layer: how advisor helps or fun fact about advisor
                        int help_or_fun;
                        cout << "Choose an option to continue:" << endl;
                        cout << "1. How Your Advisor Helps" << endl;
                        cout << "2. Fun Fact About Your Advisor" << endl;
                        cin >> help_or_fun;
                        if((help_or_fun != 1)&&(help_or_fun != 2)){
                            while((help_or_fun != 1)&&(help_or_fun != 2)){
                                cout << "Invalid input. Please select a valid option." << endl;
                                cin >> help_or_fun;
                            }
                        }
                        cout << endl;

                        switch(help_or_fun){
                            case 1: // How advisor helps
                                cout << "Your advisor is " << _players[getPlayerIndex()].getAdvisor() << ", and they help you with ";
                                if(_players[getPlayerIndex()].getAdvisor() == "Felonius Gru"){
                                    cout << "villany skills." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Dr. Nefario"){
                                    cout << "gadgets." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Silas Ramsbottom"){
                                    cout << "combatting problems with the Anti-Villain League." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Master Chow"){
                                    cout << "fighting." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Lucy Wilde"){
                                    cout << "moral." << endl;
                                }
                                break;
                            case 2: // Fun fact about advisor
                                cout << "Your advisor is " << _players[getPlayerIndex()].getAdvisor() << ", and a fun fact about ";
                                if(_players[getPlayerIndex()].getAdvisor() == "Felonius Gru"){
                                    cout << "him is that he is bald." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Dr. Nefario"){
                                    cout << "him is that he enjoys disco dancing." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Silas Ramsbottom"){
                                    cout << "him is that he likes to do the YMCA." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Master Chow"){
                                    cout << "her is that she is a chiropractor." << endl;
                                }
                                else if(_players[getPlayerIndex()].getAdvisor() == "Lucy Wilde"){
                                    cout << "her is that her favorite weapon is is the lipstick taser." << endl;
                                }
                                break;
                        }
                    }
                    cout << endl;
                    MainMenu();

                case 5: // Move Forward
                    setLastSpot(board.getPlayerPosition(getPlayerIndex())); // records where player is before they move
                    board.movePlayer(getPlayerIndex()); // Moves player
                    _players[getPlayerIndex()].setPosition(board.getPlayerPosition(getPlayerIndex())); // Changes character position number in player object
                    board.displayBoard(_players[getPlayerIndex()].getPath(), _players[0], _players[1]); // Displays board
                    cout << endl;
                    whatTileDo(board.getColor(_players[getPlayerIndex()].getPath(), board.getPlayerPosition(getPlayerIndex())));
                    changePlayerIndex(); // Switches from player 1 to player 2
                    cout << endl;
                    MainMenu();
            }
        }
    }
}


void Game::WhoWin(){
    // compare player's points once they get to final tile, announces winner, and prints stats in output file and terminal
    int stamina1, stamina2, strength1, strength2, smarts1, smarts2;
    int index = 0;

    cout << "You have both made it back to the lab after your long journeys enhancing your skills and collecting Minion Points. Time to see who did the best!" << endl;
    cout << endl;
    //Stats in Terminal
    cout << "The Final Results:" << endl;
    cout << endl;
    for(index = 0; index < 2; index++){
        cout << "--- Player " << index + 1 << " Stats ---" << endl;
        cout << "Name: " << _players[index].getName() << endl;
        cout << "Stamina: " << _players[index].getStamina() << endl;
        cout << "Strength: " << _players[index].getStrength() << endl;
        cout << "Smarts: " << _players[index].getSmarts() << endl;
        cout << "Minion Points: " << _players[index].getMinionPoints() << endl;
        cout << endl;
    }

    //Stats in Output File
    ofstream output_file("final_stats.txt");
    for(index = 0; index < 2; index++){
        output_file << "--- Player " << index + 1 << " Stats ---" << endl;
        output_file << "Name: " << _players[index].getName() << endl;
        output_file << "Stamina: " << _players[index].getStamina() << endl;
        output_file << "Strength: " << _players[index].getStrength() << endl;
        output_file << "Smarts: " << _players[index].getSmarts() << endl;
        output_file << "Minion Points: " << _players[index].getMinionPoints() << endl;
        output_file << endl;
    }

    // Setting Player 1 Final Minion Points
    stamina1 = _players[0].getStamina()/100;
    strength1 = _players[0].getStrength()/100;
    smarts1 = _players[0].getSmarts()/100;
    _players[0].setMinionPoints(_players[0].getMinionPoints() + 1000*(stamina1 + strength1 + smarts1));

    // Setting Player 2 Final Minion Points
    stamina2 = _players[1].getStamina()/100;
    strength2 = _players[1].getStrength()/100;
    smarts2 = _players[1].getSmarts()/100;
    _players[1].setMinionPoints(_players[1].getMinionPoints() + 1000*(stamina2 + strength2 + smarts2));

    // Final Minion Points and Winner in Terminal
    index = 0;
    for(index = 0; index < 2; index++){
        cout << "Player " << index + 1 << " Final Minion Points: " << _players[index].getMinionPoints() << endl;
    }

    cout << endl;
    if(_players[0].getMinionPoints() > _players[1].getMinionPoints()){
        cout << "The winner is Player 1! Congrats, " << _players[0].getName() << " is now Head Minion!" << endl;
    }
    else if(_players[0].getMinionPoints() < _players[1].getMinionPoints()){
        cout << "The winner is Player 2! Congrats, " << _players[1].getName() << " is now Head Minion!" << endl;
    }

    cout << "Thank you for playing!" << endl;

    // Final Minion Points and Winner in Output File
    index = 0;
    for(index = 0; index < 2; index++){
        output_file << "Player " << index + 1 << " Final Minion Points: " << _players[index].getMinionPoints() << endl;
    }

    output_file << endl;
    if(_players[0].getMinionPoints() > _players[1].getMinionPoints()){
        output_file << "The winner is Player 1! Congrats, " << _players[0].getName() << " is now Head Minion!" << endl;
    }
    else if(_players[0].getMinionPoints() < _players[1].getMinionPoints()){
        output_file << "The winner is Player 2! Congrats, " << _players[1].getName() << " is now Head Minion!" << endl;
    }

    output_file.close();

}


/*Split function*/
int split(string input_string, char separator, string arr[], const int ARR_SIZE){
    double i = 0;
    int j = 0;
    double num = 0;
    stringstream a(input_string);


    if (input_string == ""){
        return 0;
    }
    for (i = 0; i < input_string.length(); i++){
        if (input_string[i] == separator){
            num++;
        }
    }


    if (num == 0){
        getline(a, arr[j], separator);
        return 1;
    }
    else if((num + 1) > ARR_SIZE){
        for (j = 0; j < ARR_SIZE; j++){
            getline(a, arr[j], separator);
        }
        return -1;
    }
    else{
        for (j = 0; j < (num + 1); j++){
            getline(a, arr[j], separator);
        }
        return (j);
    } 
}

void Game::chooseCharacters(string file_name){

    ifstream characters_file(file_name);// opens a file

    if (characters_file.fail())
    {
        cout << "Could not open file." << endl; // or something else went wrong opening the file
        return;
    }

    // initialize vector here
    string line;
    const int size = 6;
    string character_stats[size]; // stores each part of line (different character stats) in array
    Player player;
    string name;
    int index = 0;


    cout << "Choose Your Minion (Player 1): " << endl;
    getline(characters_file, line); // Reads first line in txt file

    while(getline(characters_file, line)){
        /* Read line
        Put each thing in part of line_array
        Convert each part of array to correct data type and put it into player object
        Store player objects in _player_options*/

        split(line, '|', character_stats, size);
        player.setName(character_stats[0]);
        player.setFavThing(character_stats[1]);
        player.setStamina(stoi(character_stats[2]));
        player.setStrength(stoi(character_stats[3]));
        player.setSmarts(stoi(character_stats[4]));
        player.setMinionPoints(stoi(character_stats[5]));

        cout << character_stats[0] << endl;

        // Stores each player option in a vector
        _player_options.push_back(player);
    }
    cout << endl;
    cout << "Player 1: " << endl;
    cin >> name; // player 1 chooses character
    cout << endl;

    if((name != "Bob")&&(name != "Kevin")&&(name != "Stuart")&&(name != "Dave")&&(name != "Otto")){
        while((name != "Bob")&&(name != "Kevin")&&(name != "Stuart")&&(name != "Dave")&&(name != "Otto")){
            cout << "Invalid Minion name. Please choose a Minion from the list above." << endl;
            cout << endl;
            cout << "Player 1:" << endl;
            cin >> name;
            cout << endl;
        }
    }

    for(int i = 0; i < 5; i++){
        if(_player_options[i].getName() == name){
            _players[index] = _player_options[i]; // stores chosen player in _players array
            _player_options.erase(_player_options.begin() + i); // deletes chosen player from _player_options vector
            index++;
            i = 0;
            break;
        }
    }

    cout << "Choose Your Minion (Player 2): " << endl;
    for(int i = 0; i < 4; i++){
        cout << _player_options[i].getName() << endl;
    }
    cout << endl;
    cout << "Player 2: " << endl;
    cin >> name; // player 2 chooses character
    cout << endl;

    if((name != _player_options[0].getName())&&(name != _player_options[1].getName())&&(name != _player_options[2].getName())&&(name != _player_options[3].getName())){
        while((name != _player_options[0].getName())&&(name != _player_options[1].getName())&&(name != _player_options[2].getName())&&(name != _player_options[3].getName())){
            cout << "Invalid Minion name. Please choose a Minion from the list above." << endl;
            cout << endl;
            cout << "Player 2:" << endl;
            cin >> name;
            cout << endl;
        }
    }

    for(int i = 0; i < 5; i++){ // Takes chosen player 2 from _player_options, using the name of character, to transfer all player stats to _players array
        if(_player_options[i].getName() == name){
            _players[index] = _player_options[i]; // stores chosen player in _players array
            _player_options.erase(_player_options.begin() + i); // deletes chosen player from _player_options vector
            index++;
            i = 0;
            break;
        }
    }
}

void Game::choosePaths(string file_name){
    int index = 0;
    int path;
    string advisor, advisor1, advisor2;
    string line;
    int num_adv_opt = 5; // number of current advisor choices

    ifstream advisors_file(file_name);// opens a file

    if (advisors_file.fail()){
        cout << "Could not open file." << endl; // or something else went wrong opening the file
        return;
    }

    while(getline(advisors_file, line)){ // puts lines in advisor file into _advisor_options vector
        _advisor_options.push_back(line); // FIGURE OUT POWERS
    }

    for(index = 0; index < 2; index++){
        cout << "Choose a Path Number (Player " << index + 1 << "):" << endl;
        cout << "1. Mission" << endl;
        cout << "2. Minion Training" << endl;
        cout << endl;
        cout << "Player " << index + 1 << " Path: ";
        cin >> path;
        cout << endl;

        if((path != 1)&&(path != 2)){ // INFINITE LOOP IF PRESS WRONG THING????
            while((path != 1)&&(path != 2)){
                cout << "Invalid path number. Please choose option 1 or 2: " << endl;
                cout << endl;
                cout << "Player " << index + 1 << " Path: ";
                cin >> path;
                cout << endl;
            }
        }
        
        _players[index].setPath(path - 1); // sets player path in Player objects in _players array but changes it to index instead of number so Board can more easily be used

        if(path == 1){ // Stats change if path chosen is Mission
            _players[index].setStamina(_players[index].getStamina() + 200);
            _players[index].setStrength(_players[index].getStrength() + 200);
            _players[index].setSmarts(_players[index].getSmarts() + 200);
            _players[index].setMinionPoints(_players[index].getMinionPoints() + 5000);
        }
        else if(path == 2){ //Stats change if path chosen is Minion Training
            _players[index].setStamina(_players[index].getStamina() + 500);
            _players[index].setStrength(_players[index].getStrength() + 500);
            _players[index].setSmarts(_players[index].getSmarts() + 1000);
            _players[index].setMinionPoints(_players[index].getMinionPoints() - 5000);

            cout << "Since you chose Minion Training, you must choose an advisor to guide you throughout your training. Please choose your advisor: " << endl;
            cout << endl;

            for(int i = 0; i < num_adv_opt; i++){ //Prints out _advisor_options vector
                cout << _advisor_options[i] << endl;
            }

            cout << endl;
            cin >> advisor1 >> advisor2;
            advisor = advisor1 + " " + advisor2;
            cout << endl;

            if((advisor != "Felonius Gru")&&(advisor != "Master Chow")&&(advisor != "Silas Ramsbottom")&&(advisor != "Dr. Nefario")&&(advisor != "Lucy Wilde")){
                while((advisor != "Felonius Gru")&&(advisor != "Master Chow")&&(advisor != "Silas Ramsbottom")&&(advisor != "Dr. Nefario")&&(advisor != "Lucy Wilde")){
                    cout << "Invalid advisor name. Please choose an advisor from the list above." << endl;
                    cout << endl;
                    cin >> advisor1 >> advisor2;
                    advisor = advisor1 + " " + advisor2;
                }
            }
            _players[index].setAdvisor(advisor); //Sets chosen advisor to _advisor in Player
            
            // Deletes chosen advisor from advisor options
            if(advisor == "Felonius Gru"){
                _advisor_options.erase(_advisor_options.begin() + 0);
            }
            else if(advisor == "Dr. Nefario"){
                _advisor_options.erase(_advisor_options.begin() + 1);
            }
            else if(advisor == "Silas Ramsbottom"){
                _advisor_options.erase(_advisor_options.begin() + 2);
            }
            else if(advisor == "Master Chow"){
                _advisor_options.erase(_advisor_options.begin() + 3);
            }
            else if(advisor == "Lucy Wilde"){
                _advisor_options.erase(_advisor_options.begin() + 4);
            }
            num_adv_opt--;
        }
    }
}

int Game::getPlayerIndex(){
    return player_index;
}

void Game::changePlayerIndex(){
    if(player_index == 0){
        player_index++;
    }
    else if(player_index == 1){
        player_index--;
    }
}

/*A bunch of if-else statements that do things depending on what color is landed on*/
void Game::whatTileDo(char color){
    if(color == 'R'){ // Rogue gadget tile: loose 100 in each Skill and go back 10 spaces

        // Resets stats
        _players[getPlayerIndex()].setStamina(_players[getPlayerIndex()].getStamina() - 100);
        _players[getPlayerIndex()].setStrength(_players[getPlayerIndex()].getStrength() - 100);
        _players[getPlayerIndex()].setSmarts(_players[getPlayerIndex()].getSmarts() - 100);

        cout << "Oh no! You've landed on a Red tile. You've been blasted by a rogue gadget, leaving you dazed and winded. You've lost 100 Stamina, 100 Strength, and 100 Smarts and must move back 10 spaces." << endl;

        _players[getPlayerIndex()].setPosition(board.getPlayerPosition(getPlayerIndex()) - 10);
        board.setPlayerPosition(getPlayerIndex(), board.getPlayerPosition(getPlayerIndex()) - 10);

        // Displays the new board with player moved 10 spaces back
        board.displayBoard(_players[getPlayerIndex()].getPath(), _players[0], _players[1]);
    }
    else if(color == 'G'){ // Regular tile: 50% change of random event
        int chance1, chance2, pos_rand, neg_rand;
        chance1 = (rand() % 2); // 50% chance of random event being triggered
        chance2 = (rand() % 5); // Chance of event being positive or negative
        pos_rand = (rand() % 30); // Which positive event you get
        neg_rand = (rand() % 20); // Which negative event you get

        Random_Events();

        if(chance1 == 1){ // Random event occurs
            cout << "Random Event: ";
            if((chance2 >= 0)&&(chance2 <= 2)){
                while(_positive_events[pos_rand].path != _players[getPlayerIndex()].getPath()){
                    pos_rand = (rand() % 30);
                }
                cout << _positive_events[pos_rand].event << " (" << _positive_events[pos_rand].minion_points << " Minion Points!)" << endl; 
                _players[getPlayerIndex()].setMinionPoints(_players[getPlayerIndex()].getMinionPoints() + _positive_events[pos_rand].minion_points);
            }
            else if((chance2 == 3)||(chance2 == 4)){
                while(_negative_events[neg_rand].path != _players[getPlayerIndex()].getPath()){
                    neg_rand = (rand() % 20);
                }
                // None (0), Felonius Gru (1), Dr. Nefario (2), Silas Ramsbottom (3), Master Chow (4), and Lucy Wilde (5)
                cout << _negative_events[neg_rand].event << " (-" << _negative_events[neg_rand].minion_points << " Minion Points!)" << endl;
                if((_negative_events[neg_rand].advisor == 1)&&(_players[getPlayerIndex()].getAdvisor() == "Felonius Gru")){
                    cout << "But since you have Felonius Gru as your advisor, you were protected from the negative event so no Minion Points were lost!" << endl;
                }
                else if((_negative_events[neg_rand].advisor == 2)&&(_players[getPlayerIndex()].getAdvisor() == "Dr. Nefario")){
                    cout << "But since you have Dr. Nefario as your advisor, you were protected from the negative event so no Minion Points were lost!" << endl;
                }
                else if((_negative_events[neg_rand].advisor == 3)&&(_players[getPlayerIndex()].getAdvisor() == "Silas Ramsbottom")){
                    cout << "But since you have Silas Ramsbottom as your advisor, you were protected from the negative event so no Minion Points were lost!" << endl;
                }
                else if((_negative_events[neg_rand].advisor == 4)&&(_players[getPlayerIndex()].getAdvisor() == "Master Chow")){
                    cout << "But since you have Master Chow as your advisor, you were protected from the negative event so no Minion Points were lost!" << endl;
                }
                else if((_negative_events[neg_rand].advisor == 5)&&(_players[getPlayerIndex()].getAdvisor() == "Lucy Wilde")){
                    cout << "But since you have Lucy Wilde as your advisor, you were protected from the negative event so no Minion Points were lost!" << endl;
                }
                else{
                _players[getPlayerIndex()].setMinionPoints(_players[getPlayerIndex()].getMinionPoints() - _negative_events[neg_rand].minion_points);
                }
            }
        }

    }
    else if(color == 'B'){ // Banana Tile: gain 200 in each skill and get another turn
        // Resets stats
        _players[getPlayerIndex()].setStamina(_players[getPlayerIndex()].getStamina() - 100);
        _players[getPlayerIndex()].setStrength(_players[getPlayerIndex()].getStrength() - 100);
        _players[getPlayerIndex()].setSmarts(_players[getPlayerIndex()].getSmarts() - 100);

        cout << "You've landed on a Banana Tile! You've found a banana to refuel you on your journey. You gain 200 points in all Skills and get another turn!" << endl;
        cout << endl;
        MainMenu();
    }
    else if(color == 'U'){ // Purple Tile: Challenge/Riddle Tile
        // Need to read riddles.txt
        string answer;
        int random_num = (rand()% 27);
        Riddles();
        
        cout << "You've landed on a challenge tile. Time to test your knowledge with a riddle! If you get it correct, you get 500 Smarts points." << endl;
        cout << endl;
        cout << "Solve this riddle:" << endl;
        cout << _riddles[random_num].riddle << endl;
        cin >> answer;
        cout << endl;

        if(answer == _riddles[random_num].answer){
            _players[getPlayerIndex()].setSmarts(_players[getPlayerIndex()].getSmarts() + 500);
            cout << "Correct! You earn 500 Smarts points!" << endl;
        }
        else{
            cout << "Sorry, that's incorrect. The correct answer was " << _riddles[random_num].answer << "." << endl;
        }
    }
    else if(color == 'N'){ // Brown/Villain Tile: dragged back to where you were last and subtract 300 stamina

        // Subtracts from stamina
        _players[getPlayerIndex()].setStamina(_players[getPlayerIndex()].getStamina() - 300);
        cout << "Oh no! You've encountured a villain and had an epic battle, but unfortunately you lost. They've dragged you back to where you were last, and your Stamina has decreased by 300 points." << endl;

        // Changes position back to last spot
        _players[getPlayerIndex()].setPosition(getLastSpot());
        board.setPlayerPosition(getPlayerIndex(), getLastSpot());

        // Displays the new board with player moved back to where they were before
        board.displayBoard(_players[getPlayerIndex()].getPath(), _players[0], _players[1]);

    }
    else if (color == 'P'){ // Pink Tile: Choose an advisor and all skills increase by 300 points
        string advisor, advisor1, advisor2;
        int n = _advisor_options.size();

        // Adds to stats
        _players[getPlayerIndex()].setStamina(_players[getPlayerIndex()].getStamina() + 300);
        _players[getPlayerIndex()].setStrength(_players[getPlayerIndex()].getStrength() + 300);
        _players[getPlayerIndex()].setSmarts(_players[getPlayerIndex()].getSmarts() + 300);

        cout << "You've landed on an advisor tile. This means you've gained 300 points in all Skills, and you can choose a new advisor. If you do not want a new advisor, simply type 'No advisor'." << endl;
        cout << endl;
        cout << "Here are the available advisors:" << endl;
        for (int i = 0; i < n; i++){
            cout << _advisor_options[i] << endl;
        }

        cout << endl;
        cin >> advisor1 >> advisor2;
        advisor = advisor1 + " " + advisor2;
        cout << endl;

        if((advisor != "Felonius Gru")&&(advisor != "Master Chow")&&(advisor != "Silas Ramsbottom")&&(advisor != "Dr. Nefario")&&(advisor != "Lucy Wilde")&&(advisor != "No advisor")){
            while((advisor != "Felonius Gru")&&(advisor != "Master Chow")&&(advisor != "Silas Ramsbottom")&&(advisor != "Dr. Nefario")&&(advisor != "Lucy Wilde")&&(advisor != "No advisor")){
                cout << "Invalid advisor name. Please choose an advisor from the list above." << endl;
                if(advisor == "No advisor"){
                    return;
                }
                cout << endl;
                cin >> advisor1 >> advisor2;
                advisor = advisor1 + " " + advisor2;
                cout << endl;
            }
        }
        if(advisor == "No advisor"){
            return;
        }

        // Adds player's older advisor back to _advisor_options vector
        if(_players[getPlayerIndex()].getAdvisor() == "Felonius Gru"){
            _advisor_options.push_back("Felonius Gru - Helps you with villainy");
        }
        else if(_players[getPlayerIndex()].getAdvisor() == "Dr. Nefario"){
            _advisor_options.push_back("Dr. Nefario - Helps you learn and make gadgets");
        }
        else if(_players[getPlayerIndex()].getAdvisor() == "Silas Ramsbottom"){
            _advisor_options.push_back("Silas Ramsbottom - Helps you combat problems with the Anti-Villain League");
        }
        else if(_players[getPlayerIndex()].getAdvisor() == "Master Chow"){
            _advisor_options.push_back("Master Chow - Trains you to fight");
        }
        else if(_players[getPlayerIndex()].getAdvisor() == "Lucy Wilde"){
            _advisor_options.push_back("Lucy Wilde - Helps you with moral");
        }
        
        _players[getPlayerIndex()].setAdvisor(advisor); //Sets chosen advisor to _advisor in Player
        
        int index_a = 0;
        n = _advisor_options.size();
        // Deletes chosen advisor from advisor options
        //THIS DOESN'T ACTUALLY WORK BECAUSE THEY CHANGE SPOTS WHEN CHOSEN
        if(advisor == "Felonius Gru"){
            for(index_a = 0; index_a < n; index_a++){
                if(_advisor_options[index_a] == "Felonius Gru - Helps you with villainy"){
                    _advisor_options.erase(_advisor_options.begin() + index_a);
                }
            }
        }
        else if(advisor == "Dr. Nefario"){
            for(index_a = 0; index_a < n; index_a++){
                if(_advisor_options[index_a] == "Dr. Nefario - Helps you learn and make gadgets"){
                    _advisor_options.erase(_advisor_options.begin() + index_a);
                }
            }
        }
        else if(advisor == "Silas Ramsbottom"){
            for(index_a = 0; index_a < n; index_a++){
                if(_advisor_options[index_a] == "Silas Ramsbottom - Helps you combat problems with the Anti-Villain League"){
                    _advisor_options.erase(_advisor_options.begin() + index_a);
                }
            }
        }
        else if(advisor == "Master Chow"){
            for(index_a = 0; index_a < n; index_a++){
                if(_advisor_options[index_a] == "Master Chow - Trains you to fight"){
                    _advisor_options.erase(_advisor_options.begin() + index_a);
                }
            }
        }
        else if(advisor == "Lucy Wilde"){
            for(index_a = 0; index_a < n; index_a++){
                if(_advisor_options[index_a] == "Lucy Wilde - Helps you with moral"){
                    _advisor_options.erase(_advisor_options.begin() + index_a);
                }
            }
        }
        
    }
}

/*Reads the riddles.txt file and puts it into _riddles array so it can be used in whatTileDo function for Purple Challenge Tile*/
void Game::Riddles(){
    // Need to read riddles.txt
    int size = 2;
    string line_arr[2];
    string line;
    Riddle riddle_line;
    int index_r = 0;


    ifstream riddles_file("riddles.txt");// opens a file

    if (riddles_file.fail()){
        cout << "Could not open file." << endl; // or something else went wrong opening the file
        return;
    }

    getline(riddles_file, line); // reads first line in riddles.txt file
    while(getline(riddles_file, line)){ // puts lines in riddles file into riddles array
        split(line, '|', line_arr, size); // splits line into line_arr
        riddle_line.riddle = line_arr[0]; // sets first space in line_arr to riddle in riddle struct
        riddle_line.answer = line_arr[1]; // sets second space in line_arr to answer in riddle struct
        _riddles[index_r] = riddle_line; // sets Riddle we created into spot in riddles array
        index_r++;
    }
}

/*Reads the random_positive_events.txt and random_negative_events.txt files and puts it into _positive_events and _negaitve_events array so it can be used in whatTileDo function for Green Random Tiles*/
void Game::Random_Events(){
    // Need to read random_events.txt
    int size = 4;
    string positive[4];
    string negative[4];
    string line;
    RandomEvents events_line;
    int index_p = 0;
    int index_n = 0;

    // Reading and storing positive events file into _positive_events array
    ifstream random_events_file1("random_positive_events.txt");// opens a file

    if (random_events_file1.fail()){
        cout << "Could not open file." << endl; // or something else went wrong opening the file
        return;
    }

    getline(random_events_file1, line); // reads first line in random_positive_events.txt file
    getline(random_events_file1, line);
    while(getline(random_events_file1, line)){ // puts lines in random_positive_events file into positive array
        split(line, '|', positive, size); // splits line into positive array
        events_line.event = positive[0]; 
        events_line.path = stoi(positive[1]); 
        events_line.advisor = stoi(positive[2]);
        events_line.minion_points = stoi(positive[3]);
        _positive_events[index_p] = events_line; // sets RandomEvents we created into spot in _positive_events array
        index_p++;
    }

    // Reading and storing negative events file into _negative_events array
    ifstream random_events_file2("random_negative_events.txt");// opens a file

    if (random_events_file2.fail()){
        cout << "Could not open file." << endl; // or something else went wrong opening the file
        return;
    }

    getline(random_events_file2, line); // reads first line in random_negative_events.txt file
    getline(random_events_file2, line);
    while(getline(random_events_file2, line)){ // puts lines in random_negative_events file into negative array
        split(line, '|', negative, size); // splits line into negative array
        events_line.event = negative[0]; 
        events_line.path = stoi(negative[1]); 
        events_line.advisor = stoi(negative[2]);
        events_line.minion_points = stoi(negative[3]);
        _negative_events[index_n] = events_line; // sets RandomEvents we created into spot in _negative_events array
        index_n++;
    }
}

int Game::getLastSpot(){
    return _last_spot;
}

void Game::setLastSpot(int last_spot){
    _last_spot = last_spot;
}