#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QEvent>
#include <QMainWindow>
#include <QKeyEvent>

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

    void on_radioBtnENG_clicked();

    void on_radioBtnRU_clicked();

    void on_openRead_pushButton_clicked();

private:
    void currentFileSave();
    void FileSave();
    void FileSaveAs();
    void FileOpen();
    void FileOpenReadOnly();
    void init();

private:
    Ui::MainWindow *ui;
    QString openedFileName;
    QString filter;
    QString lng;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
