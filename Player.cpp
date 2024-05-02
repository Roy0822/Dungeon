#include "Player.h"
#include "Item.h"
class Goods;
class Food;
Player::Player() {
    setTag("");
    setName("");
    setMP(0); setArmor(NULL); setWeapon(NULL); setHelmet(NULL); setCurrentRoom(NULL); setHG(0); setTHR(0); setmoney(100); setPreviousRoom(NULL);
}
Player::Player(string name, int mp, int health, int attack, int defense, int hg, int thr, int mny) {
    setTag("Player");
    setName(name);
    setMP(mp);
    setAttack(attack);
    setDefense(defense);
    setMaxHealth(health);
    setCurrentHealth(health);
    setHG(hg);
    setTHR(thr);

    currentRoom = NULL;
    previousRoom = NULL;
}
void Player::addItem(Food* temp) {
    foods.push_back(temp);
}

void Player::changeRoom(Room* nextRoom) { //call by ref
    previousRoom = currentRoom;
    currentRoom = nextRoom;
}

bool Player::triggerEvent(Object* obj) { //use item bool=1 for successful and end the task
    Player* player = dynamic_cast<Player*>(obj);
    cout << "---------------------------------------" << endl;
    if (!foods.empty()) {
        cout << "You have the following item(s): \n";
        for (int i = 0; i < foods.size(); i++) {
            cout << i << ". [" << foods[i]->getName() << "] , a " << foods[i]->getTag() << "\n";
        }
        cout << foods.size() << ". Cancel the Action";
        cout << "Enter Your Choice:";  int choice; cin >> choice;
        if (choice < foods.size()) {
            foods[choice]->triggerEvent(this);
        }
        else if (choice == foods.size()) return 1;
        else cout << "Enter Your Choice:"; cin >> choice; //ban other input
    }
    else {
        cout << "You currently have no item :( poor you.\n";
        cout << "---------------------------------------" << endl;

        return 0;
    }
    return 0;
}

int Player::cal_attackval(int skill_index) { //which skill do you choose
    int total = this->getAttack();
    total += weapon->getAttack();
    if (skill_index != -1) { //if not chosing skills*, it has to be -1
        //then the option is 0~n
        if (skills[skill_index].getImpactType() == "attack") {
            total += skills[skill_index].getValue();
        }
    }
    for (int i = 0; i < conditions.size(); i++) {
        if (conditions[i].getImpactType() == "attack")  total += conditions[i].getValue();
    }

    return total;
}
int Player::cal_defval(int skill_index) { //which skill do you choose
    int total = this->getDefense();
    total += armor->getDefense();
    total += helmet->getDefense();
    if (skill_index != -1) { //if not chosing skills*, it has to be -1
        //then the option is 0~n
        if (skills[skill_index].getImpactType() == "defense") {
            total += skills[skill_index].getValue();
        }
    }
    for (int i = 0; i < conditions.size(); i++) {
        if (conditions[i].getImpactType() == "defense")  total += conditions[i].getValue();
    }
    return total;
}
void Player::printStatus() {
    cout << "---------------------------------------" << endl;
    cout << getName() << "'s Conditions: " << endl;
    cout << "Health: " << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "MP: " << getMP() << "/150\n";
    cout << "Attack: " << getAttack() << endl;
    cout << "Defense: " << getDefense() << endl;
    cout << "Hunger: " << getHG() << endl;
    cout << "Thirst: " << getTHR() << endl;
    cout << "Gears: Armor:" << getArmor() << ", Weapon:" << getWeapon() << ", Helmet:" << getHelmet() << endl;
    cout << "In packpack:\n";
    for (int i = 0; i < foods.size(); i++) {
        cout << i << ". " << foods[i]->getName() << "  ";
    }
    cout << "\n";

    for (int i = 0; i < skills.size(); i++) {
        cout << "Skill " << i << ": " << skills[i].getname() << "  "
            << "Property: " << skills[i].getProperty() << endl;
    }
    for (int i = 0; i < conditions.size(); i++) {
        cout << "Condition " << i << ": " << conditions[i].getName() << "  "
            << "Impact on: " << conditions[i].getImpactType() << "by value: " << conditions[i].getValue() << endl;
    }
    cout << "---------------------------------------" << endl;
}

void Player::refreshStatus() {
    if (thirst <= 8) { // make a new condition Condition(string n, string type, int val)
        Condition thirsty = Condition("Thirsty", "health", -2); addCondi(thirsty);
    }
    if (hunger <= 8) {
        Condition hungry = Condition("Hungry", "health", -2); addCondi(hungry);
    }
    //calculate the whole condition
    for (int i = 0; i < conditions.size(); i++) {
        if (conditions[i].getValue() < 0) {
            if (conditions[i].getImpactType() == "health") {
                setCurrentHealth((getCurrentHealth() - conditions[i].getValue() <= 0) ? 0 : getCurrentHealth() - conditions[i].getValue());
            }
        }
    }
}

Condition::Condition() { setImpactType(""); setValue(0); }
Condition::Condition(string n, string type, int val) {
    setName(n); setImpactType(type); setValue(val);
}
bool Condition::triggerEvent(Object* obj) {
    Player* player = dynamic_cast<Player*>(obj);
    return 0;
}
void Condition::setImpactType(string ttype) {
    impact_on_type = ttype;
}
string Condition::getImpactType() {
    return impact_on_type;
}

int Condition::getValue() {
    return value;
}
void Condition::setValue(int tval) {
    value = tval;
}

/* Set & Get function*/
Goods* Player::getHelmet() {
    return this->helmet;
}
void Player::setHelmet(Goods* temp) {
    this->helmet = temp;
}
Goods* Player::getWeapon() {
    return this->weapon;
}
void Player::setWeapon(Goods* temp) {
    this->weapon = temp;
}
void Player::addskill(Skill temp) {
    this->skills.push_back(temp);
}
vector<Skill> Player::getskill() {
    return this->skills;
}
Goods* Player::getArmor() {
    return this->armor;
}

void Player::setArmor(Goods* temp) {
    this->armor = temp;
}
void Player::setCurrentRoom(Room* temp) {
    this->currentRoom = temp;
}
void Player::setPreviousRoom(Room* temp) {
    this->previousRoom = temp;
}
void Player::setfoods(vector<Food*> temp) {
    foods = temp;
}
void Player::setMP(int tmp) {
    this->MP = tmp;
}
void Player::addfoods(Food* temp) {
    foods.push_back(temp);
}
void Player::setTHR(int thirst) {
    this->thirst = thirst;
}
void Player::setHG(int hunger) {
    this->hunger = hunger;
}
Room* Player::getCurrentRoom() {
    return this->currentRoom;
}
Room* Player::getPreviousRoom() {
    return this->previousRoom;
}
vector<Food*> Player::getfoods() {
    return this->foods;
}
int Player::getMP() {
    return this->MP;
}
int Player::getTHR() {
    return this->thirst;
}
int Player::getHG() {
    return this->hunger;
}

vector<Condition> Player::getCondition() { return this->conditions; }
void Player::addCondi(Condition tempcondi) { conditions.push_back(tempcondi); }

int Player::getmoney() { return this->money; }
void Player::setmoney(int temp) { this->money = temp; }