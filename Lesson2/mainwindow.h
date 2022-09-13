#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <symbols.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_addBtn_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_deleteBtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::MainWindow *ui;
    Symbols Special;
};
#endif // MAINWINDOW_H
