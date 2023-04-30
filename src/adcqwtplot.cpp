#include "adcqwtplot.h"
#include <iostream>

AdcQwtPlot::AdcQwtPlot(QWidget *parent) :
    QwtPlot(parent)
    , proc(nullptr)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    setCanvasBackground(Qt::white);

//    setAxisScale(QwtAxis::Position::YLeft, -130, 10);

    grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(QColor(0x888a85), 1, Qt::DashLine));
    grid->attach(this);

    magnifier = new QwtPlotMagnifier(canvas());
    magnifier->setMouseButton(Qt::MidButton);
    magnifier->setAxisEnabled(QwtAxis::Position::YLeft, false);

    panner = new QwtPlotPanner(canvas());
    panner->setMouseButton(Qt::RightButton);
    panner->setAxisEnabled(QwtAxis::Position::YLeft, false);
}

AdcQwtPlot::~AdcQwtPlot()
{
    delete panner;
    delete magnifier;
}

void AdcQwtPlot::setCurves(int num)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    for (int i = 0; i < num; ++i)
    {
        QwtPlotCurve * curve = new QwtPlotCurve();
        switch (i)
        {
        // [Tango palette](https://en.wikipedia.org/wiki/Tango_Desktop_Project)
        case 0:  curve->setPen(QColor(0xcc0000), 2); break;  // Scarlet Red
        case 1:  curve->setPen(QColor(0x3465a4), 2); break;  // Sky Blue
        case 2:  curve->setPen(QColor(0x73d216), 2); break;  // Chameleon
        case 3:  curve->setPen(QColor(0xedd400), 2); break;  // Butter
        default: curve->setPen(QColor(0x555753), 2);         // Aluminium
        }

        curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        curve->attach(this);

        curves.push_back(curve);
    }
}

void AdcQwtPlot::setSamples(const QVector<QVector<float>>& yData)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    for (int i = 0; i < curves.size(); ++i)
    {
        if (proc)
        {
            const auto &samples = proc->process(yData[i]);
            if (i < measures.size())
                measures[i]->process(samples);

            curves[i]->setSamples(samples);
        }
        else
            curves[i]->setSamples(yData[i]);
    }

    replot();
}

void PlotPowerMeasure::process(const QVector<QPointF> &data)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    const auto m = std::max_element(data.cbegin(), data.cend(), [](const QPointF &pt1, const QPointF &pt2){
        return pt2.y() > pt1.y();
    });

    emit measure(m->y());
}


