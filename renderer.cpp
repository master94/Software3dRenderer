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
