#include "renderer.hpp"

#include <cmath>
#include <iostream>

#include <geometry/point.hpp>
#include <geometry/rect.hpp>
#include <geometry/vec.hpp>
#include <geometry/triangle.hpp>
#include <geometry/utils.hpp>
#include <ICanvas.hpp>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, int color, ICanvas &canvas)
{
    const bool highSlope = abs(y2 - y1) > abs(x2 - x1);
    if (highSlope) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x2 < x1) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int currY = y1;
    int errY = 0;
    for (int x = x1; x <= x2; ++x) {
        if (highSlope)
            canvas.setPixelColor(currY, x, color);
        else
            canvas.setPixelColor(x, currY, color);

        errY += 2 * abs(dy);

        if (errY > dx) {
            currY += (dy > 0 ? +1 : -1);
            errY -= 2 * dx;
        }
    }
}

void Renderer::drawLine(const Point &p1, const Point &p2, int color, ICanvas &canvas)
{
    drawLine(p1.x, p1.y, p2.x, p2.y, color, canvas);
}

void Renderer::fillTriangle(const Point &p1, const Point &p2, const Point &p3,
        int color, ICanvas &canvas)
{
    drawLine(p1, p2, color, canvas);
    drawLine(p2, p3, color, canvas);
    drawLine(p3, p1, color, canvas);

    std::vector<Point> ps{ p1, p2, p3 };
    const auto brect = boundingRect<std::vector, int>(ps);

    Triangle tr(p1, p2, p3);

    for (int i = 0; i < brect.height; ++i) {
        for (int j = 0; j < brect.width; ++j) {
            if (isPointInsideTriangle(Point(brect.left + j, brect.top + i), tr))
                canvas.setPixelColor(brect.left + j, brect.top + i, color);
        }
    }
}

void Renderer::fillTriangle(const Triangle &triangle, int color, ICanvas &canvas)
{
    fillTriangle(triangle.p1, triangle.p2, triangle.p3, color, canvas);
}
