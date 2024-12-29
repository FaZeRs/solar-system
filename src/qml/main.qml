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
            position: Qt.vector3d(0, 0, 1600)
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

            App.Planet {
                id: mercury
                speed: solarSystem.speed
                rotationPeriod: 1407.5
                orbitPeriod: 88
                scale: 0.2
                orbitRadius: 1000
                tilt: 0.034

                colorData: "assets/maps/mercury.png"
                meshData: "assets/meshes/mercury.mesh"
            }

            App.Planet {
                id: venus
                speed: solarSystem.speed
                rotationPeriod: 5832
                orbitPeriod: 225
                scale: 0.2
                orbitRadius: 1500
                tilt: 177.4

                colorData: "assets/maps/venus.png"
                meshData: "assets/meshes/venus.mesh"
            }

            App.Planet {
                id: earth
                speed: solarSystem.speed
                rotationPeriod: 23.93
                orbitPeriod: 365.25
                scale: 0.3
                orbitRadius: 2000
                tilt: 23.44

                colorData: "assets/maps/earth_color.png"
                normalsData: "assets/maps/earth_normals.png"
                meshData: "assets/meshes/earth.mesh"
            }

            App.Planet {
                id: mars
                speed: solarSystem.speed
                rotationPeriod: 24.62
                orbitPeriod: 687
                scale: 0.2
                orbitRadius: 2500
                tilt: 25.19

                colorData: "assets/maps/mars_color.png"
                normalsData: "assets/maps/mars_normals.png"
                meshData: "assets/meshes/mars.mesh"
            }

            App.Planet {
                id: jupiter
                speed: solarSystem.speed
                rotationPeriod: 9.92
                orbitPeriod: 4332
                scale: 0.5
                orbitRadius: 3000
                tilt: 3.13

                colorData: "assets/maps/jupiter.png"
                meshData: "assets/meshes/jupiter.mesh"
            }

            App.Planet {
                id: saturn
                speed: solarSystem.speed
                rotationPeriod: 10.66
                orbitPeriod: 10759
                scale: 0.4
                orbitRadius: 4000
                tilt: 26.73

                colorData: "assets/maps/saturn_color.png"
                ringsData: "assets/maps/saturn_rings.png"
                ringsTopMeshData: "assets/meshes/saturn_rings_top.mesh"
                ringsBottomMeshData: "assets/meshes/saturn_rings_bottom.mesh"
                meshData: "assets/meshes/saturn.mesh"
            }

            App.Planet {
                id: uranus
                speed: solarSystem.speed
                rotationPeriod: 17.24
                orbitPeriod: 30687
                scale: 0.3
                orbitRadius: 5000
                tilt: 97.77

                colorData: "assets/maps/uranus.png"
                meshData: "assets/meshes/uranus.mesh"
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
