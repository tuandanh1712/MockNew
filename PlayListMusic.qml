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
                model:mediaObj.favoriteSongs
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
                            mediaCtrl.setFavoritMusicPlay()
                            mediaCtrl.setSourceFavor(SourceSongs);
                            mediaCtrl.playFavorit(IndexSongs)
                            mediaCtrl.setIndexFavor(IndexSongs)

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

                    // Row{
                    //     spacing: 10
                    //     anchors.verticalCenter: parent.verticalCenter
                    //     anchors.right: parent.right
                    //     anchors.rightMargin: 15

                    //     ControllerButton{
                    //         id:addFavoriteButton
                    //         imgSource: "qrc:/Icons/favorite.png"
                    //         width: 20
                    //         height: 20
                    //         radius: 20
                    //         visible: false
                    //     }
                    //     ControllerButton{
                    //         id:deleteButton
                    //         imgSource: "qrc:/Icons/delete_.png"
                    //         width: 20
                    //         height: 20
                    //         radius: 20
                    //         visible: false
                    //         onButtonCliked: {
                    //             mediaObj.removeMusic(index)

                    //         }

                    //     }
                    //     ControllerButton{
                    //         id:hideButton

                    //         height: 20
                    //         width: 20
                    //         radius: 10

                    //         Image{
                    //             height: 10
                    //             width: 10
                    //             source: "qrc:/Icons/drag_handle_FILL0_wght200_GRAD200_opsz48.png"
                    //             anchors.centerIn: parent
                    //             fillMode: Image.PreserveAspectFit
                    //         }

                    //         onButtonCliked: {
                    //             addFavoriteButton.visible =!addFavoriteButton.visible
                    //             deleteButton.visible=!deleteButton.visible
                    //         }
                    //     }

                    // }

                }


            }
        }

    }
}
