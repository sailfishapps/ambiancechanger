import QtQuick 1.1
import Sailfish.Silica 1.0
import org.SfietKonstantin.ambiancechanger 1.0

Page {

    PageHeader {
        id: pageHeader
        title: qsTr("Performing tests")
    }


    TestHelper {
        id: testHelper
        Component.onCompleted: testSudo()
        onSudoTestChanged: {
            if (sudoTest == TestHelper.Success) {
                testHelper.testHelper()
            }
        }
        onHelperTestChanged: {
            if (helperTest == TestHelper.Success) {
                testHelper.testSudoHelperLaunch()
            }
        }
        onSudoHelperLaunchTestChanged: {
            if (sudoHelperLaunchTest == TestHelper.Success) {
                pageStack.replace(Qt.resolvedUrl("AmbianceChangerPage.qml"))
            }
        }
    }

    Item {
        id: container
        anchors.top: pageHeader.bottom; anchors.topMargin: theme.paddingMedium
        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom

        Column {
            id: column
            anchors.top: parent.top
            anchors.left: parent.left; anchors.leftMargin: theme.paddingMedium
            anchors.right: parent.right; anchors.rightMargin: theme.paddingMedium
            spacing: theme.paddingMedium

            Label {
                id: testSudoLabel
                anchors.margins: theme.paddingMedium
                text: {
                    switch (testHelper.sudoTest) {
                    case TestHelper.Success:
                        qsTr("Sudo test passed")
                        break
                    case TestHelper.Failure:
                        qsTr("Sudo test failed")
                        break
                    case TestHelper.Running:
                        qsTr("Testing sudo")
                        break
                    default:
                        ""
                        break
                    }
                }
                color: testHelper.sudoTest == TestHelper.Success ? theme.highlightColor
                                                                  : theme.primaryColor
            }

            Label {
                id: testHelperLabel
                anchors.margins: theme.paddingMedium
                text: {
                    switch (testHelper.helperTest) {
                    case TestHelper.Success:
                        qsTr("Helper test passed")
                        break
                    case TestHelper.Failure:
                        qsTr("Helper test failed")
                        break
                    case TestHelper.Running:
                        qsTr("Testing helper")
                        break
                    default:
                        ""
                        break
                    }
                }
                color: testHelper.helperTest == TestHelper.Success ? theme.highlightColor
                                                                   : theme.primaryColor
            }

            Label {
                id: testSudoLaunchHelperLabel
                anchors.margins: theme.paddingMedium
                text: {
                    switch (testHelper.sudoHelperLaunchTest) {
                    case TestHelper.Success:
                        qsTr("Helper successfully launched")
                        break
                    case TestHelper.Failure:
                        qsTr("Helper failed to be launched as root")
                        break
                    case TestHelper.Running:
                        qsTr("Trying to launch the helper as root")
                        break
                    default:
                        ""
                        break
                    }
                }
                color: testHelper.sudoHelperLaunchTest == TestHelper.Success ? theme.highlightColor
                                                                             : theme.primaryColor
            }
        }

        Label {
            id: info
            anchors.bottom: parent.bottom; anchors.bottomMargin: theme.paddingMedium
            anchors.left: parent.left; anchors.leftMargin: theme.paddingMedium
            anchors.right: parent.right; anchors.rightMargin: theme.paddingMedium
            visible: testHelper.sudoTest == TestHelper.Failure
                     || testHelper.helperTest == TestHelper.Failure
                     || testHelper.sudoHelperLaunchTest == TestHelper.Failure
            wrapMode: Text.WordWrap
            font.pixelSize: theme.fontSizeExtraSmall
            text: {
                if (testHelper.sudoTest == TestHelper.Failure) {
                    qsTr("Please install sudo. SSH into the virtual machine, log as root, \
and do \"zypper install sudo\"")
                } else if(testHelper.helperTest == TestHelper.Failure) {
                    qsTr("Please check your installation again. The helper could not be found")
                } else if (testHelper.sudoHelperLaunchTest == TestHelper.Failure) {
                    qsTr("Please add a specific sudo rule for the helper, like\n\n\
nemo ALL= NOPASSWD:/opt/sdk/bin/ambiancechanger-helper\n\nor in the provided README file. \
Be careful, you have to enable NOPASSWD, and it is recommanded to put additional rules in \
/etc/sudoers.d")
                } else {
                    ""
                }
            }
        }

    }


//    ListModel {
//        id: pagesModel

//        ListElement {
//            page: "ChangeAmbiancePage.qml"
//            title: "Change ambiance"
//        }
//        ListElement {
//            page: "TestInstallPage.qml"
//            title: "Test installation"
//        }
//    }

//    SilicaListView {
//        id: listView
//        anchors.fill: parent
//        model: pagesModel
//        header: PageHeader { title: "Ambiance changer" }
//        delegate: BackgroundItem {
//            width: listView.width
//            Label {
//                anchors.left: parent.left; anchors.leftMargin: theme.paddingLarge
//                anchors.verticalCenter: parent.verticalCenter
//                text: model.title
//                color: parent.down ? theme.highlightColor : theme.primaryColor
//            }
//            onClicked: TEST_HELPER.testSudo()
////            onClicked: pageStack.push(Qt.resolvedUrl(page))
//        }
//        VerticalScrollDecorator {}
//    }
}
