import QtQuick 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.12
import QtQml.Models 2.12
import TableModel
import Qt.labs.qmlmodels 1.0
import "./"

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 400
    minimumWidth: 600
    maximumWidth: 600
    minimumHeight: 400
    maximumHeight: 400
    visible: true
    color: "lightblue"
    title: getTitle()

    property int selectedIndex: -1

    function getWidth(col) {
        if (col === 0) return 30
        else if (col === 1) return 420
        else if (col === 2 || col === 3) return 75
        else return 0
    }

    function setFontBold(row)
    {
        return (row === 0 ? true : false)
    }

    function setHorizontalCenterAnchors(row, col, parent)
    {
        return row === 0 || col === 0 || col === 2 || col === 3 ? parent.horizontalCenter : undefined
    }

    function setLeftAnchors(row, col, parent)
    {
        return row !== 0 && col === 1 ? parent.left : undefined
    }

    function isHighlighted(row)
    {
        return row === selectedIndex && row !== 0
    }

    function getCellColor(header)
    {
        return header ? "lightblue" : "white"
    }

    function getTitle()
    {
        return qsTr("Органайзер (Задачи: " + tableModel.entriesCount() + ")")
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 1
        spacing: 1
        antialiasing: true

        TableView {
            id: task_list
            Layout.fillHeight: true
            Layout.fillWidth: true
            columnSpacing: 1
            rowSpacing: 1
            clip: true
            model: tableModel


            ItemSelectionModel {
                id: sm
                model: tableModel
            }

            delegate:
                Rectangle {
                id: cell
                implicitWidth: getWidth(column)
                implicitHeight: 30
                color: getCellColor(header)

                Text {
                    id: text
                    anchors.left: setLeftAnchors(row, column, parent)
                    anchors.horizontalCenter: setHorizontalCenterAnchors(row, column, parent)
                    anchors.verticalCenter: parent.verticalCenter
                    text: tabledata
                    font.bold: setFontBold(row)
                }

                ItemDelegate {
                    id: selectedItem
                    implicitWidth: getWidth(column)
                    implicitHeight: 30
                    highlighted: isHighlighted(row)

                    Text {
                        id: selectedText
                        anchors.left: setLeftAnchors(row, column, parent)
                        anchors.horizontalCenter: setHorizontalCenterAnchors(row, column, parent)
                        anchors.verticalCenter: parent.verticalCenter
                        text: isHighlighted(row) ? tabledata : ""
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: { sm.select(tableModel.index(row, column), ItemSelectionModel.Select | ItemSelectionModel.Current); selectedIndex = row }
                }
            }
        }

        RowLayout {
            anchors.margins: 1
            spacing: 1
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            Button {
                id: add_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Добавить")
                onClicked: { add_entry_dialog.open(); add_entry_dialog.get_clear_entry_button().clicked() }
            }

            Button {
                id: remove_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Удалить")
                onClicked: { tableModel.onRemove(selectedIndex); mainWindow.title = getTitle() }
            }

            Button {
                id: clear_button
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                text: qsTr("Очистить")
                onClicked: { tableModel.onClear(); mainWindow.title = getTitle() }
            }

            Button {
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                id: save_button
                text: qsTr("Сохранить")
                onClicked: { tableModel.onSave(); }
            }

            Button {
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                id: quit_button
                text: qsTr("Выход")
                onClicked: { Qt.quit() }
            }
        }
    }

    Msg_box {
        id: error_msgbox
    }
    Add_dialog {
        id: add_entry_dialog
        x: parent.width / 4
        y: parent.height / 4
    }
}
