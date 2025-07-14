#include "Enemy.hpp"

Enemy::Enemy(std::vector<Object*> &object) : Object(object) {}

void Enemy::init() {
    mTag = "enemy";

    mAnim = Animation(0.5f, {
        AnimFrame(0.25f, Resource::textures["enemy2"]),
        AnimFrame(0.0f, Resource::textures["enemy1"])
    });

    mData.type = UserDataType::OBJECT;
    mData.object = this;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{mPosition.x, mPosition.y};
    bodyDef.motionLocks.angularZ = true;
    mBody = b2CreateBody(Physics::mWorld, &bodyDef);

    b2Circle dynamicBox = {b2Vec2{0, 0.0f}, 0.5f};
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.enableSensorEvents = true;
    shapeDef.userData = (void*)&mData;
    shapeDef.material.friction = 0.0f;
    shapeDef.density = 1.0f;
    b2CreateCircleShape(mBody, &shapeDef, &dynamicBox);
}

void Enemy::update(float dt) {
    if (isDead) {
        destroyTimer += dt;
            if (destroyTimer >= 3.0f) {
            std::vector<Object*> &container = this->mContainer;
            const auto& it = std::find(container.begin(), container.end(), this);
            if (it != container.end()) {
                container.erase(it);
                delete this;
            }
        }
        
        return;
    }


    mAnim.update(dt);

    b2Vec2 mVelocity = b2Body_GetLinearVelocity(mBody);

    if (mVelocity.x <= 0.02f && mVelocity.x >= -0.02f) mMovement *= -1;

    mVelocity.x = mMovement;

    b2Body_SetLinearVelocity(mBody, b2Vec2{mVelocity.x, mVelocity.y});

    mPosition = Vector2{b2Body_GetPosition(mBody).x, b2Body_GetPosition(mBody).y};
    mAngle = b2Rot_GetAngle(b2Body_GetRotation(mBody));
}
        
void Enemy::draw() {
    Rectangle src = {
        0, 
        0, 
        (float)mAnim.getTexture().width, 
        (float)mAnim.getTexture().height
    };

    Rectangle dest = {
        mPosition.x, 
        mPosition.y, 
        1.0f, 
        isDead ? 0.0f : 1.0f
    };

    DrawTexturePro(mAnim.getTexture(), src, dest, {0.5f, 0.5f}, - mAngle * RAD2DEG, WHITE);
}

void Enemy::die() {
    isDead = true;
    b2DestroyBody(mBody);
}