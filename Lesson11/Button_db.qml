import QtQuick 2.15
import QtQuick.Controls 2.12

BorderImage {
    width: 120
    height: 30
    source: "qrc:///res/button.png"
    id: btn_db
    Text{
        id: _txtdb
        color: "White"
        anchors.centerIn: btn_db
        text: "Показать задачи"
        font.pixelSize: 13
    }
    MouseArea{
        anchors.fill: btn_db
        onClicked: {
            _workcl.openEx()
        }
        onPressed: {
            btn_db.width = 95
            btn_db.height = 25
            _txtdb.font.pixelSize = 11
        }
        onReleased: {
            btn_db.width = 120
            btn_db.height = 30
            _txtdb.font.pixelSize = 13
        }
    }
}
