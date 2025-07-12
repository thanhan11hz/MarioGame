#include "Physics.hpp"

b2WorldId Physics::mWorld{};
MyDebugDraw Physics::mDraw{};

void Physics::init() {
    b2Vec2 gravity = {0.0f, 10.0f};
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = gravity;
    mWorld = b2CreateWorld(&worldDef);
    mDraw.init();
}

void Physics::update(float dt) {
    b2World_Step(mWorld, dt, 4);
    updateSensor();
}

void Physics::debugDraw() {
    b2World_Draw(mWorld, &mDraw.mDebugDraw);
}

void Physics::updateSensor() {

    b2SensorEvents se = b2World_GetSensorEvents(mWorld);

    for (int i = 0; i < se.beginCount; ++i) {

        const b2SensorBeginTouchEvent& e = se.beginEvents[i];

        ContactListener* sensorOwner  = (ContactListener*)b2Shape_GetUserData(e.sensorShapeId);
        ContactListener* otherVisitor = (ContactListener*)b2Shape_GetUserData(e.visitorShapeId);

        if (sensorOwner)  sensorOwner->onSensorBegin(e.sensorShapeId, e.visitorShapeId);
        if (otherVisitor) otherVisitor->onSensorBegin(e.visitorShapeId, e.sensorShapeId);

    }

    for (int i = 0; i < se.endCount; ++i) {

        const b2SensorEndTouchEvent& e = se.endEvents[i];

        ContactListener* sensorOwner  = (ContactListener*)b2Shape_GetUserData(e.sensorShapeId);
        ContactListener* otherVisitor = (ContactListener*)b2Shape_GetUserData(e.visitorShapeId);

        if (sensorOwner)  sensorOwner->onSensorEnd(e.sensorShapeId, e.visitorShapeId);
        if (otherVisitor) otherVisitor->onSensorEnd(e.visitorShapeId, e.sensorShapeId);
    }
}