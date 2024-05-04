#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;

class Monster: public GameCharacter
{
private:
    string property;
public:
    Monster();
    Monster(string,int,int,int,string);
    //Monster::Monster( string n, int chp, int a, int d,  string prop)


    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);
    void setprop(string);
    virtual int cal_defval(int);
    virtual int cal_atkval(int);
    string getprop();
};

class Boss : public Monster {
private:
    vector<string> script;
    bool isdefeated;
    vector<Skill> skills;

public:
    Boss();
    Boss( string tname, int chp, int a, int d,  vector<Skill> tskills);

    void setscript(vector<string> temp);
    vector<string> getscript() ;
    void addscript(string temp);
    void setdefeated(bool temp);
    bool getdefeated();
    vector<Skill> getskill();
    void addskill(Skill);
    void setskill(vector<Skill>);
    void printStatus();
    bool triggerEvent(Object* obj) ;

    int cal_attackval(int skill_index) ;
    int cal_defval(int skill_index) ;
};



#endif // ENEMY_H_INCLUDED
