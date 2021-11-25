#include "QtCalculator_LSH.h"
#include "calculator.hpp"
#include "ui_QtCalculator_LSH.h"
#include "qmessagebox.h"
#include "qmainwindow.h"
#include <QCloseEvent>

QtCalculator_LSH::QtCalculator_LSH(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint); // ��� x��ư ����
    setWindowFlags(windowFlags() & (~Qt::WindowMinimizeButtonHint)); //��� minimize ��ư ����   

    //this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //��� ui ����

    QWidget::grabKeyboard(); //Ű���� �Է� ban

    connect(ui.pushButton_00, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_0);
    connect(ui.pushButton_01, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_1);
    connect(ui.pushButton_02, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_2);
    connect(ui.pushButton_03, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_3);
    connect(ui.pushButton_04, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_4);
    connect(ui.pushButton_05, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_5);
    connect(ui.pushButton_06, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_6);
    connect(ui.pushButton_07, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_7);
    connect(ui.pushButton_08, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_8);
    connect(ui.pushButton_09, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_9); //keyPressEvent);

    connect(ui.pushButton_plus, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_plus);
    connect(ui.pushButton_minus, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_minus);
    connect(ui.pushButton_divide, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_divide);
    connect(ui.pushButton_multi, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_multi);    
    connect(ui.pushButton_RtP, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_RtP);
    connect(ui.pushButton_close, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_close);
    connect(ui.pushButton_clear, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_clear);
    connect(ui.pushButton_result, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_result);
    connect(ui.pushButton_Back, &QPushButton::clicked, this, &QtCalculator_LSH::setButton_BS);         

    //ui�� ���õ� ��ư�� Ŭ������ �� ���ϴ� ��ɰ� ����
    }

void QtCalculator_LSH::closeEvent(QCloseEvent* event) //alt+F4�� �̿��� ������ ����.
{
    event->ignore();
}

void QtCalculator_LSH::setButton_BS() //ui�� Backspace ���
{
    QString filename(ui.linePutInNum->text());
    auto name = ui.linePutInNum->text().chopped(1);    
    ui.linePutInNum->setText(name);  
}

void QtCalculator_LSH::setAppend(QString strButton)  //���忡 ���� Ű�� ������Ű�� �Լ�
{
    auto strStack = ui.lineStack->text();         //�� ���忡 �ԷµǾ� �ִ� ��          
    auto strInput = ui.linePutInNum->text();      //upper->Stack, Edit->Result
    auto strStack_right = strStack.right(1);
   
    if (strButton == "0" || strButton == "1" || strButton == "2" || strButton == "3" || strButton == "4" || strButton == "5" || strButton == "6" || strButton == "7" || strButton == "8" || strButton == "9") 
    {        //���� ��ư ������ 

        bool bOk = false; //Stack�� double�� �޾Ҵµ� false -> �����ڰ� �ִ°�
        auto dStack = strStack.toDouble(&bOk); //Stack�� ���ڸ� �ִ���, �����ȣ�� �ִ��� �˾ƺ��� ��. Stack �ִ� �༮�� double�� ���� �� �˻��ϴ� �뵵.

        if (bOk) // b0k�� false�ΰ� ���̴� -> �����ڰ� Stack�� �ִٸ�
        {
            ui.lineStack->setText(""); //upper�� ����� Stack�� �����.
            strStack = "";
        }


        strInput += strButton; //��ư �����°� input�� ����
        
        ui.linePutInNum->setText(strInput); //�Ʒ��� strInput�� ���
    }
    else if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/" ) //�����ȣ ������ strInput�� �ִ°� strButton�� �Բ� Stack���� �ö󰡰� ��.
    {
        strStack += (strInput + strButton);

        ui.lineStack->setText(strStack);
        ui.linePutInNum->setText("");       
    }
    else if (strButton == "=")  // result�� ������ strInput�� �����ִ��� ��� strStack�� �Űܴ�� ���.
    {
         strStack += strInput;

         ui.lineStack->setText(strStack);
         ui.linePutInNum->setText("");
    }

    if ((strStack_right == "+" || strStack_right == "-" || strStack_right == "*" || strStack_right == "/") && strInput.isEmpty()) //Stack �� �������� ��Ģ�����̰�, �̾ ��Ģ������ ������ �� ���� �޼���.
    {            
        if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/")
        {
            QMessageBox::critical(this, "Warning", "Using operator continually is wrong calculation"); //���� �޼���

            QString filename(ui.lineStack->text());  //������ �� �� �� ������ ��ĭ�� ����.
            auto name = ui.lineStack->text().chopped(2);
            ui.lineStack->setText(name);
        }

        else if (strInput.isEmpty())
        {
            QMessageBox::critical(this, "Warning", "Impossible calculation");

            QString filename(ui.lineStack->text());  //������ �� �� �� ������ ��ĭ�� ����.
            auto name = ui.lineStack->text().chopped(1);
            ui.lineStack->setText(name);
        }
    }     
}

void QtCalculator_LSH::setButton_result() // ���� ��� �Լ�. =. ������Ͽ� ����ִ� calculator�� �����ϰ�, �� ������� �о� lineEdit�� ǥ��
{
    setAppend("=");

    auto strExpr = ui.lineStack->text();
    auto stdExpr = strExpr.toStdString();
    auto nResult = calculator::eval(stdExpr);

    ui.linePutInNum->setText("");
    ui.lineStack->setText(QString::number(nResult));    
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
    exit(EXIT_FAILURE);        
}

void QtCalculator_LSH::setButton_clear()
{
    ui.linePutInNum->setText("");
    ui.lineStack->setText("");
}