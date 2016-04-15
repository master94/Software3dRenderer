#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>
#include <QImage>

class Canvas : public QWidget
{
public:
    Canvas(int width, int height, QWidget *parent = nullptr);

    QRgb pixelColor(int x, int y) const;
    void setPixelColor(int x, int y, QRgb color);

    QSize canvasSize() const;

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QImage mImage;

};

#endif // CANVAS_HPP
