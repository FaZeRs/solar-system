import QtQuick
import QtQuick3D

Node {
    id: root
    property string name: "Earth"
    position: Qt.vector3d(0, 0, 0) // Initial position
    property real rotationPeriod: 23.93 // Rotation period in hours
    property real orbitPeriod: 365.25 // Orbit period in days
    property real speed: 1 // Speed multiplier
    property real scale: 0.3 // Scale
    property real orbitRadius: 1000 // Orbit radius
    property real tilt: 23.44 // Tilt angle in degrees

    property url colorData: "assets/maps/earth_color.png"
    property url normalsData: "assets/maps/earth_normals.png"
    property url meshData: "assets/meshes/earth.mesh"

    Texture {
        id: color_texture
        tilingModeHorizontal: Texture.ClampToEdge
        tilingModeVertical: Texture.ClampToEdge
        minFilter: Texture.Nearest
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: root.colorData
    }
    Texture {
        id: normals_texture
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: root.normalsData
    }
    PrincipledMaterial {
        id: material
        baseColorMap: color_texture
        metalness: 0.25
        roughness: 0.8999999761581421
        normalMap: normals_texture
        alphaMode: PrincipledMaterial.Opaque
    }

    Model {
        source: root.meshData
        materials: [
            material
        ]
        scale: Qt.vector3d(root.scale, root.scale, root.scale)
        x: root.orbitRadius
        eulerRotation.x: root.tilt
        receivesShadows: true

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
    }

    // Rotate around the sun
    SequentialAnimation on eulerRotation.y {
        id: orbitRotationAnimation
        loops: Animation.Infinite
        NumberAnimation {
            from: 0
            to: 360
            duration: (orbitPeriod * 1000 * 24 * 60 * 60) / root.speed // Duration in milliseconds
        }
    }

    onSpeedChanged: {
        // Restart the animation when speed changes
        axisRotationAnimation.restart();
        orbitRotationAnimation.restart();
    }
}
