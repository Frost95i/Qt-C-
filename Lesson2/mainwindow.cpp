#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QString>
#include <QListWidget>
#include <QIcon>

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


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    auto spec = Special.GetSpec(arg1.toUpper());
        if(spec.has_value())
        {
            ui->lineEdit->setText(Special.Special(arg1, spec.value()));
        }
}



void MainWindow::on_addBtn_clicked()
{
    QListWidgetItem* items = new QListWidgetItem(QIcon(":img/prg.png"),
                                QInputDialog::getText(this,"Добавить","Наименование:"));
    ui->listWidget->addItem(items);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1) {
        ui->listWidget->setViewMode(QListWidget::IconMode);
    } else {
        ui->listWidget->setViewMode(QListWidget::ListMode);
        ui->listWidget->setMovement(QListView::Snap);
    }
}


void MainWindow::on_deleteBtn_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}


void MainWindow::on_closeBtn_clicked()
{
    close();
}

