#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QVector>
#include <QPointF>

#include <complex>
#include <fftw3.h>


class DataProcessor
{
public:
    DataProcessor() {};
    virtual QVector<QPointF> process(const QVector<float>& din) = 0;
};


class DataScaleProcessor : public DataProcessor
{
public:
    DataScaleProcessor(double xs = 1, double ys = 1) : _xs(xs), _ys(ys) {};
    virtual QVector<QPointF> process(const QVector<float>& din) override;

private:
    double _xs, _ys;
};


namespace window_functions
{
    template <typename T>
    QVector<T> rectangular(int N, double &sum)
    {
        QVector<T> window(N);
        sum = N;

        for (int j = 0; j < N; ++j)
            window[j] = 1;

        return window;
    }

    template <typename T>
    QVector<T> hanning(int N, double &sum)
    {
        QVector<T> window(N);
        sum = 0;

        for (int j = 0; j < N; ++j)
        {
            window[j] = 0.5 * (1 - std::cos(2 * M_PI * j / N));
            sum += window[j];
        }

        return window;
    }

    template <typename T>
    QVector<T> hamming(int N, double &sum)
    {
        QVector<T> window(N);
        sum = 0;

        for (int j = 0; j < N; ++j)
        {
            window[j] = 0.54 - 0.46 * std::cos(2 * M_PI * j / N);
            sum += window[j];
        }

        return window;
    }
}

class DataFFTProcessor : public DataProcessor
{
public:
    DataFFTProcessor(int num);
    ~DataFFTProcessor();
    virtual QVector<QPointF> process(const QVector<float>& din) override;

private:
    int _num;
    fftw_plan plan;
    QVector<double> fftin;
    QVector<std::complex<double>> fftout;
    QVector<double> window;
    double window_sum;
};

#endif // DATAPROCESSOR_H
