import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Window
import com.xul.st 1.0;
//

ApplicationWindow {
    visible:true
    id: appWindow;
//    flags: Qt.Window | Qt.FramelessWindowHint
    width: 300
    height: 180
    title: "Screenshot Tool"
    background: Image {
     anchors.fill: parent
     source: "https://w0.peakpx.com/wallpaper/273/225/HD-wallpaper-hello-kitty-pink-flowers-umbrella-flowers-hello-kitty-pink-sanrio.jpg"
    }

    //V1.0 LAYOUT
    RowLayout{
        anchors.fill: parent
        // take ss Button

        Image {
//            Layout.margins: 32
            Layout.alignment: Qt.AlignCenter | Qt.AlignLeft
            Layout.margins: 16
            source: "https://i.pinimg.com/originals/7c/86/99/7c86995d3a4ad0d67cf1ae8750cc97b9.png"
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    highlight.color = "#FF4081";
                    takeScreenshot();

                }
                onEntered:{
                    highlight.color = "#FF80AB";
                }
                onExited: {
                    highlight.color = "#E1BEE7";
                }
            }
            Rectangle {
                color: "#E1BEE7"
                id: highlight
                radius: 16
                anchors.fill: parent
                z: -32
            }
        }

//        Image {
////            Layout.margins: 32
//            Layout.alignment: Qt.AlignCenter | Qt.AlignLeft
//            Layout.margins: 16
//            source: "https://sdl-stickershop.line.naver.jp/products/0/0/5/1044/android/stickers/17299.png;compress=true"
//            Layout.preferredWidth: 100
//            Layout.preferredHeight: 100

//            MouseArea {
//                hoverEnabled: true
//                anchors.fill: parent
//                onClicked: {
//                    highlight2.color = "#FF4081";
//                    Qt.quit()
//                }
//                onEntered:{
//                    highlight2.color = "#FF80AB";
//                }
//                onExited: {
//                    highlight2.color = "#E1BEE7";
//                }
//            }
//            Rectangle {
//                color: "#E1BEE7"
//                id: highlight2
//                radius: 16
//                anchors.fill: parent
//                z: -32
//            }
//        }
    }


//    Button
//    {
//        id: takeScreenshotButton
//        text: "Take Screenshot"
//        onClicked: takeScreenshot()
//        anchors.bottom: parent.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.margins: 10
//    }

    function takeScreenshot() {
        ssWindow.visible = false
        appWindow.visible = false
        resultsWindow.visible = false

        takeScreenShootTimer.restart()
    }

    Timer {
        id: takeScreenShootTimer
           interval: 500 // 1 second interval
           repeat: false // Repeat the timer indefinitely

           onTriggered: {
               var image = ScreenshotHelper.captureWindow(appWindow);
               screenshotItem.source = image;

               appWindow.visible = true
               ssWindow.visible = true
               resultsWindow.visible = true

           }
       }

//    Button {
//        id: saveScreenshotButton
//        text: "Save Screenshot"
//        onClicked: saveScreenshot()
//        anchors.bottom: takeScreenshotButton.top
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.margins: 10
//    }

//    function saveScreenshot() {
//        var fileDialog = Qt.createQmlObject('import QtQuick.Dialogs 1.3; FileDialog {}', parent, "FileDialog");
//        fileDialog.title = "Save Screenshot";
//        fileDialog.selectExisting = false;
//        fileDialog.selectMultiple = false;
//        fileDialog.nameFilters = ["PNG Files (*.png)", "All Files (*)"];

//        fileDialog.onAccepted: {
//            screenshotItem.source.saveToFile(fileDialog.fileUrl, "png");
//        }
//        fileDialog.show();
//    }


    property int startX: 0
    property int startY: 0
    property int endX: 0
    property int endY: 0


    Window {
        id: ssWindow;
        width: Screen.width * 0.70
        height: Screen.height * 0.60
        title: "Screenshot preview"
        visible: false

        Image {
            id: screenshotItem
            anchors.fill: parent

            MouseArea {
                anchors.fill: parent
                drag.target: parent

                onPressed: {
                    startX = mouse.x
                    startY = mouse.y
                    endX = mouse.x
                    endY = mouse.y
                    selectionRect.visible = true
                }

                onPositionChanged:
                {
                    endX = mouse.x
                    endY = mouse.y

                    var rectX = Math.min(startX, endX)
                    var rectY = Math.min(startY, endY)
                    var rectW = Math.abs(endX - startX)
                    var rectH = Math.abs(endY - startY)

                    selectionRect.x = rectX
                    selectionRect.y = rectY
                    selectionRect.width = rectW
                    selectionRect.height = rectH
                }

//                onReleased: {
//                    selectionRect.visible = false
//                    // Take a screenshot of the selected area
//                    // You can implement this part according to your requirements
//                }
            }
        }

        Rectangle {
            id: selectionRect
            color: "transparent"
            border.color: "pink"
            border.width: 2
            radius: 16
            visible: false
        }
    }

    Window {
        visible:false
        id: resultsWindow
        y: ssWindow.y
        x: ssWindow.width + ssWindow.x
        width: Screen.width * 0.15
        height: Screen.height * 0.50

        ColumnLayout
        {
            anchors.margins: 8
            spacing: 10
            anchors.fill: parent

            Button
            {
                text: "Scan again"
                Layout.fillWidth: true
                onClicked: console.log("Scan again")
            }

            Button {
                text: "Compare with"
                Layout.fillWidth: true
                onClicked: console.log("Add compartor")
            }

            TextArea {
                Layout.preferredHeight: 32
                text: "TEX FORMAT"
            }

            ComboBox {
                Layout.preferredHeight: 32
                Layout.fillWidth: true

                model: ["TextRecognition", "TextComparison", "TextFormatting"]
            }

            ScrollView {
                Layout.fillHeight: true
                Layout.fillWidth: true

                TextArea {
                    anchors.fill: parent
                    textFormat: TextEdit.RichText
                    readOnly: true
                    wrapMode:  TextArea.WordWrap
                    text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce ac ipsum libero. Donec euismod, sapien id ultrices lobortis, lorem nisl eleifend lectus, non eleifend nisl massa non turpis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed hendrerit augue eget leo bibendum laoreet. Suspendisse potenti. Aliquam id metus eu arcu faucibus efficitur. Praesent laoreet risus eu enim volutpat, sed interdum augue sollicitudin. Aenean vel erat nec sapien sodales finibus id quis velit. Sed eget pretium nulla. Nulla sed purus vel neque efficitur aliquam. Suspendisse varius ipsum euismod, ullamcorper risus a, consequat est. Proin non placerat libero, ac auctor arcu. Nulla facilisi. Vivamus sit amet mauris vitae sapien venenatis interdum. "
                }
            }
        }
    }

}
