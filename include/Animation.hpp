#pragma once

#include <vector>
#include <iostream>
#include <raylib.h>

struct AnimFrame {
    AnimFrame(float time = 0.0f, Texture2D texture = Texture2D{}) : mTime(time), mTexture(texture) {}
    float mTime = 0.0f;
    Texture2D mTexture{};
};

class Animation {
    public:
        Animation(float length = 0.0f, std::vector<AnimFrame> frame = std::vector<AnimFrame>{});
        void update(float dt);
        Texture2D getTexture();
    private:
        float mTime = 0.f;
        float mLength;
        std::vector<AnimFrame> mFrame;
};