#include <stdint.h>
#include <iostream>

#include <QNetworkDatagram>
#include <QtEndian>

#include "adcudpreceiver.h"


AdcUdpReceiver::AdcUdpReceiver(QObject * parent) :
    QUdpSocket(parent)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    yData.resize(4);
    for (auto &d: yData)
        d.resize(NUM_SAMPLES);

    bind(10000);
    setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 4 * 1024 * 1024);
    connect(this, &QUdpSocket::readyRead, this, &AdcUdpReceiver::readPendingDatagrams);
}

void AdcUdpReceiver::readPendingDatagrams()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    static int num_impulses = 0;
    static int cycle_capt = 0;

    while (hasPendingDatagrams())
    {
        qint64 sz = pendingDatagramSize();
        std::vector<char> datagram(sz);
        readDatagram(datagram.data(), sz);

        const struct AdcMsg * msg = reinterpret_cast<AdcMsg *>(datagram.data());
        int offset = qFromBigEndian(msg->offset);
        int impulse = qFromBigEndian(msg->impulse);
        int cycle = qFromBigEndian(msg->cycle);
        int flags = qFromBigEndian(msg->flags);

        if (!capture && impulse == 0 && offset == 0)
        {
            dglist.clear();
            num_impulses = 0;
            cycle_capt = cycle;

            capture = true;
        }

        if (cycle != cycle_capt)
            capture = false;

        if (capture)
        {
            dglist.push_back(std::move(datagram));

            if (flags == 1)
                ++num_impulses;

            if (flags == 1 && impulse == 77)
            {
                if (num_impulses == NUM_IMPULSES)
                {
                    for (auto &m: dglist)
                    {
                        msg = reinterpret_cast<AdcMsg *>(m.data());

                        offset = qFromBigEndian(msg->offset);
                        impulse = qFromBigEndian(msg->impulse);
                        temperature = static_cast<int>(qRound(qFromBigEndian(msg->temperature) * 503.975 / 65536 - 273.15));

                        const int16_t * src = reinterpret_cast<const int16_t *>(msg->data);
                        size_t sz = (m.size() - ADCMSG_DATA_OFFSET) / 8;
                        size_t dst = (impulse * IMPULSE_BYTES + offset) / 8;

                        for (size_t i = 0; i < sz; ++i)
                        {
                            yData[0][dst + i] = static_cast<float>(src[i*4 + 0]);
                            yData[1][dst + i] = static_cast<float>(src[i*4 + 1]);
                            yData[2][dst + i] = static_cast<float>(src[i*4 + 2]);
                            yData[3][dst + i] = static_cast<float>(src[i*4 + 3]);
                        }
                    }

                    emit dataReady(yData);
                    emit tempReady(temperature);
                }

                capture = false;
            }
        }
    }
}

