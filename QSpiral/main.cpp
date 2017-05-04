#include "spiralgen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpiralGen w;
    w.show();

    return a.exec();
}
