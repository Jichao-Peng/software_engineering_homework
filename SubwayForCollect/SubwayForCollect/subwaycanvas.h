#ifndef SUBWAYCANVAS_H
#define SUBWAYCANVAS_H

#include <QDebug>
#include <QDialog>
#include <QPoint>
#include <vector>
#include <QMouseEvent>

using namespace std;

class SubwayCanvas : public QWidget
{
    Q_OBJECT
public:
    SubwayCanvas(QWidget *parent);
    ~SubwayCanvas();
    vector<QPoint> SubwayPoints;
    QPoint PointPre;
    int Cnt;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // SUBWAYCANVAS_H
