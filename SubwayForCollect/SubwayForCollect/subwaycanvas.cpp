#include "subwaycanvas.h"

SubwayCanvas::SubwayCanvas(QWidget *parent):QWidget(parent)
{
    this->setGeometry(QRect(10,20,730,730));
    Cnt = 0;
    PointPre.setX(0);
    PointPre.setY(0);
}

SubwayCanvas::~SubwayCanvas()
{

}

void SubwayCanvas::mousePressEvent(QMouseEvent *event)
{
    Cnt++;
    QPoint Point;
    int PointXDiff;
    int PointYDiff;

    PointXDiff = abs(PointPre.x() - event->pos().x());
    PointYDiff = abs(PointPre.y() - event->pos().y());

    if(PointXDiff < 5)
    {
        Point.setX(PointPre.x());
    }
    else
    {
        Point.setX(event->pos().x());
    }

    if(PointYDiff < 5)
    {
        Point.setY(PointPre.y());
    }
    else
    {
        Point.setY(event->pos().y());
    }

    PointPre = Point;

    SubwayPoints.push_back(Point);
    qDebug()<<"["<<Cnt<<"]"<<":"<<Point.x()<<" "<<Point.y()<<endl;
}

