#include "subwaygui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubwayGUI w;
    w.show();

    return a.exec();
}
