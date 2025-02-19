#ifndef ADCREMOTECTRL_H
#define ADCREMOTECTRL_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class AdcRemoteCtrl : public QObject
{
    Q_OBJECT

    enum { TCP_PORT = 2000 };

public:
    explicit AdcRemoteCtrl(QObject *parent = nullptr);
    ~AdcRemoteCtrl();
    void setAddress(const QHostAddress &addr);

    void loadVga();
    void sendVga(const std::array<int, 4> &vga);
    void storeVga(const std::array<int, 4> &vga);
    void setRemoteAddr(const std::array<uint8_t, 4> &ip, const std::array<uint8_t, 6> &mac);
    void setRfPower(bool pwr);

signals:
    void readyLoadVga(std::array<int, 4> vga);

private slots:
    void readyRead();

private:
    void sendCommand(const QByteArray& ba);

    QTcpSocket *socket;
    QHostAddress addr;
};

#endif // ADCREMOTECTRL_H
