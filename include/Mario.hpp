#pragma once

#include <raylib.h>
#include <box2d/box2d.h>
#include <iostream>
#include <algorithm>

#include "Resource.hpp"
#include "Physics.hpp"
#include "ContactListener.hpp"
#include "Animation.hpp"
#include "UserData.hpp"
#include "Enemy.hpp"

class Mario : public ContactListener {
    public:
        void init();
        void update(float dt);
        void onSensorBegin(b2ShapeId self, b2ShapeId other);
        void onSensorEnd(b2ShapeId self, b2ShapeId other);
        bool isGrounded() const;
        void draw();
        Vector2 mPosition{};
        float angle{};
        size_t getCoin() { return mCoins; }
    private:
        b2BodyId mBody;
        b2ShapeId  mFootSensorId {0};
        int        mFootContacts {0};
        bool mFacingLeft = false;
        Animation mRunAnimation;
        Texture2D mToDraw{};
        Sound jumpSound{};
        UserData mData{};
        size_t mCoins;
};