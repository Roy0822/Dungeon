#include "GameCharacter.h"
GameCharacter::GameCharacter() {
    setAttack(0); setCurrentHealth(0); setDefense(0); setName(""); setTag("");
}

GameCharacter::GameCharacter(string n, string tag, int c, int a, int d) : Object(n, tag),
currentHealth(c), maxHealth(c), attack(a), defense(d) { }

int GameCharacter::cal_atkval(int skill_index) {
    int total = attack;
    /*
    if (skill_index != -1) { //if not chosing skills*, it has to be -1
        //then the option is 0~n
        if (skills[skill_index].getImpactType() == "attack") {
            total += skills[skill_index].getValue();
        }
    }
    */
    return total;
}
int GameCharacter::cal_defval(int skill_index) {
    int total = defense;
    /*
    if (skill_index != -1) { //if not chosing skills*, it has to be -1
        //then the option is 0~n
        if (skills[skill_index].getImpactType() == "defense") {
            total += skills[skill_index].getValue();
        }
    }
    */
    return total;
}

void GameCharacter::printStatus() {
    cout << "---------------------------------------" << endl;
    cout << getTag() << ": " << getName() << "'s Conditions: " << endl;
    cout << "Health: " << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "Attack: " << getAttack() << endl;
    cout << "Defense: " << getDefense() << endl;
    /*
    for (int i = 0; i < skills.size(); i++) {
        cout << "Skill " << i << ": " << skills[i].getname() << "  "
            << "Property: " << skills[i].getProperty() << endl;
    }
    */
}


bool GameCharacter::checkIsDead() {
    return (this->currentHealth <= 0) ? true : false;
}
int GameCharacter::takeDamage(int t) {
    this->currentHealth -= t;
    return this->currentHealth;
}
/* Set & Get function*/

void GameCharacter::setMaxHealth(int t) {
    this->maxHealth = t;
}
void GameCharacter::setCurrentHealth(int t) {
    this->currentHealth = t;
}
void GameCharacter::setAttack(int t) {
    this->attack = t;
}
void GameCharacter::setDefense(int t) {
    this->defense = t;
}
int GameCharacter::getMaxHealth() {
    return this->maxHealth;
}
int GameCharacter::getCurrentHealth() {
    return this->currentHealth;
}
int GameCharacter::getAttack() {
    return this->attack;
}
int GameCharacter::getDefense() {
    return this->defense;
}

class Skill {
private:
    string impact_on_type;
    int value;
    string property;
    int costmp;
    string name;
public:
    
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
    string getImpactType() const {
        return this->impact_on_type;
    }
    int getValue() const {
        return this->value;
    }
    void setValue(int tval) {
        this->value = tval;
    }
    void setProperty(string tppt) {
        this->property = tppt;
    }
    string getProperty() const {
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
class Condition : public Object { //added: buff and debuff
private:
    string impact_on_type;
    int value;
public:
    Condition(string n, string type, int val) : value(val), impact_on_type(type) { setName(n);  setTag("condition"); }


    void setImpactType(string ttype) {
        this->impact_on_type = ttype;
    }
    string getImpactType() {
        return this->impact_on_type;
    }
    int getValue() {
        return this->value;
    }
    void setValue(int tval) {
        this->value = tval;
    }
};