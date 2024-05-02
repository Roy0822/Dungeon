#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include <thread>
#include <chrono>

using namespace std;
class Boss;
class Dungeon{
private:
    Player player; // Player object representing the adventurer
    Boss* finalboss; // Final boss in the dungeon
    std::vector<std::vector<Room>> rooms; // 2D array of rooms in the dungeon
    std::vector<Room*> historyRoom; // Tracks the history of rooms visited
    int isWin; // Flag to track if the player has won

public:
    Dungeon();
    // Methods to create the player and the map
    void createPlayer();
    void createMap();

    // Method to print the map
    void printMap();

    // Methods to handle player actions and game logic
    void handleMovement(); // Manage player movement
    void handleEvent(Object* curobj); // Manage interactions in the current room
    void startGame(); // Start the game with initial setup
    void chooseAction(); // Display action options to the player
    bool checkGameLogic(); // Check if the game should end
    void runDungeon(); // Main game loop

};


#endif // DUNGEON_H_INCLUDED
