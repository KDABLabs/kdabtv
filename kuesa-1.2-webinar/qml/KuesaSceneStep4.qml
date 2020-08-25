import Qt3D.Core 2.15
import Qt3D.Render 2.15
import Qt3D.Animation 2.15
import Qt3D.Input 2.15
import QtQuick.Scene2D 2.15
import Kuesa 1.2 as Kuesa
import Helpers 1.0
import QtQuick 2.15
import "CinematicExperience"

// SceneEntity is a regular Qt 3D Entity that contains
// collections for the various asset types in Kuesa (Camera, Materials ...)
KuesaSceneStep3 {
    id: root

    // Extract  Screen Material to apply custom Texture
    Kuesa.Asset {
        id: materialScreen
        collection: root.materials
        name: "MatScreen"
        onNodeChanged: node.diffuseMap = offscreenTexture
    }

    // Create empty texture
    Texture2D {
        id: offscreenTexture
        width: 512
        height: 512
        format: Texture.RGBA8_UNorm
        generateMipMaps: true
        magnificationFilter: Texture.Linear
        minificationFilter: Texture.LinearMipMapLinear
        wrapMode {
            x: WrapMode.ClampToEdge
            y: WrapMode.ClampToEdge
        }
    }

    // Use Scene2D to render QtQuick into offscreen Texture
    Scene2D {
        id: qmlTexture
        output: RenderTargetOutput {
            attachmentPoint: RenderTargetOutput.Color0
            texture: offscreenTexture
        }
        mouseEnabled: false
        CinematicExperience {
            width: 512
            height: 512
            transform: Scale { origin.x: 256; origin.y: 256; xScale: 1; yScale: -1 }
        }
    }
}
