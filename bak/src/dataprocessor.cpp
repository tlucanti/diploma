#include <math.h>
#include <iostream>

#include "dataprocessor.h"


QVector<QPointF> DataScaleProcessor::process(const QVector<float> &din)
{
    function_trace();
    QVector<QPointF> dout(din.size());

    for (int i = 0; i < din.size(); ++i)
        dout[i] = QPointF( i * _xs, din[i] * _ys);

    return dout;
}

DataFFTProcessor::DataFFTProcessor(int num) : _num(num), fftin(num), fftout(num / 2 + 1)
{
    function_trace();
    plan = fftw_plan_dft_r2c_1d(_num, &fftin[0],
            reinterpret_cast<fftw_complex *>(&fftout[0]), FFTW_ESTIMATE);

    window = window_functions::hanning<double>(_num, window_sum);
}

DataFFTProcessor::~DataFFTProcessor()
{
    function_trace();
    fftw_destroy_plan(plan);
}

QVector<QPointF> DataFFTProcessor::process(const QVector<float> &din)
{
    function_trace();
    auto squared = [](double x){ return x * x; };

    const double Ulsb = 2. / 65536;
    const double Ratt = 2;
    const double Rload = 200;
    const double mWatts = 1000;
    const double dBLoss = 3;
    const double freq_mhz = 120;

    double mean = 0;

    for (int i = 0; i < _num; ++i)
    {
        fftin[i] = static_cast<double>(din[i]) * Ulsb;
        mean += fftin[i];
    }
    mean = mean / _num;

    for (int i = 0; i < _num; ++i)
        fftin[i] = (fftin[i] - mean) * window[i];

    fftw_execute(plan);

    QVector<QPointF> dout(_num / 2 + 1);

    for (int i = 0; i < dout.size(); ++i)
    {
        auto a = M_SQRT2 * std::abs(fftout[i]) / window_sum;
        auto p = 10 * std::log10(squared(a * Ratt) / Rload * mWatts) + dBLoss;
        dout[i].setX(freq_mhz / _num * i);
        dout[i].setY(static_cast<float>(p));
    }

    return dout;
}
