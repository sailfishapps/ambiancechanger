import QtQuick 1.1
import Sailfish.Silica 1.0
import QtMobility.gallery 1.1
import org.nemomobile.thumbnailer 1.0
import org.SfietKonstantin.ambiancechanger 1.0

Page {
    id: container

    function setTheme(source) {
        themeRemorse.execute("Setting theme",
                             function() {
                                 if (helperLauncher.setBackground(source)) {
                                     helperLauncher.removeSettings()
                                     helperLauncher.reboot()
                                 }
                            } )
    }

    DocumentGalleryModel {
        id: galleryModel
        rootType: DocumentGallery.Image
        properties: [ "url", "title", "dateTaken" ]
        autoUpdate: true
        sortProperties: ["dateTaken"]
    }

    RemorsePopup {
        id: themeRemorse
    }

    HelperLauncher {
        id: helperLauncher
    }


    SilicaGridView {
        id: grid
        header: PageHeader { title: "Ambiance changer" }
        cellWidth: width / 2
        cellHeight: width / 2
        anchors.fill: parent
        model: galleryModel

        delegate: Image {
            asynchronous: true

            // From org.nemomobile.thumbnailer
            source:  "image://nemoThumbnail/" + url

            sourceSize.width: grid.cellWidth
            sourceSize.height: grid.cellHeight

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var dialog = pageStack.openDialog(dialogComponent)
                    dialog.source = url
                }
            }
        }
        ScrollDecorator {}
    }


    Component {
        id: dialogComponent
        Dialog {
            id: dialog
            property string source
            acceptDestination: container
            acceptDestinationAction: PageStackAction.Pop

            DialogHeader {
                id: header
                acceptText: qsTr("Accept")
            }

            Image {
                id: preview
                anchors.top: header.bottom
                width: dialog.width
                height: width
                sourceSize.width: width
                sourceSize.height: height
                source:  "image://nemoThumbnail/" + dialog.source
            }

            Label {
                anchors.margins: theme.paddingMedium
                anchors.top: preview.bottom; anchors.left: parent.left; anchors.right: parent.right
                wrapMode: Text.WordWrap
                text: qsTr("Warning ! This operation might damage your SDK. It will remove \
definitively the Sailfish background, and reboot the simulator.")
            }

            onAccepted: {
                container.setTheme(dialog.source)
            }
        }
    }
}
