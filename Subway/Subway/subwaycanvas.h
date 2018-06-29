//Created by 彭季超

#ifndef SUBWAYCANVAS_H
#define SUBWAYCANVAS_H

#include <QFile>
#include <QPainter>
#include <vector>
#include <QDebug>
#include <QPoint>
#include <QDialog>
#include <QMouseEvent>

using namespace std;

typedef enum
{
    READY,
    START_SURE,
    END_SURE,
    ALL_SURE,
    END
}STATE;

class SubwayCanvas : public QWidget
{
    Q_OBJECT
public:
    SubwayCanvas(QWidget *parent);
    ~SubwayCanvas();
    QPoint PointTarget;
    QPoint PointStart;
    QPoint PointEnd;
    QString StartSubwayName;
    QString EndSubwayName;
    STATE State;
    vector<int> ResultIndex;
    int ReturnSubscript(QPoint Point);



protected:
    bool DataInitFlag;
    vector<QPoint> SubwayPoints;

    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    bool ReadPointData();


Q_SIGNALS:
    void MousePressUpdate();
    void MousePressReset();
};

#endif // SUBWAYCANVAS_H
