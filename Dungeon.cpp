#include "Dungeon.h" // Include the corresponding header file
#include <iostream>
#include<algorithm>
using namespace std;

// Initialize game state and provide an introductory story
Dungeon::Dungeon() : isWin(0) {
    cout << "This is a story about an adventurer and their legendary journey fighting against the boss.\n";
    cout << "In this game, you will become this adventurer, experiencing the journey and unrecorded stories.\n";
    cout << "Now, it's time to begin your life. Don't be afraid, just have faith!\n";
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";
    
}

// Create a new player with basic stats
void Dungeon::createPlayer() {
    string player_name;
    cout << "Enter Your Name: ";
    cin >> player_name;
    //cout << "---------------------------------------" << endl;

    Player new_player(player_name, 150, 100, 35, 15, 20, 20, 100);
    Skill skill1("Water Stream Rock Smashing Fist", "water", 5, "attack", 15);
    Skill skill2("Star Burst", "fire", 5, "attack", 15);
    Skill skill3("Seed Bullet", "ground", 5, "attack", 15);
    Skill normal("Normal Attack", "none", 0, "attack", -10);

    new_player.addskill(skill1);
    new_player.addskill(skill2);
    new_player.addskill(skill3);
    new_player.addskill(normal);

    new_player.printStatus();

    player = new_player; // Assign to the class member
}

// Create the map with several rooms
void Dungeon::createMap() {
    rooms.resize(5); // Create a 5x5 grid of rooms
    for (auto& row : rooms) {
        row.resize(5);
    }

    for (size_t i = 0; i < rooms.size(); ++i) {
        for (size_t j = 0; j < rooms[i].size(); ++j) {
            rooms[i][j].setIsExit(0);
            rooms[i][j].setIndex(5 * i + j + 1);
        }
    }

    rooms[0][4].setIsExit(1); // Set the boss room

    // Additional code to set up NPCs, merchants, boss, and monsters would go here.
    // These can be added in a similar pattern, as you've demonstrated in the original code.
    /* NPCS */
    rooms[0][0].setRoomType("NPC");
    vector<string> Klee_script;
    string tempscript = "When you enter the room, you see a little girl with red hat, red clothes, and red backpack. She is 'Fleeing Sunshine' Klee! \n'Hello, onii-chan! I have successfully fled from disciplinary confinement room again! ...... You say you are going to crusade the boss? Coooool! I want to give you my dodoco, which is my best friend!' \n'But, make this dodoco spend me a lot of time, so can you give me a little money so that I can buy more candy? About $20 is enough. Do you want to give me?\n";
    Klee_script.push_back(tempscript);
    tempscript = "'Thank you, onii-chan! I can buy more candy! And this dodoco give you! It will protect you over all times! Bye-Bye!!'\n";
    Klee_script.push_back(tempscript);
    tempscript = "'Well... Bye-Bye onii-chan! Don't say where I am to Master Jean~'\n";
    Klee_script.push_back(tempscript);
    NPC* Klee = new NPC("Klee", Klee_script); rooms[0][0].setObjects(Klee);
    rooms[3][1].setRoomType("NPC");


    vector<string> Himeko_script;
    tempscript = "When you enter the room, you see a familiar red - hair lady with a pour over coffee.She is the navigator of astral express : Himeko!\n";
    Himeko_script.push_back(tempscript);
    tempscript = "'Hey, trailblazer! I think you are tired.Do you want a cup of coffee ? I just poured it over.'\n 'On the other hand, I still need a little money to get the coffee bean. About $5 is enough. Do you want to give me?'\n";
    Himeko_script.push_back(tempscript);
    tempscript = "'Ok, drink it slowly. It's hot, isn't it?'\n";
    Himeko_script.push_back(tempscript);
    tempscript = "'It's fine. Bless your road of trailblaze~'\n";
    Himeko_script.push_back(tempscript);
    NPC* Himeko = new NPC("Himeko", Himeko_script); rooms[3][1].setObjects(Himeko);
    
    rooms[4][4].setRoomType("NPC");
    vector<string> AL1S_script;
    tempscript = "When you enter the room, you see a little girl with a halo and and small robot accessory. She is the club member of game development department, princess of nameless gods, AL-1S(Alice).\n";
    AL1S_script.push_back(tempscript);
    tempscript = "'Welcome. I has waited you for long times, and I know what hero are going to do, so I will give you my best help: My laser cannon.'\n'However, I need to give the engineering club some compensate, so I need $90 for them to make a new laser cannon. Do you want to give me?\n";
    AL1S_script.push_back(tempscript);
    tempscript = "'Then, the laser cannon is now yours. This shit is just fxxking insane.... use it to beat up anyone's ass!!!'\n";
    AL1S_script.push_back(tempscript);
    tempscript = "'OK, but yo' get in trouble like so deep bro... Good Luck!'\n";
    AL1S_script.push_back(tempscript);
    NPC* AL_1S = new NPC("AL_1S", AL1S_script); rooms[4][4].setObjects(AL_1S);


    /* Merchants */
    rooms[0][3].setRoomType("NPC");
    vector<Goods*> Beedle1_comods; vector<Food*> b1_foods;
    Goods* blade1 = new Goods("blade lv1", 0, 5, 0, 10, "weapon", "gear"); Beedle1_comods.push_back(blade1);
    Goods* sword1 = new Goods("sword lv1", 0, 10, 0, 20, "weapon", "gear"); Beedle1_comods.push_back(sword1);
    Goods* helmet1 = new Goods("helmet lv1", 0, 0, 1, 10, "helmet", "gear"); Beedle1_comods.push_back(helmet1);
    Goods* breastplate1 = new Goods("breastplate lv1", 0, 0, 3, 20, "armor", "gear"); Beedle1_comods.push_back(breastplate1);
    Food* coriander_pizza = new Food("coriander pizza", 10, 4, 0, "food"); b1_foods.push_back(coriander_pizza);
    Food* stired_curry_rice = new Food("stired curry rice", 20, 8, 0, "food"); b1_foods.push_back(stired_curry_rice);
    Food* bottled_water =new Food("bottled water", 10, 0, 4, "food"); b1_foods.push_back(bottled_water);
    Food* oolong_tea =new Food("oolong tea", 20, 0, 8, "food"); b1_foods.push_back(oolong_tea);
    Food* milk = new Food("Milk", 35, 2, 2, "milk"); b1_foods.push_back(milk);
    NPC* Beedle1 = new NPC("Beedle", Beedle1_comods, b1_foods); rooms[0][3].setObjects(Beedle1);

    rooms[1][4].setRoomType("NPC");
    vector<Goods*> Beedle2_comods; vector<Food*>b2_foods;
    Goods* blade2 = new Goods("blade lv2", 0, 15, 0, 30, "weapon", "gear"); Beedle2_comods.push_back(blade2);
    Goods* sword2 = new Goods("sword lv2", 0, 20, 0, 40, "weapon", "gear"); Beedle2_comods.push_back(sword2);
    Goods* helmet2 = new Goods("helmet lv2", 0, 0, 3, 10, "helmet", "gear"); Beedle2_comods.push_back(helmet2);
    Goods* breastplate2 = new  Goods("breastplate lv2", 0, 0, 5, 20, "armor", "gear"); Beedle2_comods.push_back(breastplate2);
    Food* coriander_pizza1 = new Food("coriander pizza", 10, 4, 0, "food"); b1_foods.push_back(coriander_pizza1);
    Food* stired_curry_rice1 = new Food("stired curry rice", 20, 8, 0, "food"); b2_foods.push_back(stired_curry_rice1);
    Food* bottled_water1 = new Food("bottled water", 10, 0, 4, "food"); b2_foods.push_back(bottled_water1);
    Food* oolong_tea1 = new Food("oolong tea", 20, 0, 8, "food"); b2_foods.push_back(oolong_tea1);
    Food* milk1 = new Food("Milk", 35, 2, 2, "milk"); b2_foods.push_back(milk1);
    NPC* Beedle2 = new NPC("Beedle but cooler", Beedle2_comods, b2_foods); rooms[1][4].setObjects(Beedle2);

    /* Boss to be made */
    vector<string> boss_script;
    tempscript = "You've finally been here. I'm impressed that you do not withdraw from the Calculus by Prof. Lin Bear.\n But I'm sorry you must have a C- here. NOW¡@DIE!\n"; boss_script.push_back(tempscript);
    tempscript = "DROP the course and try next time.\n"; boss_script.push_back(tempscript);
    tempscript = "Fine... you are capable. Next time you will know when you meet Probability.\n"; boss_script.push_back(tempscript);

    vector<Skill> tempskills; //    Skill(string tn, string prop, int val, string ontype)
    tempskills.push_back(Skill("Parametric Curve", "psycho", 15, "attack"));
    tempskills.push_back(Skill("Triple Integral", "psycho", 15, "attack"));
    tempskills.push_back(Skill("Directional Derivation", "psycho", 15, "attack"));
    Boss* boss = new Boss("Calculus", 200, 40, 15, tempskills); boss->setscript(boss_script);
    rooms[0][4].setObjects(boss);
    finalboss = boss;

    /* monsters */
    Monster* Skeleton_lv1 = new Monster("Skeleton lv1", 70, 25, 0, "ground"); Skeleton_lv1->setTag("monster"); //no skill, normal attack
    rooms[4][3].setObjects(Skeleton_lv1);
    Monster* Skeleton_lv2 =new Monster("Skeleton lv2", 100, 30, 0, "ground"); Skeleton_lv2->setTag("monster");
    rooms[1][2].setObjects(Skeleton_lv2);
    Monster* Zombie_lv1 =new Monster("Zombie lv1", 70, 20, 5, "fire"); Zombie_lv1->setTag("monster");
    rooms[3][2].setObjects(Zombie_lv1);
    Monster* Zombie_lv2 =  new Monster("Zombie lv2", 100, 25, 5, "fire"); Zombie_lv2->setTag("monster");
    rooms[2][1].setObjects(Zombie_lv2);
    Monster* Zombie_lv3 = new Monster("Zombie lv3", 120, 30, 5, "fire"); Zombie_lv3->setTag("monster");
    rooms[1][3].setObjects(Zombie_lv3);
    Monster* Slime_lv1 = new Monster("Slime lv1", 100, 20, 0, "water"); Slime_lv1->setTag("monster");
    rooms[4][2].setObjects(Slime_lv1);
    Monster* Slime_lv2 = new Monster("Slime lv2", 120, 25, 0, "water"); Slime_lv2->setTag("monster");
    rooms[3][3].setObjects(Slime_lv2);
    Monster* Slime_lv3 = new Monster("Slime lv3", 150, 25, 0, "water"); Slime_lv3->setTag("monster");
    rooms[2][3].setObjects(Slime_lv3);


    rooms[0][1].setRoomType("wildlife"); rooms[0][2].setRoomType("swamp"); rooms[0][3].setRoomType("NPC"); rooms[0][4].setRoomType("BOSS");
    rooms[1][0].setRoomType("swamp"); rooms[1][1].setRoomType("forest"); rooms[1][2].setRoomType("lake");  rooms[1][3].setRoomType("mushroom land"); rooms[1][4].setRoomType("NPC");
    rooms[2][0].setRoomType("BLOCKED"); rooms[2][1].setRoomType("purified water"); rooms[2][2].setRoomType("mushroom land"); rooms[2][3].setRoomType("oasis"); rooms[2][4].setRoomType("sand storm");
    rooms[3][0].setRoomType("wildlife"); rooms[3][1].setRoomType("NPC"); rooms[3][2].setRoomType("lake"); rooms[3][3].setRoomType("dessert");  rooms[3][4].setRoomType("BLOCKED");
    rooms[4][0].setRoomType("START"); rooms[4][1].setRoomType("dessert"); rooms[4][2].setRoomType("forest"); rooms[4][3].setRoomType("sand storm"); rooms[4][4].setRoomType("NPC");


    for (int i = 0; i < rooms.size(); i++) {
        for (int j = 0; j < rooms[i].size(); j++) {
            if (i == 0) { rooms[i][j].setUpRoom(NULL); }
            else { rooms[i][j].setUpRoom(&rooms[i - 1][j]); }
            if (j == 0) { rooms[i][j].setLeftRoom(NULL); }
        
            else { rooms[i][j].setLeftRoom(&rooms[i][j - 1]); }
            if (i == 4) { rooms[i][j].setDownRoom(NULL); }
            else { rooms[i][j].setDownRoom(&rooms[i + 1][j]); }
            if (j == 4) { rooms[i][j].setRightRoom(NULL); }
            else { rooms[i][j].setRightRoom(&rooms[i][j + 1]); }
        }
    }    
    Food* milk2 = new Food("Milk", 35, 2, 2, "milk"); rooms[4][1].setObjects(milk2);

    historyRoom.push_back(&rooms[4][0]);
}

// Print the map to console
void Dungeon::printMap() {
    
    for (size_t i = 0; i < rooms.size(); ++i) {
        for (size_t j = 0; j < rooms[i].size(); ++j) {
            int condi = 0;
            for (int k = 0; k < historyRoom.size(); k++) {
                if (historyRoom[k] == &rooms[i][j]) {
                    condi = 1;
                    break;
                }
            }
            if (condi) cout << (i * 5 + j + 1) << ". " << rooms[i][j].getRoomType() << "   ";
            else cout << (i * 5 + j + 1) << ". ????   ";

        }
        cout << "\n";
    }

    cout << "---------------------------------------\n";
    cout << "You have been to these following rooms:\n";
    if (historyRoom.size() > 1) {
        for (size_t i = 0; i < historyRoom.size() - 1; ++i) {
            cout << historyRoom[i]->getIndex() << " -> ";
        }
    }

    cout << historyRoom[historyRoom.size() - 1]->getIndex() << "\n";
    cout << "---------------------------------------" << endl;
}

// Manage player movement between rooms
void Dungeon::handleMovement()
{ //cin 0 1 2 3 4.......
    cout << "---------------------------------------" << endl;
    cout << "0. Cancel\n1. Go upward\n2. Go downward\n3. Go right\n4. Go left\nChoose Your Action: ";
    int motion; cin >> motion; //nest structure is better for detecting a condition once
    while (motion > 4 || motion < 0) {
        cout << "Invalid Input. Choose Your Action";  cin >> motion;
    }
    if (motion == 0) return;
    //upRoom is not empty and is not BLOCKED 
    if (motion == 1 && player.getCurrentRoom()->getIndex() - 5 > 0 && player.getCurrentRoom()->getUpRoom()->getRoomType() != "BLOCKED") {
        if (player.getCurrentRoom()->getUpRoom()->getRoomType() == "BLOCKED") {
            cout << "This way is Blocked!\n"; historyRoom.push_back(player.getCurrentRoom()->getUpRoom()); return;
        }
        player.setPreviousRoom(player.getCurrentRoom());
        player.setCurrentRoom(player.getCurrentRoom()->getUpRoom());
        historyRoom.push_back(player.getCurrentRoom());
    }
    else if (motion == 2 && player.getCurrentRoom()->getIndex() + 5 <= 25 && player.getCurrentRoom()->getDownRoom()->getRoomType() != "BLOCKED") {
        if (player.getCurrentRoom()->getDownRoom()->getRoomType() == "BLOCKED") {
            cout << "This way is Blocked!\n"; historyRoom.push_back(player.getCurrentRoom()->getDownRoom()); return;
        }
        player.setPreviousRoom(player.getCurrentRoom());
        player.setCurrentRoom(player.getCurrentRoom()->getDownRoom());
        historyRoom.push_back(player.getCurrentRoom());
    }
    else if (motion == 3 && player.getCurrentRoom()->getIndex() % 5 != 0 && player.getCurrentRoom()->getRightRoom()->getRoomType() != "BLOCKED") {
        if (player.getCurrentRoom()->getRightRoom()->getRoomType() == "BLOCKED") {
            cout << "This way is Blocked!\n"; historyRoom.push_back(player.getCurrentRoom()->getRightRoom()); return;
        }
        player.setPreviousRoom(player.getCurrentRoom());
        player.setCurrentRoom(player.getCurrentRoom()->getRightRoom());
        historyRoom.push_back(player.getCurrentRoom());
    }
    else if (motion == 4 && player.getCurrentRoom()->getIndex() % 5 != 1 && player.getCurrentRoom()->getLeftRoom()->getRoomType() != "BLOCKED") {
        if (player.getCurrentRoom()->getLeftRoom()->getRoomType() == "BLOCKED") {
            cout << "This way is Blocked!\n"; historyRoom.push_back(player.getCurrentRoom()->getLeftRoom()); return;
        }
        player.setPreviousRoom(player.getCurrentRoom());
        player.setCurrentRoom(player.getCurrentRoom()->getLeftRoom());
        historyRoom.push_back(player.getCurrentRoom());
    }


    /*Dessert    hunger -1 more(eventually -3 when enter)
         Sandstorm    hunger -2 more    thirst -2 more
        Oasis    hunger +10 thirst +10(eventually+8)
        Forest hunger  -1 more
        Wildlife if(hunger > 10) then hunger+2    else HP -5 (you can modify if it's hard to do)
        Lake    thirst +6
        Swamp    HP -2
        Mushroom land    hunger +6
        Purify water    thirst +6
        */
    player.setTHR((player.getTHR() - 1 <= 0) ? 0 : player.getTHR() - 1); player.setHG((player.getHG() - 1 <= 0) ? 0 : player.getHG() - 1); // everytime entering a room -1, but not less than zero
    if (player.getCurrentRoom()->getRoomType() == "dessert") player.setTHR((player.getTHR() - 1 <= 0) ? 0 : player.getTHR() - 1);
    else if (player.getCurrentRoom()->getRoomType() == "sandstorm") { player.setTHR((player.getTHR() - 2 <= 0) ? 0 : player.getTHR() - 2); player.setHG((player.getHG() - 1 <= 0) ? 0 : player.getHG() - 1); }
    else if (player.getCurrentRoom()->getRoomType() == "oasis") { player.setTHR((player.getTHR() + 10 >= 20) ? 20 : player.getTHR() + 10); player.setHG((player.getHG() + 10 >= 20) ? 20 : player.getHG() + 10); }

    else if (player.getCurrentRoom()->getRoomType() == "forest") { player.setHG((player.getHG() - 1 <= 0) ? 0 : player.getHG() - 1); }
    else if (player.getCurrentRoom()->getRoomType() == "wildlife") {
        if (player.getHG() >= 10) player.setHG((player.getHG() + 2 >= 20) ? 20 : player.getHG() + 2);
        else player.setCurrentHealth((player.getCurrentHealth() - 5 <= 0) ? 0 : player.getCurrentHealth() - 5);
    }
    else if (player.getCurrentRoom()->getRoomType() == "lake") player.setTHR((player.getTHR() + 6 >= 20) ? 20 : player.getTHR() + 6);
    else if (player.getCurrentRoom()->getRoomType() == "swamp") player.setCurrentHealth((player.getCurrentHealth() - 2 <= 0) ? 0 : player.getCurrentHealth() - 2);
    else if (player.getCurrentRoom()->getRoomType() == "mushroom land") player.setHG((player.getHG() + 6 >= 20) ? 20 : player.getHG() + 6);
    else if (player.getCurrentRoom()->getRoomType() == "purify water") {
        player.setTHR((player.getTHR() + 6 >= 20) ? 20 : player.getTHR() + 6);
        player.setMP(player.getMP() + 50 >= 150 ? 150 : player.getMP() + 50);
        if (player.getTHR() > 8) {
            player.getCondition().erase(
                std::remove_if(
                    player.getCondition().begin(),
                    player.getCondition().end(),
                    [](Condition* condition) { return condition->getName() == "Thirsty"; }
                ),
                player.getCondition().end()
            );
        }
        if (player.getHG() > 8) {
            player.getCondition().erase(
                std::remove_if(
                    player.getCondition().begin(),
                    player.getCondition().end(),
                    [](Condition* condition) { return condition->getName() == "Hungry"; }
                ),
                player.getCondition().end()
            );
        }
    }
    else if (player.getCurrentRoom()->getRoomType() == "NPC") { player.setTHR((player.getTHR() + 1 >= 20) ? 20 : player.getTHR() + 1); player.setHG((player.getHG() + 1 >= 20) ? 20 : player.getHG() + 1); }

    player.refreshStatus(); //refresh status
    return;
}
// Deal with player interactions with objects in the room
void Dungeon::handleEvent(Object* curobj) {
    NPC* npc = dynamic_cast<NPC*>(curobj);//if not then null
    Monster* monster = dynamic_cast<Monster*> (curobj);
    Boss* boss = dynamic_cast<Boss*>(curobj);
    Food* milk = dynamic_cast<Food*>(curobj);
    Goods* gear = dynamic_cast<Goods*>(curobj);

    cout << "---------------------------------------" << endl;
    if (npc) {

        bool status = npc->triggerEvent(&player);
        if (!npc->getIsinteract()) {
            while (status) {
                status = npc->triggerEvent(&player);
            }
        }
        else {
            cout << "You've been interacted with " << npc->getName() << endl;
        }
     }
        
    else if (monster) {
        if (monster->checkIsDead()) {
            cout << "It's dead now, no need to attack him bro.\n";

            return;
        }
        bool status = monster->triggerEvent(&player);
        while (!monster->checkIsDead() && status) {
            status = monster->triggerEvent(&player);
        }
    }
    else if (boss) {
        cout << boss->getscript()[0];
        if (boss->checkIsDead()) {
            isWin = 1;
            return;
        }
        bool status = boss->triggerEvent(&player);
        while (!boss->checkIsDead() && status) {
            status = boss->triggerEvent(&player);
        }
        if (player.checkIsDead()) cout << boss->getscript()[1]; 
        
        return;
    }
    else if (milk) {
        static int isPicked=0;
        if (isPicked) {
            cout << "You've picked up this. Don't be that greedy\n"; return;
        }
        if (!isPicked) {
            player.pickupItem(milk); 
            isPicked = 1;
        }
        
    }
    else if (gear) {
        static int isPicked = 0;
        if (isPicked) {
            cout << "You've picked up this. Don't be that greedy\n"; return;
        }
        if (!isPicked) {
            player.pickupItem(gear); 
            isPicked = 1;
        }
        
    }
    
}

// Start the game, creating the map and the player
void Dungeon::startGame() {
    createMap();
    createPlayer();

    player.setCurrentRoom(&rooms[4][0]); historyRoom.push_back(&rooms[4][0]);

}

// Choose action for the player in the current room
void Dungeon::chooseAction() {

    Room* currentRoom = player.getCurrentRoom();

    cout << "You are now in room " << currentRoom->getIndex() << ". Choose your action:\n";
    cout << "---------------------------------------" << endl; 
    if (currentRoom->getObjects() != nullptr) { 
        NPC* npc = dynamic_cast<NPC*>(currentRoom->getObjects());//if not then null
        Monster* monster = dynamic_cast<Monster*> (currentRoom->getObjects());
        Food* milk = dynamic_cast<Food*> (currentRoom->getObjects());
        Goods* gear = dynamic_cast<Goods*>(currentRoom->getObjects());
        if (npc) {
            string tname = npc->getName();
            cout << 0 << ". Interact with " << tname << "\n";
        }
        else if (monster) {
            string tname = monster->getName();
            cout << 0 << ". Combat with " << tname << "\n";

        }
        else if (milk) {
            cout << 0 << ". Pick up the" << milk->getName() << endl;
        }
        else if (gear) {
            cout << 0 << ". Pick up the" << gear->getName() << endl;
        }
    }


    cout << 1 << ". Check Map\n";
    cout << 2 << ". Check Current Status\n";
    cout << 3 << ". Move to other Rooms\n";
    cout << 4 << ". Use Items\n";

    int choice;
    cin >> choice;

    if (choice == 0) {
        NPC* npc = dynamic_cast<NPC*>(currentRoom->getObjects());
        Monster* monster = dynamic_cast<Monster*>(currentRoom->getObjects());
        Food* milk = dynamic_cast<Food*> (currentRoom->getObjects());
        Goods* gear = dynamic_cast<Goods*>(currentRoom->getObjects());
        if (npc)  handleEvent(npc);
        else if (monster) handleEvent(monster);
        else if (milk) handleEvent(milk);
        else if (gear) handleEvent(gear);
    }
    else if (choice == 1) {
        printMap();
    }
    else if (choice == 2) {
        player.printStatus();
    }
    else if (choice == 3) {
        handleMovement();
    }
    else if (choice == 4) {
        player.triggerEvent(&player); return;
    }
    else {
        cout << "Invalid choice.\nChoose Your Action"; cin >> choice;
    }
}
// Check if the game should end (player wins or dies)
bool Dungeon::checkGameLogic() {
    if (player.checkIsDead()) {
        return true; // Player died
    }
    if (isWin) {
        return true; // Player won
    }
    return false; // Continue the game
}

// Main game loop
void Dungeon::runDungeon() {
    startGame(); // Start with the initial setup
    cout << rooms[3][1].getObjects()->getTag() << endl;

    cout << "Loading..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Finished! Enjoy your journey! :D\n";

    printMap();    
    while (!checkGameLogic()) {

        chooseAction(); // Let the player choose an action    

        if (finalboss && finalboss->checkIsDead()) {
            isWin = 1; // Player defeated the boss
        }

    }

    if (isWin && player.getCurrentHealth() > 0) {
        cout << finalboss->getscript()[2];
        cout << "You Won the Game !!! Enjoy the last of yours:)))))))";
    }
    else {
        cout << "Game over. You died in your adventure.\n";
    }
}
