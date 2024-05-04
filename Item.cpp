#include "Item.h"
Item::Item() {
    setAttack(0); setDefense(0); setHealth(0); setName(""); setTag("");
}
Item::Item(string tn, int h, int a, int d) {
    setAttack(a);
    setDefense(d);
    setHealth(h);
    setName(tn);
}
//Item::~Item() {}

/* Virtual function that you need to complete    */
/* In Item, this function should deal with the   */
/* pick up action. You should add status to the  */
/* player.                                       */
bool Item::triggerEvent(Object* obj) {  //no need to implement
    Player* player = dynamic_cast<Player*>(obj);
    return 0;
}

/* Set & Get function*/
int Item::getHealth() {
    return health;
}
int Item::getAttack() {
    return attack;
}
int Item::getDefense() {
    return defense;
}
void Item::setHealth(int t) {
    health = t;
}
void Item::setAttack(int t) {
    attack = t;
}
void Item::setDefense(int t) {
    defense = t;
}
bool Food::triggerEvent(Object* obj) {
    Player* player = dynamic_cast<Player*>(obj);
    if (getName() != "Milk") {
        cout << "You get: Hunger:" << hungerVal << ",  Thirst:" << thirstVal << ", Health:" << getprice() << endl; //recover health equal to price
        player->setHG((player->getHG() + hungerVal >= 20) ? 20 : player->getHG() + hungerVal); //cannot be over 20
        player->setTHR((player->getTHR() + thirstVal) >= 20 ? 20 : player->getTHR() + thirstVal); // cannot be over 20
        player->setCurrentHealth((player->getCurrentHealth() + getprice() >= player->getMaxHealth()) ? player->getMaxHealth() : player->getCurrentHealth() + getprice()); //cannot be over the max health
        return 0;
    }
    else if (getName() == "Milk") {
        cout << "You get: Hunger:" << hungerVal << ",  Thirst:" << thirstVal << ", MP:50, Health:30\n";
        cout << "Also, any negative condition of yours is cured. LETSSSSSSSS GOOOOO\n";
        player->setHG(min(20, player->getHG() + hungerVal));  // Cap at 20
        player->setTHR(min(20, player->getTHR() + thirstVal));  // Cap at 20
        player->setCurrentHealth(min(player->getMaxHealth(), player->getCurrentHealth() + 30));
        player->setMP(min(150, player->getMP() + 50));  // Cap at 150


        for (auto& condition : player->getCondition()) {
            if (condition->getValue() < 0) {
                condition->setValue(0);  // Neutralize negative values
            }
        }
        return 0;  // Success
    }
}
Food::Food() {
    sethun(0); setthr(0); setprice(0);
}
Food::Food(string tname, int p, int hv, int tv, string ttag) {
    setName(tname); setprice(p); sethun(hv); setthr(tv); setTag("food");
}
Goods::Goods() {
    setprice(0); setType("");
}
Goods::Goods(string n, int h, int a, int d, int p, string t, string ttag) {
    setName(n); setHealth(h); setAttack(a); setDefense(d); setprice(p); setType(t); setTag(ttag);
}

bool Goods::triggerEvent(Object* obj) { 
    Player* player = dynamic_cast<Player*>(obj);
    return 0;
}
