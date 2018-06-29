//Created by 彭季超

#ifndef SUBWAYGUI_H
#define SUBWAYGUI_H

#include <QDialog>
#include "subwaycanvas.h"
#include "Dijkstra.h"

namespace Ui {
class SubwayGUI;
}

class SubwayGUI : public QDialog
{
    Q_OBJECT

public:
    explicit SubwayGUI(QWidget *parent = 0);
    ~SubwayGUI();

private slots:
    void on_StartButton_clicked();

    void on_EndButton_clicked();

    void Reset();

private:
    Ui::SubwayGUI *ui;
    SubwayCanvas *Canvas;
    Graph_DG *DG;

Q_SIGNALS:
    void ButtonUpdate();
};

#endif // SUBWAYGUI_H
