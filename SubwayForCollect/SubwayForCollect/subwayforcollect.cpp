#include "subwayforcollect.h"
#include "ui_subwayforcollect.h"

SubwayForCollect::SubwayForCollect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubwayForCollect)
{
    ui->setupUi(this);
    Canvas = new SubwayCanvas(this);
}

SubwayForCollect::~SubwayForCollect()
{
    delete ui;
}

void SubwayForCollect::on_SaveButton_clicked()
{
    QString FileName = ui->FileNameEdit->text();
    QFile File(FileName);
    if(File.open(QFile::WriteOnly))
    {
        QTextStream S(&File);
        vector<QPoint>::iterator it;
        for(it = Canvas->SubwayPoints.begin(); it != Canvas->SubwayPoints.end(); it++)
        {
            QPoint Point = *it;
            S <<Point.x()<<" "<<Point.y()<<"\n";
        }
        File.close();
    }
    else
    {
        qDebug()<<"Failed to Open File"<<endl;
    }

}

void SubwayForCollect::on_pushButton_clicked()
{
    Canvas->SubwayPoints.clear();
    Canvas->Cnt = 0;
    Canvas->PointPre.setX(0);
    Canvas->PointPre.setY(0);
}
