#ifndef HELPFORM_H
#define HELPFORM_H

#include <QWidget>
#include <QString>
namespace Ui {
class HelpForm;
}

class HelpForm : public QWidget{
    Q_OBJECT

public:
    explicit HelpForm(QWidget *parent = nullptr);
    ~HelpForm();

private slots:
    void on_pushButton_clicked();

private:
    void Init();
    QString fileDir;
private:
    Ui::HelpForm *ui;

};

#endif // HELPFORM_H
