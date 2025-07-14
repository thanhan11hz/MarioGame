#include "Coin.hpp"

void Coin::init() {
    mTag = "coin";

    mAnim = Animation(1.4f, {
        AnimFrame(1.3f, Resource::textures["coin14"]),
        AnimFrame(1.2f, Resource::textures["coin13"]),
        AnimFrame(1.1f, Resource::textures["coin12"]),
        AnimFrame(1.0f, Resource::textures["coin11"]),
        AnimFrame(0.9f, Resource::textures["coin10"]),
        AnimFrame(0.8f, Resource::textures["coin9"]),
        AnimFrame(0.7f, Resource::textures["coin8"]),
        AnimFrame(0.6f, Resource::textures["coin7"]),
        AnimFrame(0.5f, Resource::textures["coin6"]),
        AnimFrame(0.4f, Resource::textures["coin5"]),
        AnimFrame(0.3f, Resource::textures["coin4"]),
        AnimFrame(0.2f, Resource::textures["coin3"]),
        AnimFrame(0.1f, Resource::textures["coin2"]),
        AnimFrame(0.0f, Resource::textures["coin1"]),
    });

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = (b2Vec2){mPosition.x, mPosition.y};
    mBody = b2CreateBody(Physics::mWorld, &bodyDef);
    b2Polygon shapeBox = b2MakeBox(0.4f, 0.4f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();

    UserData* data = new UserData();
    data->type = UserDataType::OBJECT;
    data->object = this;
    shapeDef.isSensor = true;
    shapeDef.density = 1.0f;
    shapeDef.userData = (void*) data;
    shapeDef.enableSensorEvents = true;

    b2CreatePolygonShape(mBody, &shapeDef, &shapeBox);
}

void Coin::update(float dt) {
    mAnim.update(dt);
};

void Coin::draw() {
    Rectangle src = {
        0, 
        0, 
        (float)mAnim.getTexture().width, 
        (float)mAnim.getTexture().height
    };

    Rectangle dest = {
        mPosition.x, 
        mPosition.y, 
        0.8f, 
        0.8f
    };

    DrawTexturePro(mAnim.getTexture(), src, dest, {0.4f, 0.4f}, 0.0f, WHITE);
}

Coin::~Coin() {
    b2DestroyBody(mBody);
    mBody = b2_nullBodyId;
}