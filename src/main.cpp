#include <QApplication>

#include <fstream>

#include <model_loaders/ObjModelLoader.hpp>
#include <canvas.hpp>
#include <renderer.hpp>
#include <geometry/point.hpp>
#include <geometry/utils.hpp>

const Vec3_<float> lightDir(0, 0, 1);
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
    if (!ifs) {
        std::cerr << "Bad file" << std::endl;
        exit(EXIT_FAILURE);
    }

    loader.load(ifs);

    const int halfWidth = 350;
    const int halfHeight = 350;
    Canvas canvas(2 * halfWidth, 2 * halfHeight);

    const auto toPoint = [](const Vertex &v) {
        return Point((v.x + 1) * halfWidth, (2 - (v.y + 1)) * halfHeight);
    };

    Renderer renderer(canvas);
    renderer.renderModel(loader.model());
    canvas.show();
    return app.exec();
}

void usage()
{
    std::cout << "Usage: <prog> obj_model_path" << std::endl;
}
