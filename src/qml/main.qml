import QtQuick
import QtQuick3D
import QtQuick.Window
import QtQuick3D.Helpers
import QtQuick.Controls

import "." as App

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("Solar System")

    View3D {
        id: view
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "black"
            backgroundMode: SceneEnvironment.Color
            antialiasingMode: SceneEnvironment.MSAA
        }

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
        }

        OrbitCameraController { 
            anchors.fill: parent
            origin: Qt.vector3d(0, 0, 0)
            camera: camera
        }

        Node {
            id: solarSystem
            property real speed: 100000

            App.Sun {
                id: sun
                speed: solarSystem.speed
            }

            App.Earth {
                id: earth
                speed: solarSystem.speed
            }
        }


        DirectionalLight {
            id: sunLight
            color: "white"
            brightness: 1.0
            castsShadow: true
            shadowBias: 0.001
            shadowMapQuality: DirectionalLight.ShadowMapQualityHigh
            eulerRotation: Qt.vector3d(0, 0, 0)
        }


        WasdController {
            controlledObject: camera
            speed: 1
        }
    }

    Slider {
        id: speedSlider
        width: parent.width
        from: 1000
        to: 1000000
        value: solarSystem.speed
        onValueChanged: solarSystem.speed = value
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
    }

    // DebugView {
    //     source: view
    //     resourceDetailsVisible: true
    // }
}