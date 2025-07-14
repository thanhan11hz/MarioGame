#pragma once

#include <raylib.h>
#include <box2d/box2d.h>

#include "Object.hpp"
#include "Animation.hpp"
#include "UserData.hpp"
#include "Physics.hpp"

class Enemy : public Object {
    public:
        Enemy(std::vector<Object*> &object);
        virtual void init();
        virtual void update(float dt);
        virtual void draw();
        void die();

    private:
        Animation mAnim{};
        UserData mData;
        b2BodyId mBody;
        float mMovement = 5.0f;
        float destroyTimer = 0.0f;
        bool isDead = false;
};