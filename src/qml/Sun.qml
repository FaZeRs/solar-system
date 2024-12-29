import QtQuick
import QtQuick3D

Node {
    id: root
    property string name: "Sun"
    property real rotationPeriod: 609.12 // Rotation period in hours
    property vector3d position: Qt.vector3d(0, 0, 0)
    property real speed: 1 // Speed multiplier
    property real scale: 1000 // Scale
    property real tilt: 7.25 // Tilt angle in degrees

    eulerRotation.y: 0

    property url textureData: "assets/maps/sun.png"
    property url meshData: "assets/meshes/sun.mesh"

    Texture {
        id: texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: root.textureData
    }

    PrincipledMaterial {
        id: material
        baseColor: "#ff000000"
        roughness: 1
        emissiveMap: texture
        emissiveFactor: Qt.vector3d(1, 1, 1)
        alphaMode: PrincipledMaterial.Opaque
    }

    Model {
        source: root.meshData
        materials: [material]
        scale: Qt.vector3d(root.scale, root.scale, root.scale)
        eulerRotation.x: root.tilt
    }

    // Rotate around its own axis
    SequentialAnimation on eulerRotation.y {
        id: axisRotationAnimation
        loops: Animation.Infinite
        NumberAnimation {
            from: 0
            to: 360
            duration: (root.rotationPeriod * 1000 * 60 * 60) / root.speed // Duration in milliseconds
        }
    }

    onSpeedChanged: {
        // Restart the animation when speed changes
        axisRotationAnimation.restart();
    }
}
