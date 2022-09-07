#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtMath>>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonResult_clicked()
{
    qreal valA = ui->lineEditA->text().toInt();
    qreal valB = ui->lineEditB->text().toInt();
    qreal valC = ui->lineEditC->text().toInt();
    qreal valD = valB*valB - 4 * valA * valC;
    qreal x1,x2;
    QString str;
    if (valA == 0.0){
        str = "Не квадратное уравнение";
    }else{
        if (valD>0){
            x1= (-valB+sqrt(valD))/(2*valA);
            x2= (-valB-sqrt(valD))/(2*valA);
            str = "x1 = " + QString::number(x1) +  ", x2 = " + QString::number(x2);
        } else if (valD == 0){
            x1= (-valB/(2*valA)); x2= x1;
            str = "x = " + QString::number(x1);
        } else{
            str = "Нет корня";
        }
    }
    ui->answerTab->setText(str);
}


void MainWindow::on_buttonResult2_clicked()
{
    qreal first = ui->lineEdit1->text().toInt();
    qreal second = ui->lineEdit2->text().toInt();
    qreal angle = ui->lineEdit3->text().toInt();
    qreal third;
    QString str2;

    if (ui->radioButtonRad->isChecked()){
        angle = angle * 57.3;
    }
    if (ui->radioButtonGr->isChecked()){
        angle = angle * 1;
    }
    if (angle > 180){
        str2 = "Введите угол менее 180";
    } else{
    third = sqrt(pow(first,2)+pow(second,2)-2*first*second*cos(angle* 3.1416 / 180));
    str2 = QString::number(third);
    }
    ui->answerTab2->setText(str2);
}

