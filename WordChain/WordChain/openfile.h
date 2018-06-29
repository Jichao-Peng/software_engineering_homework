#ifndef OPENFILE_H
#define OPENFILE_H

#include <QDialog>
#include <QFile>
#include <QDebug>

namespace Ui {
class OpenFIle;
}

class OpenFIle : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFIle(QWidget *parent = 0);
    ~OpenFIle();
    QString FileContent;

private slots:
    void on_OpenButton_clicked();

    void on_CloseButton_clicked();

private:
    Ui::OpenFIle *ui;

Q_SIGNALS:
    void OpenSuccess();

};

#endif // OPENFILE_H
