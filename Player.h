#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;
class Condition;
class Food;
class Skill;
class Goods;

class Player : public GameCharacter {
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Condition*> conditions;
    vector<Food*> foods;
    vector<Skill> skills;
    Goods* helmet;
    Goods* weapon;
    Goods* armor;
    int money;
    int thirst;
    int hunger;
    int MP;

public:
    // ructors
    Player();
    Player(string,int,int,int,int,int,int,int); // string name, int mp, int health, int attack, int defense, int hg, int thr, int mny

    // Methods
    void addItem(Food* temp);
    void changeRoom(Room* nextRoom);
    bool triggerEvent(Object*);  // Use items
    int cal_attackval(int skill_index);
    int cal_defval(int skill_index);
    void printStatus();
    void refreshStatus();

    // Setters and getters
    Goods* getHelmet() ;
    void setHelmet(Goods* temp);

    Goods* getWeapon() ;
    void setWeapon(Goods* temp);

    void addskill(Skill temp);
    vector<Skill> getskill() ;

    Goods* getArmor() ;
    void setArmor(Goods* temp);

    Room* getCurrentRoom() ;
    void setCurrentRoom(Room* temp);

    Room* getPreviousRoom() ;
    void setPreviousRoom(Room* temp);

    void setfoods(vector<Food*> temp);
    vector<Food*> getfoods();
    void addfoods(Food* temp);
    void setMP(int tmp);
    int getMP() ;

    void setTHR(int thirst);
    int getTHR() ;

    void setHG(int hunger);
    int getHG() ;

    vector<Condition*> getCondition() ;
    void addCondi(Condition* tempcondi);

    int getmoney();
    void setmoney(int temp);

    void pickupItem(Item*);


};

class Condition : public Object {
private:
    string impact_on_type;
    int value;

public:
    // ructors
    Condition();
    Condition(string n, string type, int val);
    bool triggerEvent(Object* obj);
    // Setters and getters
    void setImpactType(string ttype);
    string getImpactType() ;

    int getValue() ;
    void setValue(int tval);
};
class Skill {
private:
    string impact_on_type;
    int value;
    string property;
    int costmp;
    string name;
public:
    Skill() { setCost(0); setValue(0); }
    Skill(string tn, string prop, int val, string ontype) : name(tn), property(prop), value(val), impact_on_type(ontype), costmp(0) { }
    Skill(string tn, string prop, int val, string ontype, int cost) : name(tn), property(prop), value(val), impact_on_type(ontype), costmp(cost) { }
    void setname(string temp) {
        this->name = temp;
    }
    string getname() {
        return this->name;
    }
    void setImpactType(string ttype) {
        this->impact_on_type = ttype;
    }
    string getImpactType()  {
        return this->impact_on_type;
    }
    int getValue()  {
        return this->value;
    }
    void setValue(int tval) {
        this->value = tval;
    }
    void setProperty(string tppt) {
        this->property = tppt;
    }
    string getProperty()  {
        return this->property;
    }
    int getCost() {
        return this->costmp;
    }
    void setCost(int cost) {
        this->costmp = cost;
    }
    friend class Condition;
};
#endif // PLAYER_H_INCLUDED
