#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_new_pushButton_pressed();
    void on_close_pushButton_pressed();
    void on_open_pushButton_pressed();
    void on_save_pushButton_pressed();
    void on_help_pushButton_pressed();

private:
    void currentFileSave();
    void FileSave();
    void FileSaveAs();
    void FileOpen();
    void init();

private:
    Ui::MainWindow *ui;
    QString openedFileName;
    QString filter;

};
#endif // MAINWINDOW_H
