#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;
class Food;
class Goods;

class Item: public Object
{
private:
    int health; int attack; int defense;
public:
    Item();
    Item(string, int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    virtual bool triggerEvent(Object*);
    //virtual bool pickup(Object*);
    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
};

class Goods : public Item {
private:
    int price;
    string type; // weapon, armor, helmet spell, ....
public:
    Goods();
    Goods(string n, int h, int a, int d, int p, string t, string ttag);
    //bool triggerEvent(Object*);
    void setType(string temp) {
        this->type = temp;
    }
    string getType() {
        return this->type;
    }
    int getprice() {
        return this->price;
    }
    void setprice(int temp) {
        this->price = temp;
    }
    bool triggerEvent(Object* obj);

};

class Food : public Item {
private:
    int price;
    int hungerVal;
    int thirstVal;
public:
    Food();
    Food(string tname, int p, int hv, int tv, string ttag);

    bool triggerEvent(Object* obj);

    // getter ©M setter
    int getprice() { return price; }
    void setprice(int temp) { price = temp; }

    int gethun() { return hungerVal; }
    void sethun(int val) { hungerVal = val; }

    int getthr() { return thirstVal; }
    void setthr(int val) { thirstVal = val; }
};
#endif // ITEM_H_INCLUDED
