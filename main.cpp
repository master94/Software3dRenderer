#include <QApplication>

#include "canvas.hpp"
#include "renderer.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Canvas canvas(640, 480);
    canvas.show();

    Renderer renderer;
    renderer.drawLine(0, 0, 400, 200, QColor(Qt::green).rgb(), canvas);
    renderer.drawLine(0, 0, 200, 400, QColor(Qt::green).rgb(), canvas);
    renderer.drawLine(0, 200, 400, 0, QColor(Qt::blue).rgb(), canvas);

    return app.exec();
}
