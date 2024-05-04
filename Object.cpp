#include "Object.h"
Object::Object() {
    setName(""); setTag("");
}
Object::Object(string tname, string ttag) : name(tname), tag(ttag) {}

/* pure virtual function */
//virtual bool 
// Event(Object*);

/* Set & Get function*/
void Object::setName(string t) {
    name = t;
}
void Object::setTag(string t) {
    tag = t;
}
string Object::getName() {
    return name;
}
string Object::getTag() {
    return tag;
}