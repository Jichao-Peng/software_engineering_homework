#include "openfile.h"
#include "ui_openfile.h"

OpenFIle::OpenFIle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFIle)
{
    ui->setupUi(this);
    ui->StateEdit->clear();
}

OpenFIle::~OpenFIle()
{
    delete ui;
}

void OpenFIle::on_OpenButton_clicked()
{
    QString FileAddress;
    FileContent.clear();
    FileAddress = ui->AddressEdit->text();
    QFile File(FileAddress);
    if(!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->StateEdit->setText("Failure.");
    }
    else
    {
        while(!File.atEnd())
        {
            QByteArray line = File.readLine();
            QString Str(line);
            FileContent.append(Str);
        }
        ui->StateEdit->setText("Success!");
        Q_EMIT OpenSuccess();
    }
}

void OpenFIle::on_CloseButton_clicked()
{
    accept();
}
