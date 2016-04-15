#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>
#include <QImage>

#include "ICanvas.hpp"

class Canvas : public ICanvas, public QWidget
{
public:
    Canvas(int width, int height, QWidget *parent = nullptr);

    QRgb pixelColor(int x, int y) const override;
    void setPixelColor(int x, int y, QRgb color) override;

    QSize canvasSize() const override;

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QImage mImage;

};

#endif // CANVAS_HPP
