#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCalculator_LSH.h"

class QtCalculator_LSH : public QMainWindow
{
    Q_OBJECT

public:
    QtCalculator_LSH(QWidget *parent = Q_NULLPTR);

    void setButton_0();
    void setButton_1();
    void setButton_2();
    void setButton_3();
    void setButton_4();
    void setButton_5();
    void setButton_6();
    void setButton_7();
    void setButton_8();
    void setButton_9();
 
    void setButton_plus();
    void setButton_minus();
    void setButton_divide();
    void setButton_multi();    
    void setButton_clear();
    void setButton_close();
    void setButton_result();
    void setButton_RtP();

    void setPPlus(QString str);

private:
    Ui::QtCalculator_LSHClass ui;
};
