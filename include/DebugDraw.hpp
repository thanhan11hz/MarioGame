#pragma once
#include <box2d/box2d.h>
#include <raylib.h>

class MyDebugDraw {
public:
    b2DebugDraw mDebugDraw{};          

    void init();
    void updateBounds(const Camera2D& cam);           
private:
    static Color ToRay(b2HexColor c, unsigned char a = 255);

    static void DrawSegment     (b2Vec2 p1, b2Vec2 p2, b2HexColor c, void*);
    static void DrawPolygon     (const b2Vec2* v, int n, b2HexColor c, void*);
    static void DrawSolidPolygon(b2Transform xf, const b2Vec2* v, int n, float /*r*/, b2HexColor c, void*);
    static void DrawCircle      (b2Vec2 center, float r, b2HexColor c, void*);
    static void DrawSolidCircle (b2Transform xf, float r, b2HexColor c, void*);
    static void DrawTransform   (b2Transform xf, void*);
    static void DrawPoint       (b2Vec2 p, float size, b2HexColor c, void*);
    static void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
};
