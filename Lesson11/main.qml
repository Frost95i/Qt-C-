import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import com.workclass 1.0

Rectangle {
    width: 1920
    height: 1080
    visible: true
    id: root

    WorkClass{
        id:_workcl
    }

    GridLayout{
        rows: 9
        columns: 2
        Text{
            Layout.row: 0
            Layout.column: 0
            text: "Название задачи:"
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
        }
        Text{
            Layout.row: 1
            Layout.column: 1
            text: "Конец выполнения задачи:"
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
        }
        Text{
            Layout.row: 2
            Layout.column: 0
            text: "День:"
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
        }
        Text{
            Layout.row: 3
            Layout.column: 0
            text: "Месяц:"
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
        }
        Text{
            Layout.row: 4
            Layout.column: 0
            text: "Год:"
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
        }
        Text{
            Layout.row: 5
            Layout.column: 0
            text: "Текущее состояние(от 1 до 10):"
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
        }
        Text{
            Layout.row: 6
            Layout.column: 0
            text: "Кол-во задач в базе данных:"
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
        }
        Text{
            Layout.row: 6
            Layout.column: 1
            text: Number(_workcl.getCount())
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
            id: numb_txt
        }
        Text{
            Layout.row: 8
            Layout.column: 1
            text: ""
            color: "Black"
            font.family: "Helvetica"
            font.pointSize: 14
            id: error_mess
        }

        TextField{
            Layout.row: 0
            Layout.column: 1
            width: 240
            height: 60
            placeholderText: "Название задачи"
            font.family: "Helvetica"
            font.pointSize: 14
            color: "black"
            focus: true
            selectionColor:  "grey"
            selectByMouse: true
            id:_textEdit
        }
        SpinBox{
            Layout.row: 2
            Layout.column: 1
            id: _spb_day
            value: 1
            from: 1
            to: 31
        }
        SpinBox{
            Layout.row: 3
            Layout.column: 1
            id: _spb_month
            value: 1
            from: 1
            to: 12
        }
        SpinBox{
            Layout.row: 4
            Layout.column: 1
            id: _spb_year
            value: 2022
            from: 2022
            to: 2100
        }
        SpinBox{
            Layout.row: 5
            Layout.column: 1
            id: _spb_process
            value: 1
            to: 10
        }
        Button_db{
            width: 120
            height: 30
            Layout.row: 7
            Layout.column: 0
        }
        Button_w{
            width: 80
            height: 30
            Layout.row: 7
            Layout.column: 1
        }
    }


}
