#pragma once

class ContactListener {
    public:
        virtual void onSensorBegin(b2ShapeId self, b2ShapeId other) = 0;
        virtual void onSensorEnd(b2ShapeId self, b2ShapeId other) = 0;
};