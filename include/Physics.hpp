#pragma once

#include <box2d/box2d.h>
#include <box2d/base.h>
#include "DebugDraw.hpp"
#include "Mario.hpp"

class Physics {
    public:
        static void init();
        static void update(float dt);
        static void debugDraw();
        static b2WorldId mWorld;
        static MyDebugDraw mDraw;
    private:
        static void updateSensor();
};