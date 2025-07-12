#include "DebugDraw.hpp"
#include <vector>

/*──────── helpers ───────*/
Color MyDebugDraw::ToRay(b2HexColor c, unsigned char a)
{
    return { (unsigned char)(c >> 16),
             (unsigned char)(c >>  8),
             (unsigned char)(c),
             a };
}

void MyDebugDraw::DrawSegment(b2Vec2 p1,b2Vec2 p2,b2HexColor col,void*)
{
    constexpr float LIMIT = 1e6f;
    if (fabsf(p1.x) > LIMIT || fabsf(p1.y) > LIMIT ||
        fabsf(p2.x) > LIMIT || fabsf(p2.y) > LIMIT)
        return;

    DrawLineEx({p1.x, p1.y}, {p2.x, p2.y}, 0.02f, ToRay(col));
}

void MyDebugDraw::DrawPolygon(const b2Vec2* v,int n,b2HexColor col,void* ctx)
{
    for(int i=0;i<n;++i) DrawSegment(v[i], v[(i+1)%n], col, ctx);
}

static inline b2Vec2 XfPoint(const b2Transform& xf,const b2Vec2& l)
{
    return { xf.p.x + xf.q.c*l.x - xf.q.s*l.y,
             xf.p.y + xf.q.s*l.x + xf.q.c*l.y };
}

void MyDebugDraw::DrawSolidPolygon(b2Transform xf,const b2Vec2* v,int n,
                                   float,b2HexColor col,void* ctx)
{
    std::vector<b2Vec2> world(n);
    for(int i=0;i<n;++i) world[i]=XfPoint(xf,v[i]);
    DrawPolygon(world.data(), n, col, ctx);
}

void MyDebugDraw::DrawCircle(b2Vec2 c,float r,b2HexColor col,void*)
{
    DrawCircleLines((int)c.x,(int)c.y,(float)r,ToRay(col));
}

void MyDebugDraw::DrawSolidCircle(b2Transform xf,float r,b2HexColor col,void*)
{
    DrawCircleV( { xf.p.x, xf.p.y }, r, Fade(ToRay(col), 0.4f) );  

    DrawCircleLines( xf.p.x, xf.p.y, r, ToRay(col) );              
}

void MyDebugDraw::DrawTransform(b2Transform xf,void* ctx)
{
    constexpr float len=0.4f;
    b2Vec2 p=xf.p;
    b2Vec2 ex={p.x+len*xf.q.c, p.y+len*xf.q.s};
    b2Vec2 ey={p.x-len*xf.q.s, p.y+len*xf.q.c};
    DrawSegment(p,ex,b2HexColor(0xff0000),ctx);
    DrawSegment(p,ey,b2HexColor(0x00ff00),ctx);
}

void MyDebugDraw::DrawPoint(b2Vec2 p,float size,b2HexColor col,void*)
{
    DrawCircleV({p.x,p.y}, size, ToRay(col));
}

void MyDebugDraw::DrawSolidCapsule(b2Vec2 p1,
                                   b2Vec2 p2,
                                   float  radius,
                                   b2HexColor col,
                                   void*  /*ctx*/)
{

    Color fill  = Fade(ToRay(col), 0.4f);     
    Color line  = ToRay(col);                 

    DrawCircleV({p1.x, p1.y}, radius, fill);
    DrawCircleV({p2.x, p2.y}, radius, fill);

    DrawCircleLines((int)p1.x, (int)p1.y, radius, line);
    DrawCircleLines((int)p2.x, (int)p2.y, radius, line);

    b2Vec2 axis = { p2.x - p1.x, p2.y - p1.y };
    float  len  = b2Length(axis);

    if (len < 1e-6f) return;                  

    axis = b2MulSV(1.0f / len, axis);         
    b2Vec2 perp = { -axis.y * radius,          
                     axis.x * radius };

    Vector2 a = { p1.x + perp.x, p1.y + perp.y };
    Vector2 b = { p2.x + perp.x, p2.y + perp.y };
    Vector2 c = { p2.x - perp.x, p2.y - perp.y };
    Vector2 d = { p1.x - perp.x, p1.y - perp.y };

    DrawTriangle(a, b, c, fill);
    DrawTriangle(c, d, a, fill);

    constexpr float EDGE_W = 0.02f;           
    DrawLineEx(a, b, EDGE_W, line);
    DrawLineEx(c, d, EDGE_W, line);
}

void MyDebugDraw::init()
{
    mDebugDraw = {};                        
    mDebugDraw.DrawSegmentFcn       = DrawSegment;
    mDebugDraw.DrawPolygonFcn       = DrawPolygon;
    mDebugDraw.DrawSolidPolygonFcn  = DrawSolidPolygon;
    mDebugDraw.DrawCircleFcn        = DrawCircle;
    mDebugDraw.DrawSolidCircleFcn   = DrawSolidCircle;
    mDebugDraw.DrawTransformFcn     = DrawTransform;
    mDebugDraw.DrawPointFcn         = DrawPoint;
    mDebugDraw.DrawSolidCapsuleFcn = DrawSolidCapsule;

    mDebugDraw.drawShapes           = true;
    mDebugDraw.drawJoints           = true;
    mDebugDraw.drawBounds           = true;      
    mDebugDraw.drawContactNormals   = true;
    mDebugDraw.useDrawingBounds   = true; 
}

void MyDebugDraw::updateBounds(const Camera2D& cam)
{
    float w = GetScreenWidth()  / cam.zoom;
    float h = GetScreenHeight() / cam.zoom;

    mDebugDraw.drawingBounds.lowerBound = { cam.target.x - w/2.f, cam.target.y - h/2.f };
    mDebugDraw.drawingBounds.upperBound = { cam.target.x + w/2.f, cam.target.y + h/2.f };
}
