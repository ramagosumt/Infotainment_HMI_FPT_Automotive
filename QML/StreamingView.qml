import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    objectName: "streamingViewWindow"

    anchors.fill: parent

    Image {
        id: videoImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    Text {
        text: `FPS: ${streamingViewModel ? streamingViewModel.frameRate : 0}`
        color: "red"
        font.pixelSize: 12
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 4
        z: 1
    }

    Connections {
        target: streamingViewModel
        function onOnCurrentFrameUpdated() {
            Qt.callLater(() => {
                videoImage.source = "image://streamingProvider/frame?" + Date.now();
            });
        }
    }
}
