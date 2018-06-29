#include "wordchain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WordChain w;
    w.show();

    return a.exec();
}
