#include "Map.hpp"

Map::Map(float cellSize) : cellSize(cellSize), grid() {}

void Map::createCheckerBoard(size_t width, size_t height) {
    grid = std::vector(width, std::vector(height, 0));
    int last = 0;
    for (auto& column: grid) {
        for (auto& cell: column) {
            cell = !last;
            last = cell;
        }
    }
}

Vector2 Map::createFromImage(Image &image) {
    grid.clear();
    grid = std::vector(image.width, std::vector(image.height, 0));

    Vector2 marioPosition;

    for (size_t x = 0; x < grid.size(); x++) {
        for (size_t y = 0; y < grid[x].size(); ++y) {
            Color color = GetImageColor(image, x, y);
            if (color.r == 0 && color.g == 0 && color.b == 0) {
                grid[x][y] = 1;
                b2BodyDef groundBodyDef = b2DefaultBodyDef();
                groundBodyDef.position = (b2Vec2){cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f};
                b2BodyId groundId = b2CreateBody(Physics::mWorld, &groundBodyDef);
                b2Polygon groundBox = b2MakeBox(cellSize / 2.0f, cellSize / 2.0f);
                b2ShapeDef groundShapeDef = b2DefaultShapeDef();
                groundShapeDef.filter.categoryBits = 0x0004;
                groundShapeDef.enableSensorEvents = true;
                b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
            }
            else if (color.r == 255 && color.g == 0 && color.b == 0)
                marioPosition = Vector2{cellSize * x + cellSize/2.0f, cellSize * y + cellSize/2.0f};

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
                DrawTexturePro(Resource::textures["brick"], {0, 0, (float)Resource::textures["brick"].width, 
                    (float)Resource::textures["brick"].height}, {cellSize * x + cellSize/2.0f, cellSize * y + cellSize/2.0f, cellSize, cellSize}, {cellSize/2.0f, cellSize/2.0f}, 0.0f, WHITE);
            }
            y++;
        }
        x++;
    }
}