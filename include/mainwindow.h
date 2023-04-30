#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

#include <qwt_text.h>
#include <qwt_plot_textlabel.h>

#include "adcudpreceiver.h"
#include "dataprocessor.h"
#include "adcremotectrl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void measureCh(int ch, double pwr);
    void tempChanged(int temperature);
    void remoteAddrEdited();
    void setVga();
    void loadVga();
    void storeVga();
    void setUdpHost();
    void setRfPower(bool pwr);

public slots:
    void readyLoadVga(const std::array<int, 4> &vga);

private:
    Ui::MainWindow *ui;
    AdcUdpReceiver * recv;
    AdcRemoteCtrl * adc;

    QwtPlotTextLabel * labelPwr;
    QwtPlotTextLabel * labelTemp;
    std::array<double, 4> powers;
};
#endif // MAINWINDOW_H
