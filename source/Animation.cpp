#include "Animation.hpp"

Animation::Animation(float length, std::vector<AnimFrame> frame) : mFrame(frame), mLength(length) {}

void Animation::update(float dt) {
    mTime += dt;
}

Texture2D Animation::getTexture() {
    while (mTime >= mLength) {
        mTime -= mLength;
    }

    for (auto frame: mFrame) {
        if (frame.mTime <= mTime) {
            return frame.mTexture;
        }
    }

    return Texture2D();
}