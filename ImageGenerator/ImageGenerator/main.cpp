#include "ImageGenerator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ImageGenerator window;
    window.show();
    return app.exec();
}
