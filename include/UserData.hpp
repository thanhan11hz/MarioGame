#pragma once

#include <box2d/box2d.h>

#include "Object.hpp"
#include "ContactListener.hpp"

class Mario;

enum class UserDataType {
    MARIO,
    MAPTILE,
    OBJECT
};

struct UserData {
    
    UserDataType type;
    ContactListener* listener;

    union {
        Mario* mario;
        Object* object;
        struct { int mapX, mapY; };
    };
};