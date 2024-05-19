import QtQuick 2.15
import QtQuick.Layouts 1.3
import "ControlCustoms"

Rectangle {
    id: navBarID
    height:50
    width: 50
    color: colorMediaScreen
    TButton{
        id:menuID
        anchors.verticalCenter: parent.verticalCenter
        sourceIC: !colorCheck?"qrc:/assets/images/menu12.png":"qrc:/assets/images/stack.png"
        // onPressed: {
        //     console.log("navbar")
        //     menuScreenID.visible=!menuScreenID.visible
        // }
    }
    MouseArea
    {
        anchors.fill: parent
        onClicked: {
            console.log("navbar")
            menuScreenID.visible=!menuScreenID.visible
        }
    }
}

