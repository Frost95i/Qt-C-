import QtQuick 2.15
import QtQuick.Controls 2.12

BorderImage {
    width: _txt+15
    height: _txt+12
    source: "qrc:///res/button.png"
    id: btn_w
    Text{
        id: _txt
        color: "White"
        anchors.centerIn: btn_w
        text: "Сохранить"
        font.pixelSize: 13
    }
    MouseArea{
        anchors.fill: btn_w
        onClicked: {
            _workcl.setDay(_spb_day.value)
            _workcl.setMonth(_spb_month.value)
            _workcl.setYear(_spb_year.value)
            _workcl.setProcess(_spb_process.value)
            _workcl.setWorkName(_textEdit.text)
            if(!_workcl.saveWork()){
                error_mess.text = "Пожалуйвста запишите название!"
            }
            else{
                numb_txt.text = Number(_workcl.getCount());
                error_mess.text = ""
            }

        }
        onPressed: {
            btn_w.width = 75
            btn_w.height = 25
            _txt.font.pixelSize = 11
        }
        onReleased: {
            btn_w.width = 80
            btn_w.height = 30
            _txt.font.pixelSize = 13
        }
    }
}
