/********************************************************************************
** Form generated from reading UI file 'subwayforcollect.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWAYFORCOLLECT_H
#define UI_SUBWAYFORCOLLECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SubwayForCollect
{
public:
    QWidget *widget;
    QPushButton *SaveButton;
    QLineEdit *FileNameEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *SubwayForCollect)
    {
        if (SubwayForCollect->objectName().isEmpty())
            SubwayForCollect->setObjectName(QStringLiteral("SubwayForCollect"));
        SubwayForCollect->resize(1227, 764);
        widget = new QWidget(SubwayForCollect);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 20, 730, 730));
        widget->setStyleSheet(QStringLiteral("background-image: url(:/Resource/xianluda.jpg);"));
        SaveButton = new QPushButton(SubwayForCollect);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        SaveButton->setGeometry(QRect(760, 70, 161, 81));
        FileNameEdit = new QLineEdit(SubwayForCollect);
        FileNameEdit->setObjectName(QStringLiteral("FileNameEdit"));
        FileNameEdit->setGeometry(QRect(760, 20, 161, 31));
        pushButton = new QPushButton(SubwayForCollect);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(760, 220, 161, 81));

        retranslateUi(SubwayForCollect);

        QMetaObject::connectSlotsByName(SubwayForCollect);
    } // setupUi

    void retranslateUi(QDialog *SubwayForCollect)
    {
        SubwayForCollect->setWindowTitle(QApplication::translate("SubwayForCollect", "SubwayForCollect", Q_NULLPTR));
        SaveButton->setText(QApplication::translate("SubwayForCollect", "Save", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SubwayForCollect", "Reset", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SubwayForCollect: public Ui_SubwayForCollect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWAYFORCOLLECT_H
