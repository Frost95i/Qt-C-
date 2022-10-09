import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.12
import QtQuick.Dialogs


Dialog {
    title: "Добавить задачу"
    width: 350
    height: 150

    function get_clear_entry_button()
    {
        return clear_entry
    }

    function clearEntry()
    {
        taskEdit.text = ""
        priority.currentIndex = 0
        calendar.text = ""
    }
     property var tempDate: new Date();
    contentItem: Rectangle {
        antialiasing: true
        ColumnLayout {
            anchors.margins: 1
            spacing: 1

            RowLayout {
                anchors.margins: 1
                spacing: 1

                Label {
                   Layout.preferredWidth:  40
                   text: qsTr("Задача")
                   horizontalAlignment: Qt.AlignLeft
                }

                TextField {
                    id: taskEdit
                    width: 230
                    Layout.preferredWidth:  270
                    Layout.preferredHeight: 30
                    selectByMouse: true
                }
            }

            RowLayout {
                anchors.margins: 1
                spacing: 1

                Label {
                    Layout.preferredWidth:  40
                    text: qsTr("Дата")
                    horizontalAlignment: Qt.AlignLeft
                }

                TextField {
                    id: calendar
                    Layout.preferredWidth:  120
                    Layout.preferredHeight: 30
                    selectByMouse: true
                    text: Qt.formatDate(tempDate, "dd.MM.yyyy")
                }

                Label {
                    Layout.preferredWidth:  60
                    text: qsTr("Приоритет")
                    horizontalAlignment: Qt.AlignLeft
                }

                ComboBox {
                    id: priority
                    Layout.preferredWidth:  105
                    model: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                    Layout.preferredHeight: 30
                    background: Rectangle { color: "white" }
                }
            }

            RowLayout {
                anchors.margins: 1
                spacing: 1
                Layout.alignment: Qt.AlignBottom
                Layout.fillWidth: true

                Button {
                    id: add_entry
                    Layout.preferredHeight: 30
                    Layout.fillWidth: true
                    text: qsTr("Добавить")
                    onClicked: {     
                        if (!tableModel.checkDate(calendar.text.trim()))
                        {
                            console.error("incorrect date")
                            error_msgbox.text = "Неверный ввод. Введите дату в формате (dd.MM.yyyy)!"
                            error_msgbox.open();
                        }
                         if(taskEdit.text.trim().length === 0)
                        {
                            console.error("Try to add empty task")
                            error_msgbox.text = "Введите задачу"
                            error_msgbox.open();
                        }
                        else
                        {
                            tableModel.onAdd(taskEdit.text.trim(), calendar.text.trim(), priority.currentText);
                            add_entry_dialog.close();
                            mainWindow.title = getTitle()
                        }
                    }
                }

                Button {
                    id: clear_entry
                    Layout.preferredHeight: 30
                    Layout.fillWidth: true
                    text: qsTr("Очистить")
                    onClicked: { clearEntry() }
                }
            }
        }
    }
}
