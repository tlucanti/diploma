#ifndef ADCQWTPLOT_H
#define ADCQWTPLOT_H

#include <QWidget>
#include <QPen>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_textlabel.h>

#include "dataprocessor.h"

class PlotMeasure : public QObject
{
    Q_OBJECT
public:
    virtual void process(const QVector<QPointF> &data) = 0;
};

class PlotPowerMeasure : public PlotMeasure
{
    Q_OBJECT
public:
    virtual void process(const QVector<QPointF> &data) override;

signals:
    void measure(double pwr);
};

class AdcQwtPlot : public QwtPlot
{
    Q_OBJECT
public:
    AdcQwtPlot(QWidget * = nullptr);
    ~AdcQwtPlot();
    void setProcessor(DataProcessor *proc) { this->proc = proc; };
    void setCurves(int num);
    void addMeasure(PlotMeasure * meas) { this->measures.push_back(meas); };

public slots:
    void setSamples(const QVector<QVector<float>>& yData);

private:
    QwtPlotGrid * grid;
    QList<QwtPlotCurve *> curves;
    QList<PlotMeasure *> measures;
    QwtPlotMagnifier * magnifier;
    QwtPlotPanner * panner;

    DataProcessor * proc;
};

#endif // ADCQWTPLOT_H
