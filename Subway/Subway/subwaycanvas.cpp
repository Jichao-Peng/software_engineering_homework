//Created by 彭季超
#include "subwaycanvas.h"

SubwayCanvas::SubwayCanvas(QWidget *parent):QWidget(parent)
{
    this->setGeometry(QRect(10,20,730,730));    
    DataInitFlag = ReadPointData();
    State = READY;

    connect(this,SIGNAL(MousePressUpdate()),this,SLOT(update()));
}

SubwayCanvas::~SubwayCanvas()
{

}

void SubwayCanvas::paintEvent(QPaintEvent *event)
{
    if(State == READY)
    {
        if(PointTarget.x() != 0 || PointTarget.y() != 0)
        {
            QPainter Painter(this);
            Painter.setPen(QPen(Qt::red,3));
            Painter.drawEllipse(PointTarget.x()-5,PointTarget.y()-5,10,10);
        }
    }
    if(State == START_SURE)
    {
        //画起始点
        QBrush Brush(Qt::SolidPattern);
        Brush.setColor(Qt::red);

        QPainter Painter(this);
        Painter.setPen(QPen(Qt::red,2));
        Painter.drawEllipse(PointStart.x()-8,PointStart.y()-8,16,16);

        Painter.setBrush(Brush);
        Painter.setPen(QPen(Qt::red,1));
        Painter.drawEllipse(PointStart.x()-5,PointStart.y()-5,10,10);

        if(PointTarget.x() != 0 || PointTarget.y() != 0)
        {
            QPainter Painter2(this);
            Painter2.setPen(QPen(Qt::green,3));
            Painter2.drawEllipse(PointTarget.x()-5,PointTarget.y()-5,10,10);
        }
    }
    if(State == END_SURE)
    {
        //画终止点
        QBrush Brush(Qt::SolidPattern);
        Brush.setColor(Qt::green);

        QPainter Painter(this);
        Painter.setPen(QPen(Qt::green,2));
        Painter.drawEllipse(PointEnd.x()-8,PointEnd.y()-8,16,16);

        Painter.setBrush(Brush);
        Painter.setPen(QPen(Qt::green,1));
        Painter.drawEllipse(PointEnd.x()-5,PointEnd.y()-5,10,10);

        if(PointTarget.x() != 0 || PointTarget.y() != 0)
        {
            QPainter Painter2(this);
            Painter2.setPen(QPen(Qt::red,3));
            Painter2.drawEllipse(PointTarget.x()-5,PointTarget.y()-5,10,10);
        }
    }
    if(State == ALL_SURE)
    {
        //画起始点&终止点
        QBrush Brush(Qt::SolidPattern);
        Brush.setColor(Qt::red);

        QPainter Painter(this);
        Painter.setPen(QPen(Qt::red,2));
        Painter.drawEllipse(PointStart.x()-8,PointStart.y()-8,16,16);

        Painter.setBrush(Brush);
        Painter.setPen(QPen(Qt::red,1));
        Painter.drawEllipse(PointStart.x()-5,PointStart.y()-5,10,10);

        QBrush Brush2(Qt::SolidPattern);
        Brush2.setColor(Qt::green);

        QPainter Painter2(this);
        Painter2.setPen(QPen(Qt::green,2));
        Painter2.drawEllipse(PointEnd.x()-8,PointEnd.y()-8,16,16);

        Painter2.setBrush(Brush2);
        Painter2.setPen(QPen(Qt::green,1));
        Painter2.drawEllipse(PointEnd.x()-5,PointEnd.y()-5,10,10);

        //画结果
        if(ResultIndex.size() != 0)
        {
            vector<int>::iterator it;
            int PreIndex,i=0;
            QPainter Painter3(this);

            for(it = ResultIndex.begin(); it != ResultIndex.end(); it++)
            {
                if(i != 0)
                {
                    Painter3.setPen(QPen(Qt::green,2));
                    Painter.drawEllipse(SubwayPoints.at(*it).x()-5,SubwayPoints.at(*it).y()-5,10,10);
                }
                if(i != 0 && i != 1)
                {
                    Painter3.setPen(QPen(Qt::green,4));
                    Painter.drawLine(SubwayPoints.at(*it).x(),SubwayPoints.at(*it).y(),SubwayPoints.at(PreIndex).x(),SubwayPoints.at(PreIndex).y());
                }
                PreIndex = *it;
                i++;
            }
        }


    }
    if(State == END)
    {
        State = READY;
        Q_EMIT MousePressReset();
    }
}

void SubwayCanvas::mousePressEvent(QMouseEvent *event)
{
    if(State != ALL_SURE)
    {
        QPoint PointCurrent;
        int Distance;
        bool FirstFLag = true;
        PointCurrent.setX(event->pos().x());
        PointCurrent.setY(event->pos().y());

        vector<QPoint>::iterator it;
        for(it = SubwayPoints.begin(); it != SubwayPoints.end(); it++)
        {
            if(FirstFLag)
            {
                PointTarget = *it;
                Distance = abs(PointCurrent.x() - it->x())+abs(PointCurrent.y() - it->y());
                FirstFLag = false;
            }
            else
            {
                if((abs(PointCurrent.x() - it->x()) + abs(PointCurrent.y() - it->y())) < Distance)
                {
                    PointTarget = *it;
                    Distance = abs(PointCurrent.x() - it->x())+abs(PointCurrent.y() - it->y());
                }
            }
        }
        qDebug()<<PointTarget.x()<<" "<<PointTarget.y()<<endl;

        Q_EMIT MousePressUpdate();
    }
    else
    {
        PointStart.setX(0);
        PointStart.setY(0);
        PointEnd.setX(0);
        PointEnd.setY(0);
        State = END;
        Q_EMIT MousePressUpdate();
    }
}

bool SubwayCanvas::ReadPointData()
{
    QFile File("Point.txt");
    SubwayPoints.clear();
    if(File.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream Stream(&File);
        while(1)
        {
            QStringList PointList = Stream.readLine().split(" ");
            if(PointList.size() == 2)
            {
                QPoint Point;
                Point.setX(PointList.at(0).toInt());
                Point.setY(PointList.at(1).toInt());
                SubwayPoints.push_back(Point);
            }
            else
            {
                qDebug()<<"Data Init Finish!"<<endl;
                break;
            }
        }
        qDebug()<<"The Size of Point is "<<SubwayPoints.size()<<endl;
        return true;
    }
    else
    {
        qDebug()<<"Can't Open Data!"<<endl;
        return false;
    }
}

int SubwayCanvas::ReturnSubscript(QPoint Point)
{
    for(unsigned int i = 0; i<SubwayPoints.size(); i++)
    {
        if(SubwayPoints.at(i) == Point)
        {
            return i;
        }
    }
}







