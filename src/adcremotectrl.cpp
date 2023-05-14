#include <QNetworkProxy>
#include <QtEndian>
#include <iostream>
#include <color.h>

#include "adcremotectrl.h"
#include <common.hpp>

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
    trace_function();
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
    function_trace();
    if (this->addr != addr)
        socket->disconnectFromHost();

    this->addr = addr;
}

void AdcRemoteCtrl::readyRead()
{
    function_trace();
    std::cout << ANSI_YELLOW << "ready reaad\n" ANSI_RESET;
    struct cmd cmdin;

    while (socket->bytesAvailable() > 0)
    {
        int rb = socket->read(reinterpret_cast<char *>(&cmdin), sizeof(cmdin));
        std::cout << "read " << rb << '/' << sizeof(cmdin) << " bytes\n";
        //int opcode = qFromBigEndian(cmdin.opcode);
        //if (opcode == 0x06)
        if (true)
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
    function_trace();
    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        //socket->connectToHost(addr, TCP_PORT);
        socket->connectToHost("0.0.0.0", 10000);
        socket->waitForConnected(100);
    }

    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(ba);
        std::cout << ANSI_GREEN "write success\n" ANSI_RESET;
    } else {
        std::cout << ANSI_RED "write error\n" ANSI_RESET;
    }
}

void AdcRemoteCtrl::loadVga()
{
    function_trace();
    QByteArray ba(2, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x06);

    sendCommand(ba);
}

void AdcRemoteCtrl::sendVga(const std::array<int, 4> &vga)
{
    function_trace();
    QByteArray ba(10, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x05);
    for (size_t i = 0; i < vga.size(); ++i)
        cmdout->gain[i] = qToBigEndian<uint16_t>(vga[i]);

    sendCommand(ba);
}

void AdcRemoteCtrl::storeVga(const std::array<int, 4> &vga)
{
    function_trace();
    QByteArray ba(10, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x07);
    for (size_t i = 0; i < vga.size(); ++i)
        cmdout->gain[i] = qToBigEndian<uint16_t>(vga[i]);

    sendCommand(ba);
}

void AdcRemoteCtrl::setRemoteAddr(const std::array<uint8_t, 4> &ip, const std::array<uint8_t, 6> &mac)
{
    function_trace();
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
    function_trace();
    QByteArray ba(4, 0);

    struct cmd * cmdout = reinterpret_cast<struct cmd *>(ba.data());
    cmdout->opcode = qToBigEndian<uint16_t>(0x01);
    cmdout->pwr = qToBigEndian<uint16_t>(pwr ? 1 : 0);

    sendCommand(ba);
}
