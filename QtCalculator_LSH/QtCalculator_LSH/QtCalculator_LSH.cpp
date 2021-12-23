#include "QtCalculator_LSH.h"
#include "calculator.hpp"
#include "ui_QtCalculator_LSH.h"
#include "qmessagebox.h"
#include <QCloseEvent>

QtCalculator_LSH::QtCalculator_LSH(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 
    //소스트리 확인하려고 작업중인것을 설정해보았다. -> main branch
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint); // 상부 x버튼 제거
    //setWindowFlags(windowFlags() & (~Qt::WindowMinimizeButtonHint)); //상부 minimize 버튼 제거   

    //소스트리 확인하기 -> test branch

    //소스트리 확인하기
    //211223 branch test

    //merging these files success.

    //

    QWidget::grabKeyboard(); //키보드 입력 제거

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

    //ui에 세팅된 버튼클릭과 원하는 기능과 연결
    }

void QtCalculator_LSH::closeEvent(QCloseEvent* event) //alt+F4를 이용한 종료방법 막음. close 관련 이벤트를 무시시킴.
{
    event->ignore();
}

void QtCalculator_LSH::setButton_BS() //ui내 Backspace 기능
{
    QString filename(ui.linePutInNum->text()); 
    auto name = ui.linePutInNum->text().chopped(1); //오른쪽 한칸을 지우고 그것을 name이라 명명
    ui.linePutInNum->setText(name);  //name을 linePutInNum에 출력
}

void QtCalculator_LSH::setAppend(QString strButton)  //strButton을 눌렀을 때 입력하는 함수
{
    auto strStack = ui.lineStack->text();         //lineStack에 입력되어 있는 값
    auto strInput = ui.linePutInNum->text();      //strButton을 눌러 linePutInNum에 입력되는 (수)
    auto strStack_right = strStack.right(1);      //lineStack의 맨 오른쪽에 배치되어있는 것
   
    if (strButton == "0" || strButton == "1" || strButton == "2" || strButton == "3" || strButton == "4" || strButton == "5" || strButton == "6" || strButton == "7" || strButton == "8" || strButton == "9") 
    {        //숫자 버튼 누를때 

        bool bOk = false; //Stack을 double로 받았는데 false -> 연산자가 있는거
        auto dStack = strStack.toDouble(&bOk); //Stack에 숫자만 있는지, 연산기호가 있는지 알아보는 것. Stack 있는 녀석을 double로 받은 뒤 검사하는 용도.

        if (bOk) // b0k가 false인게 참이다 -> 연산자가 lineStack에 있다면
        {
            ui.lineStack->setText(""); //lineStack을 지우고 strStack도 지운다.
            strStack = "";
        }


        strInput += strButton; //버튼 누르는걸 input에 누적
        
        ui.linePutInNum->setText(strInput); //아래에 strInput을 출력
    }
    else if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/" || strButton == "**")
    {
        strStack += (strInput + strButton); //연산기호 누르면 strInput에 있는게 strButton과 함께 Stack으로 올라가게 됨.

        ui.lineStack->setText(strStack);   //strStack에 누적되고 있는 값을 출력
        ui.linePutInNum->setText("");      //연산기호 누를 시 linePutInNum 은 초기화
    }
    else if (strButton == "=")  // result를 누르면 strInput에 남아있던걸 모두 strStack에 옮겨담고 lineStack으로 출력, linePutInNum 은 초기화
    {
         strStack += strInput;           //strInput에 있던 수를 strStack으로 옮긴 후, 

         ui.lineStack->setText(strStack);//lineStack을 읽어줌.
         ui.linePutInNum->setText("");   //그 후, linePutInNum은 초기화
    }

    if ((strStack_right == "+" || strStack_right == "-" || strStack_right == "*" || strStack_right == "/") && strInput.isEmpty()) 
        //lineStack 배열의 맨 오른쪽이 연산기호이고, strInput이 비어있을 때이어서 사칙연산 or result 눌렀을 때 오류 메세지.
    {            
        if (strButton == "+" || strButton == "-" || strButton == "*" || strButton == "/") //strStack쪽에 (수)(연산기호)가 되어있고, 순리대로라면 strInput에 (수)가 나와야 하지만 연산기호
        {
            QMessageBox::critical(this, "Warning", "Using operator continually is wrong expression"); //오류 메세지

            QString filename(ui.lineStack->text());  
            auto name = ui.lineStack->text().chopped(2);//오류가 난 뒤 맨 오른쪽 두칸 (strStack에 있던 것과 strInput에 있다 strStack으로 올라가는 것)을 지움.
            ui.lineStack->setText(name);
        }

        else if (strInput.isEmpty()) // result 버튼 눌렀을 때 오류 메세지
        {
            QMessageBox::warning(this, "Warning", "Using operator and equal sign together is incorrent");

            QString filename(ui.lineStack->text());  
            auto name = ui.lineStack->text().chopped(1);//오류가 난 뒤 맨 오른쪽 한칸 (=은 애초에 들어가지 않음. 기존 strStack에 있던 것)을 지움.
            ui.lineStack->setText(name);
        }
    }     
}

void QtCalculator_LSH::setButton_result() // 최종 결과 함수. =. 헤더파일에 들어있는 calculator와 연결하고, 그 결과값을 읽어 lineEdit에 표시
{
    setAppend("="); //lineStack에 표시되진 않지만, setAppend 해주지않으면 인식하지못해 오류발생.

    auto strExpr = ui.lineStack->text();       //lineStack값을 읽어 strExpr로 지정
    auto stdExpr = strExpr.toStdString();      //calculator에서 받아들일 수 있는 값이 StdString이기에 strExpr을 toStdString을 통해 변환. 그 값을 stdExpr
    auto nResult = calculator::eval(stdExpr);  //stdExpr을 계산기 함수인 calculator::eval에 적용, 그 값을 nResult라 명명

    ui.linePutInNum->setText("");              //result버튼을 누르고, 계산이 완료됨에 따라 linePutInNum은 초기화 되고, 결과값은 lineStack에 올라감
    ui.lineStack->setText(QString::number(nResult));    //lineStack의 기본 세팅은 QString이기에 nResult값을 QString::number로 변환하여 lineStack에 출력.
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

void QtCalculator_LSH::setButton_close() //close가 모두 막혔기에 exit으로 버튼 지정
{
    exit(EXIT_FAILURE);        
}

void QtCalculator_LSH::setButton_clear() //linePutInNum과 lineStack을 초기화
{
    ui.linePutInNum->setText("");
    ui.lineStack->setText("");
}