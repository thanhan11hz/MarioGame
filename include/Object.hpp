#pragma once

#include <raylib.h>
#include <vector>

#include "Resource.hpp"

class Object {
    public:
        Object(std::vector<Object*> &object);
        virtual ~Object() = default;
        virtual void init();
        virtual void update(float dt);
        virtual void draw();

        std::string mTag{};
        Vector2 mPostion{};
        float mAngle{};
        std::vector<Object*>& mContainer;
};