#include <QNetworkInterface>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , recv(new AdcUdpReceiver)
    , adc(new AdcRemoteCtrl)
{
    ui->setupUi(this);

    setWindowTitle("ADC Unit Monitor");

    ui->qwtPlotter->setCurves(4);
    DataScaleProcessor * voltsproc = new DataScaleProcessor(1 / 120., 2. / 65536);
    ui->qwtPlotter->setProcessor(voltsproc);
    ui->qwtPlotter->setAxisScale(QwtPlot::yLeft, -1, 1);
    ui->qwtPlotter->setAxisScale(QwtPlot::xBottom, 0, 2082);
    ui->qwtPlotter->setAxisTitle(QwtPlot::yLeft, "Amplitude, mV");
    ui->qwtPlotter->setAxisTitle(QwtPlot::xBottom, "Time, us");

    labelTemp = new QwtPlotTextLabel();
    labelTemp->attach(ui->qwtPlotter);

    ui->qwtSpectr->setCurves(4);
    DataFFTProcessor * fftproc = new DataFFTProcessor(32768 /*recv->NUM_SAMPLES*/);
    ui->qwtSpectr->setProcessor(fftproc);
    ui->qwtSpectr->setAxisScale(QwtPlot::yLeft, -130, 10);
    ui->qwtSpectr->setAxisTitle(QwtPlot::yLeft, "Power spectral density, dBm");
    ui->qwtSpectr->setAxisTitle(QwtPlot::xBottom, "Frequency, MHz");

    labelPwr = new QwtPlotTextLabel();
    labelPwr->attach(ui->qwtSpectr);

    for (int i = 0; i < 4; ++i)
    {
        PlotPowerMeasure * meas = new PlotPowerMeasure();
        ui->qwtSpectr->addMeasure(meas);
        connect(meas, &PlotPowerMeasure::measure, this,
                [=](double pwr){ this->measureCh(i, pwr); });
    }

    connect(recv, &AdcUdpReceiver::dataReady, ui->qwtPlotter, &AdcQwtPlot::setSamples);
    connect(recv, &AdcUdpReceiver::dataReady, ui->qwtSpectr, &AdcQwtPlot::setSamples);
    connect(recv, &AdcUdpReceiver::tempReady, this, &MainWindow::tempChanged);

//    QNetworkInterface network;
//    for (const auto &interface: network.allInterfaces())
//    {
//        if (interface.type() == QNetworkInterface::Ethernet)
//        {
//            for (const auto &addr: interface.addressEntries())
//            {
//                const auto &ip = addr.ip();
//                if (ip.protocol() == QAbstractSocket::IPv4Protocol)
//                    ui->comboHostIface->addItem(
//                                ip.toString() + " -- " + interface.humanReadableName());
//            }
//        }
//    }

    adc->setAddress(QHostAddress(ui->editRemoteIp->text()));
    connect(adc, &AdcRemoteCtrl::readyLoadVga, this, &MainWindow::readyLoadVga);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::measureCh(int i, double pwr)
{
    powers[i] = pwr;

    QwtText txt(
        QString("<span style=\" color:#cc0000;\">CH 1: %1 dBm</span><br>").arg(QString::number(powers[0], 'f', 1)) +
        QString("<span style=\" color:#3465a4;\">CH 2: %2 dBm</span><br>").arg(QString::number(powers[1], 'f', 1)) +
        QString("<span style=\" color:#73d216;\">CH 3: %3 dBm</span><br>").arg(QString::number(powers[2], 'f', 1)) +
        QString("<span style=\" color:#edd400;\">CH 4: %4 dBm</span>").arg(QString::number(powers[3], 'f', 1))
    );
    txt.setRenderFlags(Qt::AlignLeft | Qt::AlignTop);
    txt.setFont(QFont("Calibri", 12, QFont::Bold));
    labelPwr->setText(txt);
}

void MainWindow::tempChanged(int temperature)
{
    QwtText temp(QString("FPGA Temperature: %1°C").arg(QString::number(temperature, 'f', 1)));
    temp.setRenderFlags(Qt::AlignLeft | Qt::AlignTop);
    temp.setFont(QFont("Calibri", 12, QFont::Bold));
    labelTemp->setText(temp);
}

void MainWindow::remoteAddrEdited()
{
    adc->setAddress(QHostAddress(ui->editRemoteIp->text()));
}

void MainWindow::setVga()
{
    std::array<int, 4> vga;
    vga[0] = ui->editVgaCh1->value();
    vga[1] = ui->editVgaCh2->value();
    vga[2] = ui->editVgaCh3->value();
    vga[3] = ui->editVgaCh4->value();

    adc->sendVga(vga);
}

void MainWindow::loadVga()
{
    adc->loadVga();
}

void MainWindow::readyLoadVga(const std::array<int, 4> &vga)
{
    ui->editVgaCh1->setValue(vga[0]);
    ui->editVgaCh2->setValue(vga[1]);
    ui->editVgaCh3->setValue(vga[2]);
    ui->editVgaCh4->setValue(vga[3]);
}

void MainWindow::storeVga()
{
    std::array<int, 4> vga;
    vga[0] = ui->editVgaCh1->value();
    vga[1] = ui->editVgaCh2->value();
    vga[2] = ui->editVgaCh3->value();
    vga[3] = ui->editVgaCh4->value();

    adc->storeVga(vga);
}

void MainWindow::setUdpHost()
{
    std::array<uint8_t, 4> ip;
    std::array<uint8_t, 6> mac;

    auto octets = ui->editSetIP->text().split('.');
    for (size_t i = 0; i < ip.size(); ++i)
        ip[i] = octets[i].toUInt();

    octets = ui->editSetMAC->text().split(':');
    for (size_t i = 0; i < mac.size(); ++i)
        mac[i] = octets[i].toUInt(nullptr, 16);

    adc->setRemoteAddr(ip, mac);
}

void MainWindow::setRfPower(bool pwr)
{
    adc->setRfPower(pwr);
}

