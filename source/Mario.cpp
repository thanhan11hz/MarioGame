#include "Mario.hpp"

const float movementSpeed = 8.0f; 

const float jumpVelocity = 12.0f;

void Mario::update(float dt) {
    float move = movementSpeed;

    mRunAnimation.update(dt);

    if (IsKeyDown(KEY_LEFT_SHIFT))
        move *= 2;

    b2Vec2 mVelocity = b2Body_GetLinearVelocity(mBody);
    mVelocity.x = 0.0f;

    if (IsKeyDown(KEY_RIGHT)) 
        mVelocity.x += move;

    if (IsKeyDown(KEY_LEFT)) 
        mVelocity.x -= move;

    if (IsKeyDown(KEY_UP) && isGrounded()) {
        mVelocity.y = -jumpVelocity;
        PlaySound(jumpSound);
    }

    mToDraw = mRunAnimation.getTexture();
        
    if (mVelocity.x < - 0.02f) {
        mFacingLeft = true;
    } else if (mVelocity.x > 0.02f) 
        mFacingLeft = false;
    else {
        mToDraw = Resource::textures["idle"];
    }

    if (!isGrounded()) mToDraw = Resource::textures["jump"];

    b2Body_SetLinearVelocity(mBody, mVelocity);

    mPosition = {b2Body_GetPosition(mBody).x, b2Body_GetPosition(mBody).y};
    angle = b2Rot_GetAngle(b2Body_GetRotation(mBody));
}

void Mario::draw() {
    Rectangle src = {
        0, 
        0, 
        (float)mToDraw.width, 
        (float)mToDraw.height
    };

    if (mFacingLeft) {
        src.x += src.width;
        src.width *= -1;
    }

    Rectangle dest = {
        mPosition.x, 
        mPosition.y, 
        1.0f, 
        2.0f
    };

    DrawTexturePro(mToDraw, src, dest, {0.5f, 1.0f}, - angle * RAD2DEG, WHITE);
}

void Mario::init() {
    mRunAnimation = Animation(0.45f, {
        AnimFrame(0.3f, Resource::textures["run3"]),
        AnimFrame(0.15f, Resource::textures["run2"]),
        AnimFrame(0.0f, Resource::textures["run1"])
    });

    mData.listener = this;
    mData.mario = this;
    mData.type = UserDataType::MARIO;

    mCoins = 0;

    jumpSound = Resource::sounds["jump"];

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){mPosition.x, mPosition.y};
    bodyDef.motionLocks.angularZ = true;
    mBody = b2CreateBody(Physics::mWorld, &bodyDef);

    b2Capsule dynamicBox = {b2Vec2{0, 0.5f}, b2Vec2{0, -0.5f}, 0.5f};

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.enableSensorEvents = true;
    shapeDef.userData = (void*)&mData;
    shapeDef.material.friction = 0.0f;
    shapeDef.density = 1.0f;
    b2CreateCapsuleShape(mBody, &shapeDef, &dynamicBox);

    b2Circle foot = {
        .center = {0.0f, 1.05f},    
        .radius = 0.15f
    };

    b2ShapeDef sd = b2DefaultShapeDef();
    sd.isSensor            = true;
    sd.enableSensorEvents  = true;
    sd.density             = 0.1f;
    // Using for contact
    // sd.filter.categoryBits = 0x0002; // FOOT
    // sd.filter.maskBits     = 0x0004; // chỉ Ground (tile/platform)
    sd.userData           = (void*)&mData;
    mFootSensorId = b2CreateCircleShape(mBody, &sd, &foot);
}

void Mario::onSensorBegin(b2ShapeId self, b2ShapeId other) {
    UserData* data = (UserData*)b2Shape_GetUserData(other);

    if (!data) return;

    if (data->type == UserDataType::MAPTILE && B2_ID_EQUALS(self, mFootSensorId)) 
        ++mFootContacts;
    else if (data->type == UserDataType::OBJECT && data->object && data->object->mTag == "coin") {
        std::cout << "Coins = " << ++mCoins << "\n";
        std::vector<Object*> &container = data->object->mContainer;
        const auto& it = std::find(container.begin(), container.end(), data->object);
        if (it != container.end()) {
            delete data->object;
            data->object = nullptr;
            container.erase(it);
        }
    }
}

void Mario::onSensorEnd(b2ShapeId self, b2ShapeId other) {

    if (!b2Shape_IsValid(other)) return;
    
    UserData* data = (UserData*)b2Shape_GetUserData(other);

    if (!data) return;

    if (data->type == UserDataType::MAPTILE && B2_ID_EQUALS(self, mFootSensorId) && mFootContacts > 0) 
        --mFootContacts;
    
}

bool Mario::isGrounded() const { 
    return mFootContacts > 0; 
}