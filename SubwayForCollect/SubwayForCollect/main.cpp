#include "subwayforcollect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubwayForCollect w;
    w.show();

    return a.exec();
}
