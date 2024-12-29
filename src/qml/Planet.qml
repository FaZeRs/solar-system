import QtQuick
import QtQuick3D

Node {
    id: root
    position: Qt.vector3d(0, 0, 0) // Initial position
    property real rotationPeriod: 1 // Rotation period around its axis in hours
    property real orbitPeriod: 1 // Orbit period around sun in days
    property real speed: 1 // Speed multiplier
    property real scale: 1 // Scale
    property real orbitRadius: 1000 // Orbit radius around sun
    property real tilt: 0 // Tilt angle in degrees

    property url colorData
    property url normalsData
    property url ringsData
    property url meshData
    property url ringsTopMeshData
    property url ringsBottomMeshData

    Loader {
        id: colorLoader
        active: root.colorData != ""
        sourceComponent: Texture {
            id: colorTexture
            tilingModeHorizontal: Texture.ClampToEdge
            tilingModeVertical: Texture.ClampToEdge
            minFilter: Texture.Nearest
            generateMipmaps: true
            mipFilter: Texture.Linear
            source: root.colorData
        }
    }

    Loader {
        id: normalsLoader
        active: root.normalsData != ""
        sourceComponent: Texture {
            id: normalsTexture
            generateMipmaps: true
            mipFilter: Texture.Linear
            source: root.normalsData
        }
    }

    Loader {
        id: ringsLoader
        active: root.ringsData != ""
        sourceComponent: Texture {
            id: ringsTexture
            minFilter: Texture.Linear
            generateMipmaps: true
            source: root.ringsData
        }
    }

    PrincipledMaterial {
        id: material
        baseColorMap: colorLoader.active ? colorLoader.item : null
        metalness: 0.25
        roughness: 0.8999999761581421
        normalMap: normalsLoader.active ? normalsLoader.item : null
        alphaMode: PrincipledMaterial.Opaque
    }

    Loader {
        id: ringsMaterialLoader
        active: root.ringsData != ""
        sourceComponent: PrincipledMaterial {
            id: ringsMaterial
            baseColorMap: ringsLoader.active ? ringsLoader.item : null
            roughness: 1
            alphaMode: PrincipledMaterial.Blend
        }
    }

    Node {
        id: orbitNode
        x: root.orbitRadius

        Node {
            id: tiltNode
            eulerRotation.x: root.tilt

            Node {
                id: rotationNode

                // Rotate around its own axis
                SequentialAnimation on eulerRotation.y {
                    id: axisRotationAnimation
                    loops: Animation.Infinite
                    NumberAnimation {
                        from: 0
                        to: 360
                        duration: (root.rotationPeriod * 1000 * 60 * 60) / root.speed
                    }
                }

                Model {
                    source: root.meshData
                    materials: [material]
                    scale: Qt.vector3d(root.scale, root.scale, root.scale)
                    receivesShadows: true
                }

                Model {
                    source: root.ringsTopMeshData
                    materials: [ringsMaterialLoader.active ? ringsMaterialLoader.item : null]
                    scale: Qt.vector3d(root.scale, root.scale, root.scale)
                    receivesShadows: true
                }

                Model {
                    source: root.ringsBottomMeshData
                    materials: [ringsMaterialLoader.active ? ringsMaterialLoader.item : null]
                    scale: Qt.vector3d(root.scale, root.scale, root.scale)
                    receivesShadows: true
                }
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
