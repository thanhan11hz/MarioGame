#pragma once

#include <raylib.h>
#include <filesystem>
#include <iostream>

#include "Resource.hpp"
#include "Map.hpp"
#include "Mario.hpp"
#include "Physics.hpp"
#include "Object.hpp"

#include <box2d/box2d.h>

class Game {
    public:
        explicit Game();
        void run();
        void input();
        void update(float dt);
        void draw();
        void drawUI();
    private:
        float mTimePerFrame = 1 / 60.f;
        Camera2D mCamera;
        Map mMap;
        Mario mMario;
        Music mMusic;
        Font mFont;
        std::vector<Object*> mObject;
};