import Qt3D.Core 2.15
import Qt3D.Render 2.15
import Qt3D.Animation 2.15
import Qt3D.Input 2.15
import Kuesa 1.2 as Kuesa
import Helpers 1.0

// SceneEntity is a regular Qt 3D Entity that contains
// collections for the various asset types in Kuesa (Camera, Materials ...)
Kuesa.SceneEntity {
    id: root

    property real sceneWidth: 1
    property real sceneHeight: 1
    readonly property real aspectRatio: sceneWidth / Math.max(1, sceneHeight)
    property bool animated: true
    readonly property real motorLabelOpacity: triggerMotoTransform.translation.y
    readonly property vector2d motorLabelScreenPosition: projectionHelper.screenPosition

    // Load our glTF scene
    Kuesa.GLTF2Importer {
        sceneEntity: root
        source: 'file:' + _assetPath + "/exportb/car.gltf"
        onSourceChanged: console.log("SOURCE " + source)
    }

    // Extract Camera from the glTF scene
    Kuesa.Asset {
        id: sweepCameraAsset
        collection: root.cameras
        name: "CamSweep_Orientation"
        // Bind a new property aspectRatio on the node
        property real aspectRatio: root.aspectRatio
    }

    // Extract animations from the glTF scene
    NodeInstantiator {
        readonly property var cameraAnimationNames: [
            "SweepCamAction",
            "SweepCamCenterAction",
            "SweepCamPitchAction",
            "MatMotorBlockAction",
            "TriggerMotorInfoAction",
            "DoorLeftAction",  // Only available with exportb
            "DoorRightAction", // Only available with exportb
            "HoodAction"
        ]
        model: cameraAnimationNames
        Kuesa.AnimationPlayer {
            clip: model.modelData
            // Loop forever
            loops: Kuesa.AnimationPlayer.Infinite
            running: root.animated
        }
    }

    // Extract  Trigger Transform from the glTF scene
    Kuesa.Asset {
        id: triggerMotoTransform
        collection: root.transforms
        name: "TriggerMotorInfo"
        // Create properties that will be bound (if they exist) to the Asset's node
        property vector3d translation
        property matrix4x4 worldMatrix
    }

    // Helper to project a world position to a 2D screen position
    ProjectionHelper {
        id: projectionHelper
        width: sceneWidth; height: sceneHeight
        worldMatrix: triggerMotoTransform.worldMatrix
        camera: sweepCameraAsset.node
    }


    // Specify how the scene should be rendered
    components: [
        RenderSettings {
            // FrameGraph configuration that Qt3D should use to render the scene
            Kuesa.ForwardRenderer {
                camera: sweepCameraAsset.node
            }
        },
        InputSettings {}
    ]
}
