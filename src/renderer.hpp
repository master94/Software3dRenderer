#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <geometry/point.hpp>
#include <geometry/triangle.hpp>

class ICanvas;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void drawLine(int x1, int y1, int x2, int y2, int color, ICanvas &canvas);
    void drawLine(const Point &p1, const Point &p2, int color, ICanvas &canvas);

    void fillTriangle(const Point &p1, const Point &p2, const Point &p3,
            int color, ICanvas &canvas);
    void fillTriangle(const Triangle &triangle, int color, ICanvas &canvas);
};

#endif //RENDERER_HPP

