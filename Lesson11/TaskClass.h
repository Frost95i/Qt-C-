#ifndef TASKCLASS_H
#define TASKCLASS_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QTableView>


class TaskClass : public QObject
{
    Q_OBJECT

public:
    explicit TaskClass(QObject *parent = nullptr);
    ~TaskClass();
    Q_INVOKABLE
    bool saveWork();
    Q_INVOKABLE
    void setDay(int newDay);
    Q_INVOKABLE
    void setMonth(int newMonth);
    Q_INVOKABLE
    void setYear(int newYear);
    Q_INVOKABLE
    void setProcess(int newProcess);
    Q_INVOKABLE
    void setWorkName(const QString &newWorkName);
    Q_INVOKABLE
    int getCount() const;
    Q_INVOKABLE
    void openEx();

signals:

private:
    bool createConnection();
    bool createTable();
    bool insertRecord(QString ex_name, int proc, QString d_date);

private:
    int day, month, year, process;
    int count = 0;
    QSqlDatabase db;
    QString TaskName;
    QSqlQueryModel * model;
    QTableView * view;
};

#endif // TASKCLASS_H
