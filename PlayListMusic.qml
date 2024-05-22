import QtQuick 2.15
import QtQuick.Controls 2.15
import "ControlCustoms"


Rectangle{
    id:playListScreen
    width: musicScreenID.width
    height: musicScreenID.height
    color: colorMediaScreen
    Column{
        Rectangle{
            id:titleArea
            width: playListScreen.width
            height:100
            color: colorMediaScreen
            Rectangle{
                id:nameArea
                height: titleArea.height
                width: 200
                color: colorMediaScreen
                Text{
                    id:textHome
                    text: qsTr("PLAY LIST")+Translator.updateText
                    font.pointSize: 25
                    anchors.centerIn: parent
                    // font.family:"Tahoma"
                    font.bold: true
                    color: colorText

                }
            }

        }
        Rectangle
        {
            id:content
            width: playListScreen.width
            height:playListScreen.height-titleArea.height
            color: colorMediaScreen
            clip: true
            ListView
            {
                id:listGlobal
                spacing: 5
                height: content.height
                width: content.width

                visible: true
                model: isVideo==false? mediaCtrl.favoriteSongs:mediaCtrl.favoritVideos
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
                            if(isVideo==false){
                                isPlaying=true
                                isVideo=false
                                isShowCoverArt=false
                                isFavoritMusic=true
                                mediaCtrl.isMusicFavorit=true
                                mediaCtrl.setFavoritMusicPlay()
                                mediaCtrl.setSource(SourceSongs);
                                mediaCtrl.playFavorit(index)
                                mediaCtrl.setIndexFavor(index)
                                controllerScreenID.textMusic=mediaCtrl.getFavoritTitleArtits(index)
                            }else{
                                isFavoritVideo=true
                                mediaCtrl.setFavoritVideoPlay()
                                mediaCtrl.playFavoritVideo(index);
                                mediaCtrl.setIndexVideoFavor(index);
                                loader.active=false
                                controllerScreenID.textVideo=mediaCtrl.getFavoritVideoTitleArtits(index)
                            }

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
                            if(isVideo==false){
                                mediaCtrl.deletelMusicFavorit(index)

                            }else{
                                mediaCtrl.deletelVideoFavorit(index)
                            }
                        }

                    }


                }


            }
        }

    }
}
