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
}

bool Monster::triggerEvent(Object* obj) {
    Player* player = dynamic_cast<Player*>(obj);  
    if (this->checkIsDead()) {
        return false;  // If monster is dead, end event
    }
    if (player->checkIsDead()) {
        return false;  // If player is dead, end event
    }

    // Example combat interaction
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
                if (player_property == "water") modifier = 1.5f;
                else if (player_property == "fire") modifier = 0.8f;
            }

            damage *= modifier;
            player->setMP(player->getMP() - player->getskill()[choice].getCost());
            setCurrentHealth((getCurrentHealth() - static_cast<int>(damage)) >= 0 ? getCurrentHealth() - static_cast<int>(damage) : 0);
        }
    }
    else if (choice == skill_count) {  // Check current status
        player->printStatus();
        this->printStatus();
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

    // Monster's counter-attack logic
    if (!checkIsDead()) {  // If monster's still alive
        srand(static_cast<unsigned int>(time(0)));
        int attack_choice = rand() % (skill_count);  // Random attack
        float damage = cal_atkval(attack_choice) - player->cal_defval(0);

        if (damage > 0) {
            player->setCurrentHealth((player->getCurrentHealth() - static_cast<int>(damage)) >= 0 ?
                player->getCurrentHealth() - static_cast<int>(damage) : 0);
        }
        else {
            cout << "The attack had no effect!" << endl;
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
    setName(tname); setCurrentHealth(chp); setMaxHealth(chp); setAttack(a); setDefense(d); 
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
    Player* player = dynamic_cast<Player*>(obj);
    if (this->checkIsDead()) {  // If the boss is defeated
        return false;  // End the event
    }

    int choice;
    cout << "---------------------------------------" << endl;

    for (int i = 0; i < player->getskill().size(); i++) {
        cout << i << ". Using " << player->getskill()[i].getname()
            << " (cost: " << player->getskill()[i].getCost() << ")" << endl;
    }

    cout << player->getskill().size() << ". Check status" << endl;
    cout << (player->getskill().size() + 1) << ". Use items" << endl;
    cout << (player->getskill().size() + 2) << ". Flee" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice < player->getskill().size()) {  // If using a skill
        if (player->getMP() < player->getskill()[choice].getCost()) {
            cout << "Not enough MP!" << endl;
            return true;  // Continue the event
        }

        float damage = player->cal_attackval(choice) - cal_defval(0);
        player->setMP(player->getMP() - player->getskill()[choice].getCost());

        float modifier = 1.0f;
        if (getprop() == "fire" && player->getskill()[choice].getProperty() == "water") {
            modifier = 1.5f;
        }

        damage *= modifier;
        setCurrentHealth((getCurrentHealth() - static_cast<int>(damage)) >= 0 ? getCurrentHealth() - static_cast<int>(damage) : 0);
    }
    else if (choice == player->getskill().size()) {  // Check status
        player->printStatus();
        printStatus();
        return true;  // Continue the event
    }
    else if (choice == player->getskill().size() + 1) {  // Use items
        player->triggerEvent(player);
        return true;  // Continue the event
    }
    else if (choice == player->getskill().size() + 2) {  // Flee
        cout << "Fleeing from combat." << endl;
        player->setmoney((player->getmoney() - 5 > 0) ? player->getmoney() - 5 : 0);
        return false;  // End the event
    }

    // Boss attacks back
    if (!checkIsDead()) {
        int boss_attack = cal_attackval(0);
        player->setCurrentHealth((player->getCurrentHealth() - boss_attack) >= 0 ?
            player->getCurrentHealth() - boss_attack : 0);
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
    if (skill_index != -1) { //if not chosing skills*, it has to be -1
        //then the option is 0~n
        if (skills[skill_index].getImpactType() == "defense") {
            total += skills[skill_index].getValue();
        }
    }
    return total;
}
