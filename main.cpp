#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

#include "calcTest.h"
#include "engine.h"
#include "serialHelper.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 *
 * 如何在 C++ 中使用 QML 对象
 * https://www.cnblogs.com/linuxAndMcu/p/12208786.html
 *
 * 【QML与C++混合编程】在 QML 中使用 C++ 类和对象（一）
 * https://www.cnblogs.com/linuxAndMcu/p/11961090.html
 *
 * 画图工具
 * https://zhuangzuoyi.github.io/using-Qt-Charts/
 *
 * QT教程
 * https://blog.csdn.net/dengjin20104042056/article/details/115174639
 *
 */

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Create the chart view and set the chart
    QChartView *chartView = new QChartView();
    QChart *chart = new QChart();
    chartView->setChart(chart);

    // Create the series and set the data
    QLineSeries *series1 = new QLineSeries();
    series1->append(1, 2);
    series1->append(3, 4);
    series1->append(5, 6);
    chart->addSeries(series1);

    QLineSeries *series2 = new QLineSeries();
    series2->append(2, 3);
    series2->append(4, 5);
    series2->append(6, 7);
    chart->addSeries(series2);

    // Set the axis
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 8);
    chart->addAxis(axisX, Qt::AlignBottom);
    series1->attachAxis(axisX);
    series2->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 8);
    chart->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisY);
    series2->attachAxis(axisY);

    // Set the title and legend
    chart->setTitle("Multi-line Chart Example");
    chart->legend()->hide();

    // Show the chart
    chartView->show();

    QQmlApplicationEngine *engine = Engine::getInstance();
    CalcTest testClass;
    SerialHelper serialHelper;

    //打印所有串口设备
    serialHelper.listCom();

    const QUrl url(u"qrc:/test_1/main.qml"_qs);

    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     &app, [](QObject *obj, const QUrl &objUrl) {
        qDebug() << "Object created:" << obj << "at url:" << objUrl;
    });

    engine->load(url);

    //获取到全局上下午，可以访问QML里面的对象
    QQmlContext * rootContext = engine->rootContext();
    rootContext->setContextProperty("ClassA", &testClass);

    return app.exec();
}
