#include "Object.hpp"

Object::Object(std::vector<Object*> &object) : mContainer(object) {}

void Object::init() {}

void Object::draw() {}

void Object::update(float dt) {}
