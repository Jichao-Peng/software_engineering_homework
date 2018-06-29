#ifndef WORDCHAIN_H
#define WORDCHAIN_H

#include <QDialog>
#include <QTime>
#include "algorithm.h"
#include "openfile.h"

namespace Ui {
class WordChain;
}

class WordChain : public QDialog
{
    Q_OBJECT

public:
    explicit WordChain(QWidget *parent = 0);
    ~WordChain();


private slots:
    void on_StartButton_clicked();

    void on_ResetButton_clicked();

    void on_FileButton_clicked();

private:
    Ui::WordChain *ui;    
    Algorithm* WordChainAlg;
    OpenFIle* File;

private slots:
    void InputFileContent();
};

#endif // WORDCHAIN_H
