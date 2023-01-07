#include "TaskClass.h"
#include <QDebug>

TaskClass::TaskClass(QObject *parent)
    : QObject{parent}
{
    createConnection();

    QSqlQuery query;
    query.exec("SELECT count (*) FROM exercises");
    while(query.next()){
        count = query.value(0).toInt();
    }
    model = new QSqlQueryModel(this);
    view = new QTableView();
    view->setModel(model);
}

TaskClass::~TaskClass(){
    delete model;
    delete view;
}


bool TaskClass::saveWork()
{
    if(TaskName.size() != 0){
        insertRecord(TaskName, process , QString::number(day) + "." + QString::number(month) + "." + QString::number(year));
        count++;
        return true;
    }
    else{
        return false;
    }

}

void TaskClass::setDay(int newDay)
{
    day = newDay;
}

void TaskClass::setMonth(int newMonth)
{
    month = newMonth;
}

void TaskClass::setYear(int newYear)
{
    year = newYear;
}

void TaskClass::setProcess(int newProcess)
{
    process = newProcess;
}

void TaskClass::setWorkName(const QString &newTaskName)
{
    TaskName = newTaskName;
}

int TaskClass::getCount() const
{
    return count;
}

void TaskClass::openEx()
{
    model->setQuery("SELECT * FROM exercises");
    view->resize(500,300);
    view->show();
}

bool TaskClass::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Qt-HomeWork11_1/res/exercises.db");
    if(!db.open()){
        qDebug() << "Cant open db";
        return false;
    }
    return true;
}

bool TaskClass::createTable()
{
    QSqlQuery query;
    QString s = "CREATE TABLE exercises ("
                "id INTEGER PRIMARY KEY NOT NULL,"
                "Exercise_Name VARCHAR(15),"
                "Process INTEGER NOT NULL,"
                "End_Date VARCHAR(10));";
    if(!query.exec(s)){
        qDebug() << "Unable to create a table";
        return false;
    }
    return true;
}

bool TaskClass::insertRecord(QString ex_name, int proc, QString d_date)
{
    QSqlQuery query;
    QString s = "INSERT INTO exercises (Exercise_Name, Process, End_Date)"
                "VALUES('%1','%2','%3');";
    QString q = s.arg(ex_name).arg(proc).arg(d_date);
    if(!query.exec(q)){
        qDebug() << "Unable to make insertion";
        return false;
    }
    return true;

}
