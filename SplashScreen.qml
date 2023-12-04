import QtQuick
import QtMultimedia

Item {
    signal splashEnd()

    MediaPlayer {
        id: player
        source: "qrc:/lottie/splash.mp4"
        onMediaStatusChanged: {
            if (mediaStatus == MediaPlayer.LoadedMedia)
                play()
        }
        videoOutput: spashOutput
        onPositionChanged: function (position) {
            if (position >= 3500) {
                pause()
                splashEnd()
            }
        }
    }

    VideoOutput {
        id: spashOutput
        anchors.centerIn: parent
        width: 350
        height: 350
    }
}
