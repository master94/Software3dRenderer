#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <geometry/point.hpp>
#include <geometry/triangle.hpp>

class ICanvas;

class Renderer
{
public:
    Renderer(ICanvas &canvas);
    ~Renderer();

    void drawLine(int x1, int y1, int x2, int y2, int color);
    void drawLine(const Point &p1, const Point &p2, int color);

    void fillTriangle(const Point &p1, const Point &p2, const Point &p3, int color);
    void fillTriangle(const Triangle &triangle, int color);

private:
    ICanvas &mCanvas;

};

#endif //RENDERER_HPP

