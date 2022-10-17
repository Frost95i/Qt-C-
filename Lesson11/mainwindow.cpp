#include "mainwindow.h"
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QColor>
#include <QtDebug>
#include <QRegularExpression>
#include <QSqlDatabase>


namespace  {
    constexpr int COLUMNS_COUNT = 3;
}

MainWindow::MainWindow(QObject* parent) :
    QAbstractTableModel{parent}
{
    Init();
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("quests");
    if  (!database.open()){
        qDebug() << "db not open";
    }
    else{
        QSqlQuery query;

    auto a = query.exec("create table quests(task varchar(50)),"
                        "data varchar(1024),"
                        "id int(11))"
                        );
    }
}

void MainWindow::Init()
{
    entries.append({"", "Task", "Date", "Priority"});
    LoadData();
}

void MainWindow::LoadData()
{
    //QFile file("DataBase.txt");
    //if (file.open(QIODevice::ReadOnly))
    //{
    //    QTextStream in(&file);
    //    while (!in.atEnd())
    //    {
    //        QStringList entry = parseEntry(in.readLine());
    //        if(COLUMNS_COUNT == entry.size())
    //        {
    //            entry.insert(0, "");
    //            entries.append(entry);
    //        }
    //        else
    //        {
    //            qWarning() << "Incorrect entry";
    //        }
    //    }
    //    file.close();
    //    qInfo() << "Data loaded successfully!";
    //}
    //a = query.exec("select task, data, id from quests");
    while (query.next())
    {
        entries.append({ "query.value(0)", "query.value(1)", "query.value(2)"});
    }
}

void MainWindow::SaveData()
{
    //QFile file("DataBase.txt");
    //if (file.open(QIODevice::WriteOnly))
    //{
    //    QTextStream out(&file);
    //    for(int i = 1; i < entries.size(); ++i)
    //    {
    //        out << entries.at(i).at(1) << " " << entries.at(i).at(2) << " " << entries.at(i).at(3);
    //    }
    //    file.close();
    //    qInfo() << "Data saved successfully!";
    //}
    query.exec("insert into quests values('entries.at(i).at(1)', 'entries.at(i).at(2)', 'entries.at(i).at(3)')");
    //for (int i = 1; i < entries.size(); ++i) {
    //    query.exec("insert into quests values(entries.at(i).at(1), entries.at(i).at(2), entries.at(i).at(3))");
    //}

}

QStringList MainWindow::parseEntry(const QString& line) const
{
    QStringList entry;
    int pos1 = line.indexOf(QRegularExpression("[0-9]"));
    int pos2 = line.lastIndexOf(' ');
    if(pos1 > 0 && pos2 > pos1)
    {
        QString task = line.left(pos1 - 1).trimmed();
        QString date = line.mid(pos1, pos2 - pos1);
        QString priority = line.right(line.size() - 1 - pos2 );
        entry.append(task);
        entry.append(date);
        entry.append(priority);
    }
    else
    {
        qDebug() << "Incorrect entry parsing!";
    }
    return entry;
}

int MainWindow::rowCount(const QModelIndex &) const
{
    return entries.size();
}

int MainWindow::columnCount(const QModelIndex &) const
{
    return entries.at(0).size();
}

QVariant MainWindow::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TableDataRole:
    {
        if(index.column() == 0)
        {
            if(index.row() == 0)
            {
                return "#";
            }
            return QString::number(index.row());
        }
        else
        {
            return entries.at(index.row()).at(index.column());
        }
    }
    case HeadingRole:
    {
        if(index.row() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> MainWindow::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "header";
    return roles;
}

void MainWindow::onSave()
{
    SaveData();
}

void MainWindow::onRemove(int index)
{
    if(index >= 0 && index < entries.size())
    {
        beginRemoveRows(QModelIndex(), 0, rowCount());
        entries.removeAt(index);
        endRemoveRows();
    }
    else
    {
        qWarning() << "Incorrect index. Can't remove entry!";
    }
}

void MainWindow::onClear()
{
    if(entries.size() >= 1)
    {
        beginRemoveRows(QModelIndex(), 0, rowCount());
        entries.erase(entries.begin() + 1, entries.end());
        endRemoveRows();
    }
    else
    {
        qWarning() << "Incorrect data table. Can't clear entries!";
    }
}

void MainWindow::onAdd(const QString& task, const QString& date, const QString& priority)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    entries.append(QStringList{"", task, date, priority});
    endInsertRows();
}

int MainWindow::entriesCount() const
{
    int count = entries.size() - 1;
    if (count < 0)
    {
        qWarning() << "Incorrect data table! Can't count entries!";
    }
    return count;
}

void MainWindow::checkDate()
{
    QRegularExpression version(QRegularExpression::anchoredPattern(QLatin1String("(0[1-9]|[12][0-9]|3[01])[-/.](0[1-9]|1[012])[-/.](19\\d{2}|20\\d{2})")));
}

QStringList MainWindow::getRow(int index) const
{
    if(index >= 0 && index < entries.size())
    {
        return entries.at(index);
    }
    return QStringList{};
}

bool MainWindow::findTask(const QString& task) const
{
    auto it = std::find_if(entries.begin(), entries.end(), [task](const auto& entry) { return entry[1] == task; });
    if(it != entries.end())
    {
        return true;
    }
    return false;
}
