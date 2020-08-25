import QtQuick 2.0

ShaderEffect {
    id: root

    property variant source
    property real leftHeight: height / 2
    property real rightHeight: height / 2
    property real originalHeight: height
    property real originalWidth: width
    property real amplitude: 0.10

    anchors.fill: parent
    mesh: Qt.size(1, 80)

    vertexShader: "
        attribute highp vec4 qt_Vertex;
        attribute highp vec2 qt_MultiTexCoord0;
        uniform highp mat4 qt_Matrix;
        varying highp vec2 qt_TexCoord0;
        varying lowp float shade;
        uniform highp float leftHeight;
        uniform highp float rightHeight;
        uniform highp float originalHeight;
        uniform highp float originalWidth;
        uniform highp float amplitude;

        void main() {
            qt_TexCoord0 = qt_MultiTexCoord0;

            highp vec4 shift = vec4(0);
            shift.y = qt_Vertex.y * ((originalHeight - leftHeight) + (leftHeight - rightHeight) * (qt_Vertex.x / originalWidth)) / originalHeight;

            shade = sin(21.9911486 * qt_Vertex.y / originalHeight);
            shift.x = amplitude * (originalHeight - leftHeight + (leftHeight - rightHeight) * (qt_Vertex.x / originalWidth)) * shade;

            gl_Position = qt_Matrix * (qt_Vertex - shift);

            shade = 0.2 * (2.0 - shade ) * (1.0 - (rightHeight + (leftHeight  - rightHeight) * (1.0 - qt_Vertex.y / originalWidth)) / originalHeight);
        }
    "

    fragmentShader: "
        varying highp vec2 qt_TexCoord0;
        uniform lowp float qt_Opacity;
        uniform sampler2D source;
        varying lowp float shade;
        void main() {
            highp vec4 color = texture2D(source, qt_TexCoord0);
            color.rgb *= 1.0 - shade;
            gl_FragColor = color * qt_Opacity;
        }
    "
}
