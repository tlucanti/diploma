/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "adcqwtplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *layoutPlots;
    AdcQwtPlot *qwtPlotter;
    AdcQwtPlot *qwtSpectr;
    QVBoxLayout *layoutControl;
    QLineEdit *editRemoteIp;
    QCheckBox *chkRfPwr;
    QPushButton *bttnLoadVga;
    QFormLayout *formLayout;
    QSpinBox *editVgaCh1;
    QLabel *labelCh1;
    QLabel *labelCh2;
    QSpinBox *editVgaCh2;
    QLabel *labelCh3;
    QSpinBox *editVgaCh3;
    QLabel *labelCh4;
    QSpinBox *editVgaCh4;
    QPushButton *bttnSetVga;
    QPushButton *bttnStoreVga;
    QSpacerItem *verticalSpacer;
    QLineEdit *editSetIP;
    QLineEdit *editSetMAC;
    QPushButton *bttnSendIP;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        layoutPlots = new QVBoxLayout();
        layoutPlots->setObjectName(QString::fromUtf8("layoutPlots"));
        qwtPlotter = new AdcQwtPlot(centralwidget);
        qwtPlotter->setObjectName(QString::fromUtf8("qwtPlotter"));

        layoutPlots->addWidget(qwtPlotter);

        qwtSpectr = new AdcQwtPlot(centralwidget);
        qwtSpectr->setObjectName(QString::fromUtf8("qwtSpectr"));

        layoutPlots->addWidget(qwtSpectr);


        horizontalLayout->addLayout(layoutPlots);

        layoutControl = new QVBoxLayout();
        layoutControl->setObjectName(QString::fromUtf8("layoutControl"));
        editRemoteIp = new QLineEdit(centralwidget);
        editRemoteIp->setObjectName(QString::fromUtf8("editRemoteIp"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(editRemoteIp->sizePolicy().hasHeightForWidth());
        editRemoteIp->setSizePolicy(sizePolicy);

        layoutControl->addWidget(editRemoteIp);

        chkRfPwr = new QCheckBox(centralwidget);
        chkRfPwr->setObjectName(QString::fromUtf8("chkRfPwr"));
        chkRfPwr->setLayoutDirection(Qt::RightToLeft);
        chkRfPwr->setChecked(true);

        layoutControl->addWidget(chkRfPwr);

        bttnLoadVga = new QPushButton(centralwidget);
        bttnLoadVga->setObjectName(QString::fromUtf8("bttnLoadVga"));

        layoutControl->addWidget(bttnLoadVga);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        editVgaCh1 = new QSpinBox(centralwidget);
        editVgaCh1->setObjectName(QString::fromUtf8("editVgaCh1"));
        editVgaCh1->setMaximum(1250);
        editVgaCh1->setSingleStep(10);
        editVgaCh1->setValue(800);

        formLayout->setWidget(0, QFormLayout::FieldRole, editVgaCh1);

        labelCh1 = new QLabel(centralwidget);
        labelCh1->setObjectName(QString::fromUtf8("labelCh1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelCh1);

        labelCh2 = new QLabel(centralwidget);
        labelCh2->setObjectName(QString::fromUtf8("labelCh2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelCh2);

        editVgaCh2 = new QSpinBox(centralwidget);
        editVgaCh2->setObjectName(QString::fromUtf8("editVgaCh2"));
        editVgaCh2->setMaximum(1250);
        editVgaCh2->setSingleStep(10);
        editVgaCh2->setValue(800);

        formLayout->setWidget(1, QFormLayout::FieldRole, editVgaCh2);

        labelCh3 = new QLabel(centralwidget);
        labelCh3->setObjectName(QString::fromUtf8("labelCh3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelCh3);

        editVgaCh3 = new QSpinBox(centralwidget);
        editVgaCh3->setObjectName(QString::fromUtf8("editVgaCh3"));
        editVgaCh3->setMaximum(1250);
        editVgaCh3->setSingleStep(10);
        editVgaCh3->setValue(800);

        formLayout->setWidget(2, QFormLayout::FieldRole, editVgaCh3);

        labelCh4 = new QLabel(centralwidget);
        labelCh4->setObjectName(QString::fromUtf8("labelCh4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelCh4);

        editVgaCh4 = new QSpinBox(centralwidget);
        editVgaCh4->setObjectName(QString::fromUtf8("editVgaCh4"));
        editVgaCh4->setMaximum(1250);
        editVgaCh4->setSingleStep(10);
        editVgaCh4->setValue(800);

        formLayout->setWidget(3, QFormLayout::FieldRole, editVgaCh4);


        layoutControl->addLayout(formLayout);

        bttnSetVga = new QPushButton(centralwidget);
        bttnSetVga->setObjectName(QString::fromUtf8("bttnSetVga"));

        layoutControl->addWidget(bttnSetVga);

        bttnStoreVga = new QPushButton(centralwidget);
        bttnStoreVga->setObjectName(QString::fromUtf8("bttnStoreVga"));

        layoutControl->addWidget(bttnStoreVga);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutControl->addItem(verticalSpacer);

        editSetIP = new QLineEdit(centralwidget);
        editSetIP->setObjectName(QString::fromUtf8("editSetIP"));

        layoutControl->addWidget(editSetIP);

        editSetMAC = new QLineEdit(centralwidget);
        editSetMAC->setObjectName(QString::fromUtf8("editSetMAC"));

        layoutControl->addWidget(editSetMAC);

        bttnSendIP = new QPushButton(centralwidget);
        bttnSendIP->setObjectName(QString::fromUtf8("bttnSendIP"));

        layoutControl->addWidget(bttnSendIP);


        horizontalLayout->addLayout(layoutControl);

        horizontalLayout->setStretch(0, 15);
        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(bttnSetVga, SIGNAL(pressed()), MainWindow, SLOT(setVga()));
        QObject::connect(bttnLoadVga, SIGNAL(pressed()), MainWindow, SLOT(loadVga()));
        QObject::connect(bttnStoreVga, SIGNAL(pressed()), MainWindow, SLOT(storeVga()));
        QObject::connect(bttnSendIP, SIGNAL(pressed()), MainWindow, SLOT(setUdpHost()));
        QObject::connect(editRemoteIp, SIGNAL(editingFinished()), MainWindow, SLOT(remoteAddrEdited()));
        QObject::connect(chkRfPwr, SIGNAL(toggled(bool)), MainWindow, SLOT(setRfPower(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        editRemoteIp->setInputMask(QApplication::translate("MainWindow", "000.000.000.000;_", nullptr));
        editRemoteIp->setText(QApplication::translate("MainWindow", "192.168.0.100", nullptr));
        chkRfPwr->setText(QApplication::translate("MainWindow", "\320\237\320\270\321\202\320\260\320\275\320\270\320\265 \320\241\320\222\320\247 \320\262\320\272\320\273.", nullptr));
        bttnLoadVga->setText(QApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        editVgaCh1->setSuffix(QApplication::translate("MainWindow", " \320\274\320\222", nullptr));
        labelCh1->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\260\320\273 1", nullptr));
        labelCh2->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\260\320\273 2", nullptr));
        editVgaCh2->setSuffix(QApplication::translate("MainWindow", " \320\274\320\222", nullptr));
        labelCh3->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\260\320\273 3", nullptr));
        editVgaCh3->setSuffix(QApplication::translate("MainWindow", " \320\274\320\222", nullptr));
        labelCh4->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\260\320\273 4", nullptr));
        editVgaCh4->setSuffix(QApplication::translate("MainWindow", " \320\274\320\222", nullptr));
        bttnSetVga->setText(QApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        bttnStoreVga->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        editSetIP->setInputMask(QApplication::translate("MainWindow", "000.000.000.000;_", nullptr));
        editSetIP->setText(QApplication::translate("MainWindow", "192.168.0.2", nullptr));
        editSetMAC->setInputMask(QApplication::translate("MainWindow", "HH:HH:HH:HH:HH:HH;_", nullptr));
        editSetMAC->setText(QApplication::translate("MainWindow", "00:ad:24:16:89:59", nullptr));
        bttnSendIP->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
