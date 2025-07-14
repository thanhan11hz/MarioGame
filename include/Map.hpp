#pragma once

#include <vector>
#include <box2d/box2d.h>

#include "Resource.hpp"
#include "Physics.hpp"
#include "Coin.hpp"
#include "Enemy.hpp"

class Map {
    public:
        Map(float cellSize = 1.f);
        std::vector<std::vector<Texture2D*>> grid;
        void createCheckerBoard(size_t width, size_t height);
        void draw();
        Vector2 createFromImage(Image &image, std::vector<Object*> &object);
    private:
        float cellSize;
};