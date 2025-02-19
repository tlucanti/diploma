#ifndef ADCUDPRECEIVER_H
#define ADCUDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>


#define ADCMSG_DATA_OFFSET 16

#define IMPULSE_BYTES (3204 * 2 * 4)
#define NUM_IMPULSES 78

struct AdcMsg {
    uint8_t id;
    uint8_t selftest;
    uint8_t ovr;
    uint8_t rsvd;
    uint16_t cycle;
    uint16_t impulse;
    uint32_t offset;
    uint16_t flags;
    uint16_t temperature;
    uint8_t data[1408];
} __attribute__((__packed__));

class AdcUdpReceiver : public QUdpSocket
{
    Q_OBJECT

public:
    enum { NUM_SAMPLES = 3204*78 };
    int temperature;

    AdcUdpReceiver(QObject * = nullptr);

public slots:
    void readPendingDatagrams();

signals:
    void dataReady(const QVector<QVector<float>>& yData);
    void tempReady(int temperature);

private:
    bool capture = false;
    QVector<QVector<float>> yData;
    std::list<std::vector<char>> dglist;
};

#endif // ADCUDPRECEIVER_H
