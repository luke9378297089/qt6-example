#ifndef CALCTEST_H
#define CALCTEST_H

#include <QObject>
#include<QQmlApplicationEngine>
#include<QQmlContext>
#include<QQmlProperty>


class CalcTest : public QObject {

    Q_OBJECT

private:
    QString m_com;
    QObject *m_rootObject = nullptr;

signals:
    // 信号是使用 emit 来发送的
    void comChanged();

public slots:
    // 反应槽，用来接收信号
    void processComChange(QVariant inputValue);

public:
    explicit CalcTest(QObject *parent = nullptr);
    void getMCom();

};

#endif // CALCTEST_H
