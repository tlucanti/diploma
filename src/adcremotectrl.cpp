#include <QNetworkProxy>
#include <QtEndian>

#include "adcremotectrl.h"

struct cmd {
    uint16_t opcode;
    union {
        uint16_t gain[4];
        uint16_t pwr;
        uint8_t remote_addr[4];
        uint8_t remote_mac[6];
    };
} __attribute__((packed));


AdcRemoteCtrl::AdcRemoteCtrl(QObject *parent) :
    QObject(parent)
    , socket(new QTcpSocket(parent))
{
    QNetworkProxy proxy;
    QNetworkProxy::setApplicationProxy(proxy);

    connect(socket, &QTcpSocket::readyRead, this, &AdcRemoteCtrl::readyRead);
}

AdcRemoteCtrl::~AdcRemoteCtrl()
{
    delete socket;
}

void AdcRemoteCtrl::setAddress(const QHostAddress &addr)
{
    if (this->addr != addr)
        socket->disconnectFromHost();

    this->addr = addr;
}

void AdcRemoteCtrl::readyRead()
{
    struct cmd cmdin;

    while (socket->bytesAvailable() > 0)
    {
        socket->read(reinterpret_cast<char *>(&cmdin), sizeof(cmdin));
        int opcode = qFromBigEndian(cmdin.opcode);
        if (opcode == 0x06)
        {
            std::array<int, 4> ret;
            for (size_t i = 0; i < ret.size(); ++i)
                ret[i] = qFromBigEndian(cmdin.gain[i]);

            emit readyLoadVga(ret);
        }
    }
}

void AdcRemoteCtrl::sendCommand(const QByteArray& ba)
{
    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        socket->connectToHost(addr, TCP_PORT);
        socket->waitForConnected(1000);
    }

    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(ba);
    }
}

void AdcRemoteCtrl::loadVga()
{
    QByteArray ba(2, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x06);

    sendCommand(ba);
}

void AdcRemoteCtrl::sendVga(const std::array<int, 4> &vga)
{
    QByteArray ba(10, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x05);
    for (size_t i = 0; i < vga.size(); ++i)
        cmdout->gain[i] = qToBigEndian<uint16_t>(vga[i]);

    sendCommand(ba);
}

void AdcRemoteCtrl::storeVga(const std::array<int, 4> &vga)
{
    QByteArray ba(10, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x07);
    for (size_t i = 0; i < vga.size(); ++i)
        cmdout->gain[i] = qToBigEndian<uint16_t>(vga[i]);

    sendCommand(ba);
}

void AdcRemoteCtrl::setRemoteAddr(const std::array<uint8_t, 4> &ip, const std::array<uint8_t, 6> &mac)
{
    QByteArray ba;
    struct cmd * cmdout;

    ba = QByteArray(6, 0);
    cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x08);
    for (size_t i = 0; i < ip.size(); ++i)
        cmdout->remote_addr[i] = ip[i];

    sendCommand(ba);

    ba = QByteArray(8, 0);
    cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x09);
    for (size_t i = 0; i < mac.size(); ++i)
        cmdout->remote_mac[i] = mac[i];

    sendCommand(ba);
}

void AdcRemoteCtrl::setRfPower(bool pwr)
{
    QByteArray ba(4, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x01);
    cmdout->pwr = qToBigEndian<uint16_t>(pwr ? 1 : 0);

    sendCommand(ba);
}

