#include "renderer.hpp"

#include <cmath>
#include "ICanvas.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, int color, ICanvas &canvas)
{
    if (x2 < x1) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    const bool highSlope = abs(dy) > abs(dx);
    if (highSlope) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
    }

    const int slope = dy;

    int currY = y1;
    long errY = 0;
    for (int x = x1; x <= x2; ++x) {
        if (highSlope)
            canvas.setPixelColor(currY, x, color);
        else
            canvas.setPixelColor(x, currY, color);

        errY += slope;

        if (labs(errY) > abs(dx)) {
            currY += (slope > 0 ? +1 : -1);
            errY -= 2 * dy;
        }
    }
}
