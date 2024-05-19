import QtQuick 2.15
import QtMultimedia 5.15
import QtGraphicalEffects 1.15

Rectangle{
    id:mediaScreen
    anchors.right: parent.right
    color: colorMediaScreen
    // clip: true
    property alias coverArt: coverArt
    // Image {
    //     id: imgHomeID
    //     source: "qrc:/assets/images/Spotify-Emblema.png"
    //     fillMode: Image.PreserveAspectFit
    //     anchors.fill:parent

    // }
    Image {
        id: coverArt
        source: mediaCtrl.songCoverArt()
        z:isShowCoverArt?-1:0
        anchors.centerIn: parent
        height: parent.height*2/3
        width: parent.height*2/3
        fillMode: Image.PreserveAspectFit
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: coverArt.width
                height: coverArt.height
                radius: Math.min(coverArt.width, coverArt.height) / 2
                color: "black"
            }
        }
    }
    RotationAnimation{
        id: rollanimationid
        target: coverArt
        from: 0
        to:360
        loops: Animation.Infinite
        duration: 10000
        running:true
    }
    Connections{
        target: mediaCtrl
        function onDurationChanged(){
            coverArt.source = mediaCtrl.songCoverArt()
        }
    }
    VideoOutput{
        id:videoID
        source: mediaCtrl
        anchors.fill: parent
        fillMode: VideoOutput.PreserveAspectFit
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            menuScreenID.visible=false
        }
    }


}
