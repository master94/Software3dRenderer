#include <QApplication>

#include "canvas.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Canvas canvas(640, 480);
    canvas.show();

    for (int i = 0; i < 400; ++i) {
        canvas.setPixelColor(i, i, QColor(255, 0, 0).rgb());
    }
    return app.exec();
}
