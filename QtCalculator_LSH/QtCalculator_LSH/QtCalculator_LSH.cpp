#include "QtCalculator_LSH.h"
#include "calculator.hpp"
#include "ui_QtCalculator_LSH.h"
#include "qmessagebox.h"
#include <QCloseEvent>

QtCalculator_LSH::QtCalculator_LSH(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 
    //�ҽ�Ʈ�� Ȯ���Ϸ��� �۾����ΰ��� �����غ��Ҵ�. -> main branch
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint); // ��� x��ư ����
    //setWindowFlags(windowFlags() & (~Qt::WindowMinimizeButtonHint)); //��� minimize ��ư ����   

    //�ҽ�Ʈ�� Ȯ���ϱ� -> test branch

    //�ҽ�Ʈ�� Ȯ���ϱ�
    //211223 branch test

    //merging these files success.

    //

    QWidget::grabKeyboard(); //Ű���� �Է� ����

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

    //ui�� ���õ� ��ưŬ���� ���ϴ� ��ɰ� ����
    }

void QtCalculator_LSH::closeEvent(QCloseEvent* event) //alt+F4�� �̿��� ������ ����. close ���� �̺�Ʈ�� ���ý�Ŵ.
{
    event->ignore();
}

void QtCalculator_LSH::setButton_BS() //ui�� Backspace ���
{
    QString filename(ui.linePutInNum->text()); 
    auto name = ui.linePutInNum->text().chopped(1); //������ ��ĭ�� ����� �װ��� name�̶� ���
    ui.linePutInNum->setText(name);  //name�� linePutInNum�� ���
}

void QtCalculator_LSH::setAppend(QString strButton)  //strButton�� ������ �� �Է��ϴ� �Լ�
{
    auto strStack = ui.lineStack->text();         //lineStack�� �ԷµǾ� �ִ� ��
    auto strInput = ui.linePutInNum->text();      //strButton�� ���� linePutInNum�� �ԷµǴ� (��)
    auto strStack_right = strStack.right(1);      //lineStack�� �� �����ʿ� ��ġ�Ǿ��ִ� ��
   
    if (strButton == "0" || strButton == "1" || strButton == "2" || strButton == "3" || strButton == "4" || strButton == "5" || strButton == "6" || strButton == "7" || strButton == "8" || strButton == "9") 
    {        //���� ��ư ������ 

        bool bOk = false; //Stack�� double�� �޾Ҵµ� false -> �����ڰ� �ִ°�
        auto dStack = strStack.toDouble(&bOk); //Stack�� ���ڸ� �ִ���, �����ȣ�� �ִ��� �˾ƺ��� ��. Stack �ִ� �༮�� double�� ���� �� �˻��ϴ� �뵵.

        if (bOk) // b0k�� false�ΰ� ���̴� -> �����ڰ� lineStack�� �ִٸ�
        {
            ui.lineStack->setText(""); //lineStack�� ����� strStack�� �����.
            strStack = "";
        }


        strInput += strButton; //��ư �����°� input�� ����
        
        ui.linePutInNum->setText(strInput); //�Ʒ��� strInput�� ���
    }
    else if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/" || strButton == "**")
    {
        strStack += (strInput + strButton); //�����ȣ ������ strInput�� �ִ°� strButton�� �Բ� Stack���� �ö󰡰� ��.

        ui.lineStack->setText(strStack);   //strStack�� �����ǰ� �ִ� ���� ���
        ui.linePutInNum->setText("");      //�����ȣ ���� �� linePutInNum �� �ʱ�ȭ
    }
    else if (strButton == "=")  // result�� ������ strInput�� �����ִ��� ��� strStack�� �Űܴ�� lineStack���� ���, linePutInNum �� �ʱ�ȭ
    {
         strStack += strInput;           //strInput�� �ִ� ���� strStack���� �ű� ��, 

         ui.lineStack->setText(strStack);//lineStack�� �о���.
         ui.linePutInNum->setText("");   //�� ��, linePutInNum�� �ʱ�ȭ
    }

    if ((strStack_right == "+" || strStack_right == "-" || strStack_right == "*" || strStack_right == "/") && strInput.isEmpty()) 
        //lineStack �迭�� �� �������� �����ȣ�̰�, strInput�� ������� ���̾ ��Ģ���� or result ������ �� ���� �޼���.
    {            
        if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/") //strStack�ʿ� (��)(�����ȣ)�� �Ǿ��ְ�, ������ζ�� strInput�� (��)�� ���;� ������ �����ȣ
        {
            QMessageBox::critical(this, "Warning", "Using operator continually is wrong expression"); //���� �޼���

            QString filename(ui.lineStack->text());  
            auto name = ui.lineStack->text().chopped(2);//������ �� �� �� ������ ��ĭ (strStack�� �ִ� �Ͱ� strInput�� �ִ� strStack���� �ö󰡴� ��)�� ����.
            ui.lineStack->setText(name);
        }

        else if (strInput.isEmpty()) // result ��ư ������ �� ���� �޼���
        {
            QMessageBox::warning(this, "Warning", "Using operator and equal sign together is incorrent");

            QString filename(ui.lineStack->text());  
            auto name = ui.lineStack->text().chopped(1);//������ �� �� �� ������ ��ĭ (=�� ���ʿ� ���� ����. ���� strStack�� �ִ� ��)�� ����.
            ui.lineStack->setText(name);
        }
    }     
}

void QtCalculator_LSH::setButton_result() // ���� ��� �Լ�. =. ������Ͽ� ����ִ� calculator�� �����ϰ�, �� ������� �о� lineEdit�� ǥ��
{
    setAppend("="); //lineStack�� ǥ�õ��� ������, setAppend ������������ �ν��������� �����߻�.

    auto strExpr = ui.lineStack->text();       //lineStack���� �о� strExpr�� ����
    auto stdExpr = strExpr.toStdString();      //calculator���� �޾Ƶ��� �� �ִ� ���� StdString�̱⿡ strExpr�� toStdString�� ���� ��ȯ. �� ���� stdExpr
    auto nResult = calculator::eval(stdExpr);  //stdExpr�� ���� �Լ��� calculator::eval�� ����, �� ���� nResult�� ���

    ui.linePutInNum->setText("");              //result��ư�� ������, ����� �Ϸ�ʿ� ���� linePutInNum�� �ʱ�ȭ �ǰ�, ������� lineStack�� �ö�
    ui.lineStack->setText(QString::number(nResult));    //lineStack�� �⺻ ������ QString�̱⿡ nResult���� QString::number�� ��ȯ�Ͽ� lineStack�� ���.
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

void QtCalculator_LSH::setButton_close() //close�� ��� �����⿡ exit���� ��ư ����
{
    exit(EXIT_FAILURE);        
}

void QtCalculator_LSH::setButton_clear() //linePutInNum�� lineStack�� �ʱ�ȭ
{
    ui.linePutInNum->setText("");
    ui.lineStack->setText("");
}