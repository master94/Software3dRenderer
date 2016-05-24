#include <QApplication>

#include <fstream>

#include <model_loaders/ObjModelLoader.hpp>
#include <canvas.hpp>
#include <renderer.hpp>
#include <geometry/point.hpp>
#include <geometry/utils.hpp>

#include <3dparty/tgaimage.h>

const Vec3_<float> lightDir(0, 0, 1);
void usage();

int main(int argc, char **argv)
{
    if (argc != 3) {
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

    TGAImage texture;
    if (!texture.read_tga_file(argv[2])) {
        std::cerr << "Cant load TGA texture: " << argv[2] << std::endl;
        exit(1);
    }

    Renderer renderer(canvas);
    renderer.renderModel(loader.model(), texture);
    canvas.show();

    return app.exec();
}

void usage()
{
    std::cout << "Usage: <prog> obj_model_path tga_texture" << std::endl;
}
