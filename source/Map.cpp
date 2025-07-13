#include "Map.hpp"

Map::Map(float cellSize) : cellSize(cellSize), grid() {}

void Map::createCheckerBoard(size_t width, size_t height) {
    grid = std::vector(width, std::vector(height, (Texture2D*)nullptr));
    int last = 0;
    for (auto& column: grid) {
        for (auto& cell: column) {
            last = !last;
            if (last) cell = &Resource::textures["brick"];
        }
        if (width % 2 == 0) last = !last;
    }
}

Vector2 Map::createFromImage(Image &image, std::vector<Object*> &object) {
    grid.clear();
    grid = std::vector(image.width, std::vector(image.height, (Texture2D*)nullptr));

    Vector2 marioPosition;

    for (size_t x = 0; x < grid.size(); x++) {
        for (size_t y = 0; y < grid[x].size(); ++y) {
            Color color = GetImageColor(image, x, y);
            Object* entity = nullptr;

            if (color.r == 255 && color.g == 255 && color.b == 255) {

                continue;

            } else if (color.r == 255 && color.g == 0 && color.b == 0) {

                marioPosition = Vector2{cellSize * x + cellSize/2.0f, cellSize * y + cellSize/2.0f};
                continue;

            } else if (color.r == 0 && color.g == 0 && color.b == 0) {

                grid[x][y] = &(Resource::textures["brick"]);

            } else if (color.r == 255 && color.g == 255 && color.b == 0) {
                std::cout << "Coin";
                entity = new Coin(object);

            } else if (color.r == 0 && color.g == 255 && color.b == 0) {

                grid[x][y] = &Resource::textures["rock"];

            } 

            if (entity) {
                entity->mPostion = {cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f};
                object.push_back(entity);

            } else {
                b2BodyDef groundBodyDef = b2DefaultBodyDef();
                groundBodyDef.position = (b2Vec2){cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f};
                b2BodyId groundId = b2CreateBody(Physics::mWorld, &groundBodyDef);
                b2Polygon groundBox = b2MakeBox(cellSize / 2.0f, cellSize / 2.0f);
                b2ShapeDef groundShapeDef = b2DefaultShapeDef();

                UserData* data = new UserData();
                data->type = UserDataType::MAPTILE;
                data->mapX = x;
                data->mapY = y;
                groundShapeDef.density = 1.0f;
                groundShapeDef.userData = (void*) data;
                groundShapeDef.enableSensorEvents = true;
                b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
            }

        }
    }
    return marioPosition;
}

void Map::draw() {
    int x = 0;
    for (const auto& column: grid) {
        int y = 0;
        for (const auto& cell: column) {
            if (cell) {
                DrawTexturePro(*cell, {0, 0, (float)(*cell).width, 
                    (float)(*cell).height}, {cellSize * x + cellSize/2.0f, cellSize * y + cellSize/2.0f, cellSize, cellSize}, {cellSize/2.0f, cellSize/2.0f}, 0.0f, WHITE);
            }
            y++;
        }
        x++;
    }
}