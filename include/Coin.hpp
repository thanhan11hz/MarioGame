#pragma once

#include <box2d/box2d.h>

#include "Object.hpp"
#include "Animation.hpp"
#include "UserData.hpp"
#include "Physics.hpp"

class Coin : public Object {
    public:
        Coin(std::vector<Object*> &object) : Object(object) {}
        ~Coin();
        virtual void init();
        virtual void update(float dt);
        virtual void draw();
    private:
        Animation mAnim;
        b2BodyId mBody;
};