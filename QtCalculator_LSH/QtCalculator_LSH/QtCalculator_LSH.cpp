#include "QtCalculator_LSH.h"
#include "calculator.hpp"
#include "ui_QtCalculator_LSH.h"

QtCalculator_LSH::QtCalculator_LSH(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);//just test.

    connect(ui.pushButton_00, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_0);
    connect(ui.pushButton_01, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_1);
    connect(ui.pushButton_02, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_2);
    connect(ui.pushButton_03, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_3);
    connect(ui.pushButton_04, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_4);
    connect(ui.pushButton_05, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_5);
    connect(ui.pushButton_06, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_6);
    connect(ui.pushButton_07, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_7);
    connect(ui.pushButton_08, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_8);
    connect(ui.pushButton_09, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_9);

    connect(ui.pushButton_plus, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_plus);
    connect(ui.pushButton_minus, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_minus);
    connect(ui.pushButton_divide, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_divide);
    connect(ui.pushButton_multi, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_multi);    
    connect(ui.pushButton_RtP, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_RtP);
    connect(ui.pushButton_close, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_close);
    connect(ui.pushButton_clear, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_clear);
    connect(ui.pushButton_result, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_result);
    connect(ui.pushButton_Back, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_BS);

    //Now, I'm going to fix my code
}

void QtCalculator_LSH::setButton_BS()
{
    QString filename(ui.lineEdit->text());
    auto name = ui.lineEdit->text().chopped(1);
    ui.lineEdit->setText(name);
}

void QtCalculator_LSH::setAppend(QString str)
{  
    auto strStack = ui.lineEdit->text();
    strStack += str;
    ui.lineEdit->setText(strStack);
}

void QtCalculator_LSH::setButton_0()
{
    setAppend("0");
}

void QtCalculator_LSH::setButton_1()
{
    setAppend("1");
}

void QtCalculator_LSH::setButton_2()
{
    setAppend("2");
}

void QtCalculator_LSH::setButton_3()
{
    setAppend("3");
}

void QtCalculator_LSH::setButton_4()
{
    setAppend("4");
}

void QtCalculator_LSH::setButton_5()
{
    setAppend("5");
}

void QtCalculator_LSH::setButton_6()
{
    setAppend("6");
}

void QtCalculator_LSH::setButton_7()
{
    setAppend("7");
}

void QtCalculator_LSH::setButton_8()
{
    setAppend("8");
}

void QtCalculator_LSH::setButton_9()
{
    setAppend("9");
}

void QtCalculator_LSH::setButton_plus()
{
    setAppend("+");
}

void QtCalculator_LSH::setButton_minus()
{
    setAppend("-");
}

void QtCalculator_LSH::setButton_divide()
{
    setAppend("/");
}

void QtCalculator_LSH::setButton_multi()
{
    setAppend("*");
}

void QtCalculator_LSH::setButton_RtP()
{
    setAppend("**");
}

void QtCalculator_LSH::setButton_close()
{
    this->close();
}

void QtCalculator_LSH::setButton_clear()
{
    ui.lineEdit->setText("");
}

void QtCalculator_LSH::setButton_result()
{
    auto strExpr = ui.lineEdit->text();
    auto stdExpr = strExpr.toStdString();
    auto nResult = calculator::eval(stdExpr);
    ui.lineEdit->setText(QString::number(nResult));
}