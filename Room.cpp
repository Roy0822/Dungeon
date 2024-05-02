#include "Room.h"
#include <iostream>
Room::Room() {
    setIsExit(0);
    setIndex(0);
    setRoomType("");
}
Room::Room(bool tisExit, int id, string type, vector<Object*> tobjects){
    setIsExit(tisExit);
    setIndex(id);
    setRoomType(type);
    setObjects(tobjects);
}

bool Room::popObject(Object* tobj) {
    // find a specific thing with iterator
    auto it = std::find(objects.begin(), objects.end(), tobj);

    if (it != objects.end()) {  // if found
        objects.erase(it);  // deleta
        return true;  // true for delete successful
    }
    else {
        return false;  // not finding it
    }
}

/* Set & Get function*/

void Room::setUpRoom(Room* temproom) {
    this->upRoom = temproom;
}
void Room::setDownRoom(Room* temproom) {
    this->downRoom = temproom;
}
void Room::setLeftRoom(Room* temproom) {
    this->leftRoom = temproom;
}
void Room::setRightRoom(Room* temproom) {
    this->rightRoom = temproom;
}

void Room::setIsExit(bool temp) {
    this->isExit = temp;
}
void Room::setIndex(int temp) {
    this->index = temp;
}
void Room::setObjects(vector<Object*>temp) {
    this->objects = temp;
}
void Room::setRoomType(string temp) { //added
    this->roomType = temp;
}

bool Room::getIsExit() {
    return isExit;
}
int Room::getIndex() {
    return index;
}
vector<Object*> Room::getObjects() {
    return objects;
}
string Room::getRoomType() {
    return roomType;
}


Room* Room::getUpRoom() {
    return upRoom;
}
Room* Room::getDownRoom() {
    return downRoom;
}
Room* Room::getLeftRoom() {
    return leftRoom;
}
Room*Room::getRightRoom() {
    return rightRoom;
}
