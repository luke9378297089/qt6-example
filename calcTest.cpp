#include <QDebug>

#include "calcTest.h"
#include "engine.h"

CalcTest::CalcTest(QObject *parent) : QObject{parent} {
}

//槽
void CalcTest::processComChange(QVariant inputValue)
{
    Engine::getInstance()->rootObjects().first();
    QObject *myTextFieldObject = Engine::getInstance()->rootObjects().first()->findChild<QObject*>("textField");
    QString text = QQmlProperty::read(myTextFieldObject, "text").toString();
    qDebug() << "Hello " << text << inputValue << myTextFieldObject;
    //回写操作QML对象
    QQmlProperty::write(myTextFieldObject, "text", "Hello World!");


    QObject *myComboBoxObject = Engine::getInstance()->rootObjects().first()->findChild<QObject*>("myComboBox");
    QVariant returnedValue;
    QVariant itemText = text;
    QMetaObject::invokeMethod(myComboBoxObject, "addItem", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, itemText));
    qDebug() << "returnedValue " << returnedValue << myComboBoxObject;
}
