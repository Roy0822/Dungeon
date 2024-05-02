#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class NPC : public Object {
private:
    vector<string> script;   // Dialogue script for the NPC
    vector<Goods*> commodities;  // Goods the NPC offers
    vector<Food*> foods;         // Food items the NPC offers
    bool isInteract;                  // Flag to track if NPC has interacted with the player

public:
    // ructors
    NPC(); // Default constructor
    NPC(string n, vector<string> tscript, vector<Goods*> commodities); // Constructor with scripts and commodities
    NPC(string n, vector<string> tscript); // Constructor with just scripts
    NPC(string n, vector<Goods*> commodities, vector<Food*> foodie); // Constructor with commodities and food

    // Virtual function for NPC interaction with a Player
    bool triggerEvent(Object* obj);

    // Setters and getters
    void setScript(vector<string> temp); // Set script
    vector<string> getScript();           // Get script

    void setCom(vector<Goods*> temp);         // Set commodities
    vector<Goods*> getCom();                  // Get commodities

    void setfood(vector<Food*> temp);         // Set foods
    vector<Food*> getfood() ;                  // Get foods

    bool getIsinteract() ;                           // Check if interacted
    void setIsinteract(bool temp);                        // Set interaction flag
};




#endif // NPC_H_INCLUDED
