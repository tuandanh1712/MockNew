import QtQuick 2.15
import QtQuick.Controls 2.15
import "ControlCustoms"



Rectangle{
    id:musicScreen
    width: musicScreenID.width
    height: musicScreenID.height
    color: colorMediaScreen
    Column{
        Rectangle{
            id:titleArea
            width: musicScreen.width
            height:100
            color: colorMediaScreen
            Rectangle{
                id:nameArea
                height: titleArea.height
                width: 300
                color: colorMediaScreen
                Text{
                    id:textHome
                    text: qsTr("PLAY LIST")
                    font.pointSize: 25
                    anchors.centerIn: parent
                    font.family:"Tahoma"
                    color: colorText

                }
            }

        }
        Rectangle
        {
            id:content
            width: musicScreen.width
            height:musicScreen.height-titleArea.height
            color: colorMediaScreen
            clip: true
            ListView
            {
                spacing: 5
                id:listGlobal
                height: content.height
                width: content.width
                currentIndex: -1
                visible: true
                ScrollBar.vertical: ScrollBar {
                    visible: true
                    contentItem: Item {
                        implicitWidth: 7
                        implicitHeight: 5
                        Rectangle {
                            color: "#8b9dc3"
                            anchors.fill: parent
                            radius: 5

                        }
                    }
                }
                model:mediaCtrl.favoriteSongs
                delegate:
                    Rectangle{

                    id:listRect
                    width: listGlobal.width
                    height: 100
                    radius: 10
                    color: colorListView

                    MouseArea{
                        anchors.fill:parent
                        hoverEnabled: true

                        onEntered: {

                            listRect.color = "#8b9dc3"
                        }

                        onExited: {

                            listRect.color=colorListView
                        }
                        onClicked: {
                            listGlobal.currentIndex = index
                            isPlaying=true
                            isVideo=false
                            isShowCoverArt=false
                            isFavorit=true
                            mediaCtrl.setFavoritMusicPlay()
                            mediaCtrl.setSourceFavor(SourceSongs);
                            mediaCtrl.playFavorit(index)
                            mediaCtrl.setIndexFavor(index)
                            controllerScreenID.textMusic=mediaCtrl.getFavoritTitleArtits(index)


                        }
                    }
                    Column{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        spacing: 5
                        Text{
                            text:  index+1+"."+ TitleSongs
                            font.pixelSize: 30
                            color:"Green"
                        }
                        Text{
                            text:"&nbsp;<b>Artist:</b>&nbsp;" + ArtistSongs+ "&nbsp;<b>Album:</b>&nbsp;" + AlbumSongs;
                            font.pixelSize: 20
                            color:  "black"

                        }

                    }
                    TButton{
                        id:deleteButton
                        sourceIC: !colorCheck? "qrc:/assets/images/trash.png":"qrc:/assets/images/garbage.png"
                        anchors.right: parent.right
                        anchors.rightMargin: 15
                        width: 20
                        height: 20
                        onPressed:{
                            // mediaCtrl.deletelMusic(index)
                        }

                    }


                }


            }
        }

    }
}
