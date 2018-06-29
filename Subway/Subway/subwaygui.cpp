//Created by 彭季超

#include "subwaygui.h"
#include "ui_subwaygui.h"

SubwayGUI::SubwayGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubwayGUI)
{
    ui->setupUi(this);
    Canvas = new SubwayCanvas(this);
    DG = new Graph_DG(452);
    DG->ReadFile("SubwayName.txt");
    DG->createGraph();

    connect(this,SIGNAL(ButtonUpdate()),Canvas,SLOT(update()));
    connect(this,SIGNAL(ButtonUpdate()),Canvas,SLOT(update()));
    connect(Canvas,SIGNAL(MousePressReset()),this,SLOT(Reset()));
}

SubwayGUI::~SubwayGUI()
{
    delete ui;
}

void SubwayGUI::Reset()
{
    DG->reset();
    ui->EndEdit->clear();
    ui->StartEdit->clear();
    ui->ResultEdit->clear();
}

void SubwayGUI::on_StartButton_clicked()
{
    Canvas->PointStart = Canvas->PointTarget;
    Canvas->StartSubwayName = QString::fromLocal8Bit(DG->ReturnString(Canvas->ReturnSubscript(Canvas->PointStart)).c_str());
    ui->StartEdit->setText(Canvas->StartSubwayName);

    Canvas->PointTarget.setX(0);
    Canvas->PointTarget.setY(0);
    if(Canvas->State == END_SURE)
    {
        Canvas->State = ALL_SURE;

        DG->Dijkstra(string((const char *)Canvas->StartSubwayName.toLocal8Bit()),
                     string((const char *)Canvas->EndSubwayName.toLocal8Bit()),
                     DG->returnpath,
                     DG->returnindex);
        QString ResultString = QString::fromLocal8Bit(DG->returnpath.c_str());
        Canvas->ResultIndex.assign(DG->returnindex.begin(),DG->returnindex.end());
        ui->ResultEdit->setText(ResultString);
    }
    else if(Canvas->State == READY)
    {
        Canvas->State = START_SURE;
    }
    Q_EMIT(ButtonUpdate());
}

void SubwayGUI::on_EndButton_clicked()
{
    Canvas->PointEnd = Canvas->PointTarget;
    Canvas->EndSubwayName = QString::fromLocal8Bit(DG->ReturnString(Canvas->ReturnSubscript(Canvas->PointEnd)).c_str());
    ui->EndEdit->setText(Canvas->EndSubwayName);

    Canvas->PointTarget.setX(0);
    Canvas->PointTarget.setY(0);
    if(Canvas->State == START_SURE)
    {
        Canvas->State = ALL_SURE;

        DG->Dijkstra(string((const char *)Canvas->StartSubwayName.toLocal8Bit()),
                     string((const char *)Canvas->EndSubwayName.toLocal8Bit()),
                     DG->returnpath,
                     DG->returnindex);
        QString ResultString = QString::fromLocal8Bit(DG->returnpath.c_str());
        Canvas->ResultIndex.assign(DG->returnindex.begin(),DG->returnindex.end());
        ui->ResultEdit->setText(ResultString);
    }
    else if(Canvas->State == READY)
    {
        Canvas->State = END_SURE;
    }
    Q_EMIT(ButtonUpdate());
}
