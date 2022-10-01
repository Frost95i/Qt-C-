#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewer.h"

#include <QMainWindow>
#include <QKeyEvent>
#include <QEvent>
#include <QStyle>
#include <QShortcut>
#include <QModelIndex>
#include <QtWidgets>
#include <QMenu>
#include <QMenuBar>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextCharFormat>
#include <QTextFormat>
#include <QTextCursor>

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

    void on_radioButtonLight_clicked();

    void on_radioButtonDark_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionPrint_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionReadOnly_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionLight_triggered();

    void on_actionDark_triggered();

    void on_actionRu_triggered();

    void on_actionHelp_triggered();

    void on_actionEng_triggered();

    void sizeFont();

    void setFont();

    void copyStyle();

    void pasteStyle();

    void on_pushButtonFont_clicked();

    void on_pushButtonAlignLeft_clicked();

    void on_pushButtonAlignMid_clicked();

    void on_pushButtonAlignRight_clicked();

    void on_pushButtonCopyStyle_clicked();

    void on_pushButtonPasteStyle_clicked();

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
    QMenu* fileMenu;
    QMenu* shortcutSubMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* readOnlyAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* closeAction;
    QAction* exitAction;
    QFileInfoList *aDirList;
    QListViewExplorerModel *model;
    QDir currentFolder;
    QTextEdit *tEdit;
    QFont copyFont;
    QBrush copyForeground;
    QBrush copyBackground;
protected:
    virtual void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
