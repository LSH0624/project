#include "QtCalculator_LSH.h"
#include "calculator.hpp"
#include "ui_QtCalculator_LSH.h"

QtCalculator_LSH::QtCalculator_LSH(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

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
}

void QtCalculator_LSH::setPPlus(QString str)
{
    auto allstr = ui.lineEdit->text();
    allstr += str;
    ui.lineEdit->setText(allstr);
}
void QtCalculator_LSH::setButton_0()
{
    setPPlus("0");
}
void QtCalculator_LSH::setButton_1()
{
    setPPlus("1");
}
void QtCalculator_LSH::setButton_2()
{
    setPPlus("2");
}
void QtCalculator_LSH::setButton_3()
{
    setPPlus("3");
}
void QtCalculator_LSH::setButton_4()
{
    setPPlus("4");
}
void QtCalculator_LSH::setButton_5()
{
    setPPlus("5");
}
void QtCalculator_LSH::setButton_6()
{
    setPPlus("6");
}
void QtCalculator_LSH::setButton_7()
{
    setPPlus("7");
}
void QtCalculator_LSH::setButton_8()
{
    setPPlus("8");
}
void QtCalculator_LSH::setButton_9()
{
    setPPlus("9");
}
void QtCalculator_LSH::setButton_plus()
{
    setPPlus("+");
}
void QtCalculator_LSH::setButton_minus()
{
    setPPlus("-");
}
void QtCalculator_LSH::setButton_divide()
{
    setPPlus("/");
}
void QtCalculator_LSH::setButton_multi()
{
    setPPlus("*");
}
void QtCalculator_LSH::setButton_RtP()
{
    setPPlus("**");
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