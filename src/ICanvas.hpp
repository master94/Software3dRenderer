#ifndef ICANVAS_HPP
#define ICANVAS_HPP

#include <QSize>
#include <QColor>

class ICanvas
{
public:
    virtual ~ICanvas() {}

    virtual QRgb pixelColor(int x, int y) const = 0;
    virtual void setPixelColor(int x, int y, QRgb color) = 0;

    virtual QSize canvasSize() const = 0;
};

#endif // ICANVAS_HPP
