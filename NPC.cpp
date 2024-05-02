#include "NPC.h"
#include "Player.h"

// NPC::NPC() : isInteract(false) {}

NPC::NPC(string n, vector<string> tscript, vector<Goods*> commodities)
    : isInteract(false), script(tscript), commodities(commodities) {
    setName(n);
    setTag("NPC");
}

NPC::NPC(string n, vector<string> tscript)
    : isInteract(false), script(tscript) {
    setName(n);
    setTag("NPC");
}

NPC::NPC(string n, vector<Goods*> commodities, vector<Food*> foodie)
    : isInteract(false), commodities(commodities), foods(foodie) {
    setName(n);
    setTag("NPC");
}

// 
bool NPC::triggerEvent(Object* obj) {
    Player* player = dynamic_cast<Player*>(obj);

    if (commodities.size() == 0) {
        cout << script[0] << endl;
        cout << "---------------------------------------" << endl;
        int condi;
        cout << "1.Make a deal with " << getName() << "\n2.leave\nEnter Your Choice:";
        cin >> condi;
        if (condi == 1) {
            if (commodities.size() == 0) { // commonds size ==0 meaning that it is a NPC, but not a merchant 
                if (getName() == "Klee" && !getIsinteract()) { //diff NPC have diff trade, make sure only interact once
                    if (player->getmoney() - 20 < 0) {
                        cout << "Sorry, you don't have enough money. poor you...\n";
                        return 0; //stop interact
                    }
                    else {
                        cout << script[1] << endl; //decide to buy script
                        Condition Klee_bless = Condition("Klee's blessing", "attack", 20);
                        player->getCondition().push_back(Klee_bless); //this is pass copy    (((NOT reference))) 
                        setIsinteract(true);
                    }
                }
                else if (getName() == "Himeko" && !getIsinteract()) {
                    if (player->getmoney() - 5 < 0) {
                        cout << "Sorry, you don't have enough money. poor you...\n";
                    }
                    else {
                        cout << script[1] << endl; //decide to buy script
                        Condition Himeko_bless = Condition("Himeko's blessing", "poison", -5); //this is posion, careful dealing with
                        player->getCondition().push_back(Himeko_bless); //this is pass copy    (((NOT reference))) 
                        setIsinteract(true);
                    }
                }
                else if (getName() == "AL_1S" && !getIsinteract()) {
                    if (player->getmoney() - 90 < 0) {
                        cout << "Sorry, you don't have enough money. poor you...\n";
                    }
                    else {
                        cout << script[1] << endl; //decide to buy script
                        Condition AL1S_bless = Condition("AL_1S's blessing", "attack", 90);
                        player->getCondition().push_back(AL1S_bless); //this is pass copy    (((NOT reference))) 
                        setIsinteract(true);
                    }

                }
                return 0; //stop interact
            }
        }
        else if (condi == 2) { //no interaction
            cout << script[2];
            return 0;
        }
        else cin >> condi;
    }
    else if (commodities.size() != 0) {
        cout << "Commodities: \n"; //list all commodities
        for (int i = 0; i < commodities.size(); i++) { //helmet weapon armor
            if (commodities[i]->getType() == "helmet" && commodities[i]->getType() == "armor")cout << i << ". " << commodities[i]->getName() << " : def+" << commodities[i]->getDefense() << ", price = " << commodities[i]->getprice() << endl;
            else if (commodities[i]->getType() == "weapon")cout << i << ". " << commodities[i]->getName() << " : atk+" << commodities[i]->getAttack() << ", price = " << commodities[i]->getprice() << endl;
        }
        for (int i = 0; i < foods.size(); i++) {
            if (foods[i]->getTag() == "food")cout << commodities.size() + i << ". " << foods[i]->getName() << " : thirst+" << foods[i]->getthr() << ", hunger+" << foods[i]->gethun() << ", price = " << foods[i]->getprice() << endl;
            else if (foods[i]->getTag() == "milk")cout << i << ". " << foods[i]->getName() << " : thirst+" << foods[i]->getthr() << ", hunger+" << foods[i]->gethun() << ", price = " << foods[i]->getprice() << endl;
        }
        cout << "-1. exit buying\n";
        int choice; cin >> choice;
        if (choice < commodities.size()) { //purchasing
            if (player->getmoney() - commodities[choice]->getprice() >= 0) {
                if (commodities[choice]->getType() == "helmet") player->setHelmet(commodities[choice]);
                else if (commodities[choice]->getType() == "weapon") player->setWeapon(commodities[choice]);
                else if (commodities[choice]->getType() == "armor") player->setArmor(commodities[choice]);
                player->setmoney(player->getmoney() - commodities[choice]->getprice()); //deduct money
            }
            else cout << "You don't have enough money.\n"; return 0;
        }
        else if (choice >= commodities.size() && choice < commodities.size() + foods.size()) {
            if (player->getmoney() - foods[choice]->getprice() >= 0) {
                player->getfoods().push_back(foods[choice]);
                player->setmoney(player->getmoney() - foods[choice]->getprice()); //deduct money
            }
            else cout << "You don't have enough money.\n"; return 0;
        }
        else if (choice == -1) {
            return 0; //end this task
        }
        //todo: when have money can buy until run out of money.
    }

    return false;
}

// Setter  Getter
void NPC::setScript( vector<string> temp) {
    script = temp;
}

vector<string> NPC::getScript()  {
    return script;
}

void NPC::setCom(vector<Goods*> temp) {
    commodities = temp;
}

vector<Goods*> NPC::getCom()  {
    return commodities;
}

void NPC::setfood(vector<Food*> temp) {
    foods = temp;
}

vector<Food*> NPC::getfood()  {
    return foods;
}

bool NPC::getIsinteract()  {
    return isInteract;
}

void NPC::setIsinteract(bool temp) {
    isInteract = temp;
}
