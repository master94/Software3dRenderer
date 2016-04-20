#include <QApplication>

#include <fstream>

#include <model_loaders/ObjModelLoader.hpp>
#include <canvas.hpp>
#include <renderer.hpp>

void usage();

int main(int argc, char **argv)
{
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    QApplication app(argc, argv);
    ObjModelLoader loader;

    std::ifstream ifs(argv[1]);
    loader.load(ifs);

    const int halfWidth = 350;
    const int halfHeight = 350;
    Canvas canvas(2 * halfWidth, 2 * halfHeight);

    Renderer renderer;
    const QRgb color = QColor(Qt::white).rgb();

    Model model = loader.model();
    for (auto &face : model.faces) {
        Vertex *v = face.points;
        
        for (size_t j = 0; j < 3; ++j) {
            const size_t p1 = j;
            const size_t p2 = (j + 1) % 3;

            const int x1 = (v[p1].x + 1) * halfWidth;
            const int y1 = (2 - (v[p1].y + 1)) * halfHeight;
            const int x2 = (v[p2].x + 1) * halfWidth;
            const int y2 = (2 - (v[p2].y + 1)) * halfHeight;

            renderer.drawLine(x1, y1, x2, y2, color, canvas);
        }
    }

    canvas.show();
    return app.exec();
}

void usage()
{
    std::cout << "Usage: <prog> obj_model_path" << std::endl;
}
