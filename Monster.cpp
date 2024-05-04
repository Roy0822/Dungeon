#include "Monster.h"
#include "Player.h"
#include <iostream>
using namespace std;
Monster::Monster() {
    setprop("");
}
Monster::Monster(const string n, int chp, int a, int d, const string prop) {
    setName(n);
    setTag("monster");
    setCurrentHealth(chp);
    setMaxHealth(chp);
    setAttack(a);
    setDefense(d);
    setprop(prop);
}

bool Monster::triggerEvent(Object* obj) {
    Player* player = dynamic_cast<Player*>(obj);  
    if (this->checkIsDead()) {
        cout << "You defeated " << getName() << "!\n";

        return false;  // If monster is dead, end event
    }
    if (player->checkIsDead()) {
        return false;  // If player is dead, end event
    }

    // Example combat interaction
    cout << "---------------------------------------" << endl;
    printStatus();
    cout << "---------------------------------------" << endl;

    int skill_count = static_cast<int>(player->getskill().size());
    for (int i = 0; i < skill_count; ++i) {
        cout << i << ". Using " << player->getskill()[i].getname()
            << " (property: " << player->getskill()[i].getProperty()
            << ", cost: " << player->getskill()[i].getCost() << ")" << endl;
    }

    cout << skill_count << ". Check current status" << endl;  // Option to check status
    cout << skill_count + 1 << ". Use items" << endl;  // Option to use items
    cout << skill_count + 2 << ". Flee" << endl;  // Option to flee
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice < skill_count) {  // If using a skill
        if (checkIsDead()) {
            cout << "You defeated " << getName()<< "!\n";
            return 0;
        }
        if (player->getMP() - player->getskill()[choice].getCost() < 0) {

            cout << "You do not have enough MP. Try a normal attack!" << endl;
            return true;
        }
        else {
            float damage = player->cal_attackval(choice) - cal_defval(0);  // Monster's defense

            float modifier = 1.0f;
            string player_property = player->getskill()[choice].getProperty();

            // Determine element advantage or disadvantage
            if (getprop() == "fire") {
                if (player_property == "water") modifier = 1.5f;
                else if (player_property == "ground") modifier = 0.8f;
            }
            else if (getprop() == "water") {
                if (player_property == "ground") modifier = 1.5f;
                else if (player_property == "fire") modifier = 0.8f;
            }
            else if (getprop() == "ground") {
                if (player_property == "fire") modifier = 1.5f;
                else if (player_property == "water") modifier = 0.8f;
            }
            damage *= modifier;
            player->setMP(player->getMP() - player->getskill()[choice].getCost());
            setCurrentHealth((getCurrentHealth() - static_cast<int>(damage)) >= 0 ? getCurrentHealth() - static_cast<int>(damage) : 0);
            checkIsDead();
        }
    }
    else if (choice == skill_count) {  // Check current status
        player->printStatus();
        //this->printStatus();
        return true;  // Continue the event
    }
    else if (choice == skill_count + 1) {  // Use items
        bool isFinish = player->triggerEvent(player);
        return true;  // Continue the event
    }
    else if (choice == skill_count + 2) {  // Flee
        cout << "You flee from combat." << endl;
        player->setmoney((player->getmoney() - 5 > 0) ? player->getmoney() - 5 : 0);  // Deduct money for fleeing
        return false;  // End the event
    }
    if (checkIsDead()) {
        player->setmoney(player->getmoney() + 20);
        return 0;
    }

    // Monster's counter-attack logic
    if (!checkIsDead()) {  // If monster's still alive
        int mst_dmg = getAttack() - player->cal_defval(choice) >= 0 ? getAttack() - player->cal_defval(choice) : 0;
        if (mst_dmg > 0) {
            player->setCurrentHealth(player->getCurrentHealth() - mst_dmg >= 0 ? player->getCurrentHealth() - mst_dmg : 0);

        }
        
    }

    return true;  // Continue the event
}

int Monster::cal_atkval(int skill_index) {
    return getAttack();
}

int Monster::cal_defval(int skill_index) {
    return getDefense();
}

string Monster::getprop() {
    return property;
}

void Monster::setprop(string tprop) {
    property = tprop;
}


Boss::Boss() {
    setdefeated(0); return;
}
Boss::Boss(string tname, int chp, int a, int d, vector<Skill> tskills) {
    setName(tname); setCurrentHealth(chp); setMaxHealth(chp); setAttack(a); setDefense(d); setdefeated(0);
}
vector<Skill> Boss::getskill() {
    return skills;
}
void Boss::addskill(Skill temp){
    skills.push_back(temp);
}
void Boss::setskill(vector<Skill>temp) {
    skills = temp;
}
void Boss::setscript(vector<string> temp) {
    script = temp;
}
vector<string> Boss::getscript() {
    return script;
}
void Boss::addscript(string temp) {
    script.push_back(temp);
}
void Boss::setdefeated(bool temp) {
    isdefeated = temp;
}
bool Boss::getdefeated() {
    return isdefeated;
}

bool Boss::triggerEvent(Object* obj) {
    //printStatus();
    Player* player = dynamic_cast<Player*>(obj);
    if (this->checkIsDead()) {
        cout << "You defeated " << getName() << "!\n";

        return false;  // If monster is dead, end event
    }
    if (player->checkIsDead()) {
        return false;  // If player is dead, end event
    }

    // Example combat interaction
    cout << "---------------------------------------" << endl;
    printStatus();
    cout << "---------------------------------------" << endl;

    int skill_count = static_cast<int>(player->getskill().size());
    for (int i = 0; i < skill_count; ++i) {
        cout << i << ". Using " << player->getskill()[i].getname()
            << " (property: " << player->getskill()[i].getProperty()
            << ", cost: " << player->getskill()[i].getCost() << ")" << endl;
    }

    cout << skill_count << ". Check current status" << endl;  // Option to check status
    cout << skill_count + 1 << ". Use items" << endl;  // Option to use items
    cout << skill_count + 2 << ". Flee" << endl;  // Option to flee
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice < skill_count) {  // If using a skill

        if (checkIsDead()) {
            cout << "You defeated " << getName() << "!\n";
            return 0;
        }

        if (player->getMP() - player->getskill()[choice].getCost() < 0) {

            cout << "You do not have enough MP. Try a normal attack!" << endl;
            return true;
        }

        else {

            float damage = (int)player->cal_attackval(choice) - (int)cal_defval(0);  // Monster's defense


            float modifier = 1.0f;
            string player_property = player->getskill()[choice].getProperty();


            // Determine element advantage or disadvantage
            if (getprop() == "fire") {
                if (player_property == "water") modifier = 1.5f;
                else if (player_property == "ground") modifier = 0.8f;
            }

            else if (getprop() == "water") {
                if (player_property == "ground") modifier = 1.5f;
                else if (player_property == "fire") modifier = 0.8f;
            }
            else if (getprop() == "ground") {
                if (player_property == "fire") modifier = 1.5f;
                else if (player_property == "water") modifier = 0.8f;
            }

            damage *= modifier;
            player->setMP(player->getMP() - player->getskill()[choice].getCost());
            setCurrentHealth((getCurrentHealth() - static_cast<int>(damage)) >= 0 ? getCurrentHealth() - static_cast<int>(damage) : 0);

            //checkIsDead();
        }
    }
    else if (choice == skill_count) {  // Check current status
        player->printStatus();
        //this->printStatus();
        return true;  // Continue the event
    }
    else if (choice == skill_count + 1) {  // Use items
        bool isFinish = player->triggerEvent(player);
        return true;  // Continue the event
    }
    else if (choice == skill_count + 2) {  // Flee
        cout << "You flee from combat." << endl;
        player->setmoney((player->getmoney() - 5 > 0) ? player->getmoney() - 5 : 0);  // Deduct money for fleeing
        return false;  // End the event
    }
    if (checkIsDead()) {

        return 0;
    }

    // Monster's counter-attack logic
    if (!checkIsDead()) {  // If monster's still alive
        int mst_dmg = getAttack() - player->cal_defval(choice) >= 0 ? getAttack() - player->cal_defval(choice) : 0;
        if (mst_dmg > 0) {
            player->setCurrentHealth(player->getCurrentHealth() - mst_dmg >= 0 ? player->getCurrentHealth() - mst_dmg : 0);

        }

    }

    return true;  // Continue the event
}


int Boss::cal_attackval(int skill_index) {
    int total = this->getAttack();
    if (skill_index != -1) { //if not chosing skills*, it has to be -1
        //then the option is 0~n
        if (skills[skill_index].getImpactType() == "attack") {
            total += skills[skill_index].getValue();
        }
    }
    return total;
}
int Boss::cal_defval(int skill_index) {
    int total = this->getDefense();
    if (this->getCurrentHealth() / 200 < 0.5) total *= 2;
    return total;
}
void Boss::printStatus() {
    cout << "---------------------------------------" << endl;
    cout << getTag() << ": " << getName() << "'s Conditions: " << endl;
    cout << "Health: " << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "Attack: " << getAttack() << endl;
    cout << "Defense: " << getDefense() << endl;
    
    for (int i = 0; i < skills.size(); i++) {
        cout << "Skill " << i << ": " << skills[i].getname() << "  "
            << "Property: " << skills[i].getProperty() << endl;
    }
    
}
