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

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint); // 상부 x버튼 제거
    setWindowFlags(windowFlags() & (~Qt::WindowMinimizeButtonHint)); //상부 minimize 버튼 제거   

    //this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //상부 ui 제거

    QWidget::grabKeyboard(); //키보드 입력 ban

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

    //ui에 세팅된 버튼을 클릭했을 때 원하는 기능과 연결
    }

void QtCalculator_LSH::closeEvent(QCloseEvent* event) //alt+F4를 이용한 종료방법 막음.
{
    event->ignore();
}

void QtCalculator_LSH::setButton_BS() //ui내 Backspace 기능
{
    QString filename(ui.linePutInNum->text());
    auto name = ui.linePutInNum->text().chopped(1);    
    ui.linePutInNum->setText(name);  
}

void QtCalculator_LSH::setAppend(QString strButton)  //보드에 누른 키를 누적시키는 함수
{
    auto strStack = ui.lineStack->text();         //윗 보드에 입력되어 있는 값          
    auto strInput = ui.linePutInNum->text();      //upper->Stack, Edit->Result
    auto strStack_right = strStack.right(1);
   
    if (strButton == "0" || strButton == "1" || strButton == "2" || strButton == "3" || strButton == "4" || strButton == "5" || strButton == "6" || strButton == "7" || strButton == "8" || strButton == "9") 
    {        //숫자 버튼 누를때 

        bool bOk = false; //Stack을 double로 받았는데 false -> 연산자가 있는거
        auto dStack = strStack.toDouble(&bOk); //Stack에 숫자만 있는지, 연산기호가 있는지 알아보는 것. Stack 있는 녀석을 double로 받은 뒤 검사하는 용도.

        if (bOk) // b0k가 false인게 참이다 -> 연산자가 Stack에 있다면
        {
            ui.lineStack->setText(""); //upper를 지우고 Stack도 지운다.
            strStack = "";
        }


        strInput += strButton; //버튼 누르는걸 input에 누적
        
        ui.linePutInNum->setText(strInput); //아래에 strInput을 출력
    }
    else if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/" ) //연산기호 누르면 strInput에 있는게 strButton과 함께 Stack으로 올라가게 됨.
    {
        strStack += (strInput + strButton);

        ui.lineStack->setText(strStack);
        ui.linePutInNum->setText("");       
    }
    else if (strButton == "=")  // result를 누르면 strInput에 남아있던걸 모두 strStack에 옮겨담고 계산.
    {
         strStack += strInput;

         ui.lineStack->setText(strStack);
         ui.linePutInNum->setText("");
    }

    if ((strStack_right == "+" || strStack_right == "-" || strStack_right == "*" || strStack_right == "/") && strInput.isEmpty()) //Stack 맨 오른쪽이 사칙연산이고, 이어서 사칙연산을 눌렀을 때 오류 메세지.
    {            
        if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/")
        {
            QMessageBox::critical(this, "Warning", "Using operator continually is wrong calculation"); //오류 메세지

            QString filename(ui.lineStack->text());  //오류가 난 뒤 맨 오른쪽 두칸을 지움.
            auto name = ui.lineStack->text().chopped(2);
            ui.lineStack->setText(name);
        }

        else if (strInput.isEmpty())
        {
            QMessageBox::critical(this, "Warning", "Impossible calculation");

            QString filename(ui.lineStack->text());  //오류가 난 뒤 맨 오른쪽 한칸을 지움.
            auto name = ui.lineStack->text().chopped(1);
            ui.lineStack->setText(name);
        }
    }     
}

void QtCalculator_LSH::setButton_result() // 최종 결과 함수. =. 헤더파일에 들어있는 calculator와 연결하고, 그 결과값을 읽어 lineEdit에 표시
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