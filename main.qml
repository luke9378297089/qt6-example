import QtQuick
import QtQuick.Controls 6.3


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ComboBox {
        id: comboBox
        objectName: "myComboBox"
        x: 195
        y: 136
        width: 140
        height: 48
        model: ListModel {
            ListElement { name: "item1" }
        }
        function addItem(item) {
            model.append({"name": item})
        }
    }

    Button {
        id: button
        x: 195
        y: 263
        width: 140
        height: 48
        text: qsTr("Button")
        icon.color: "#ffffff"

        onClicked: {
            ClassA.processComChange(textField.text)
        }
    }

    TextField {
        id: textField
        objectName: "textField"
        x: 195
        y: 62
        width: 177
        height: 35
        placeholderText: qsTr("Text Field")
    }


}
