#include "canvas.hpp"

#include <QPainter>
#include <QPaintEvent>

Canvas::Canvas(int width, int height, QWidget *parent)
    : QWidget(parent)
    , mImage(width, height, QImage::Format_RGB888)
{
    setFixedSize(width, height);
}

QRgb Canvas::pixelColor(int x, int y) const
{
    return mImage.pixel(x, y);
}

void Canvas::setPixelColor(int x, int y, QRgb color)
{
    mImage.setPixel(x, y, color);
}

QSize Canvas::canvasSize() const
{
    return mImage.size();
}

void Canvas::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.drawImage(0, 0, mImage);
}
