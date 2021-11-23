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
    connect(ui.pushButton_Back, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_BS);

    //ui에 세팅된 버튼을 클릭했을 때 원하는 기능과 연결
    }

void QtCalculator_LSH::setButton_BS() //ui내 Backspace 기능
{
    QString filename(ui.lineEdit->text());
    auto name = ui.lineEdit->text().chopped(1);
    ui.lineEdit->setText(name);
}

void QtCalculator_LSH::setAppend(QString str) //ui보드에 누른 키를 누적시키는 함수
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

void QtCalculator_LSH::setButton_result() // 최종 결과 함수. =. 헤더파일에 들어있는 calculator와 연결하고, 그 결과값을 읽어 lineEdit에 표시
{
    auto strExpr = ui.lineEdit->text();
    auto stdExpr = strExpr.toStdString();
    auto nResult = calculator::eval(stdExpr);
    ui.lineEdit->setText(QString::number(nResult));
} 
//결과창이 나온 후, 사칙연산을 누르면 누적해서 계산 지속, 숫자를 누르면 새롭게 입력->이걸 어떻게 구현?