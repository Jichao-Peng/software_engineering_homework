#ifndef SUBWAYFORCOLLECT_H
#define SUBWAYFORCOLLECT_H

#include <QDialog>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include "subwaycanvas.h"

namespace Ui {
class SubwayForCollect;
}

class SubwayForCollect : public QDialog
{
    Q_OBJECT

public:
    explicit SubwayForCollect(QWidget *parent = 0);
    ~SubwayForCollect();

private slots:
    void on_SaveButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::SubwayForCollect *ui;
    SubwayCanvas *Canvas;
};

#endif // SUBWAYFORCOLLECT_H
