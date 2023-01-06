import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import RenderingSandbox

Window {
    id: root

    width: 800
    height: 800
    visible: true
    Component.onCompleted: DrawManager.parseFile();
    color: "#D9D9D9"

    RowLayout {
        anchors.centerIn: parent
        width: parent.width - 32
        height: parent.height - 32

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true

                color: "white"

                Repeater {
                    id: repeater

                    readonly property int sizeFactor: Math.min(repeater.width, repeater.height) / 2

                    height: parent.height; width: parent.width;
                    model: DrawManager.drawingModel

                    Triangle {
                        width: parent.width
                        height: parent.height

                        x: -repeater.sizeFactor
                        y: -repeater.sizeFactor

                        readonly property int finalX1: (model.x1) * repeater.sizeFactor;
                        readonly property int finalY1: (model.y1) * repeater.sizeFactor;
                        readonly property int finalZ1: (model.z1) * repeater.sizeFactor;
                        readonly property int finalX2: (model.x2) * repeater.sizeFactor;
                        readonly property int finalY2: (model.y2) * repeater.sizeFactor;
                        readonly property int finalZ2: (model.z2) * repeater.sizeFactor;
                        readonly property int finalX3: (model.x3) * repeater.sizeFactor;
                        readonly property int finalY3: (model.y3) * repeater.sizeFactor;
                        readonly property int finalZ3: (model.z3) * repeater.sizeFactor;

                        property variant rotated1: trackBall.rotationQ?.rotateVector([finalX1, finalY1, finalZ1]) ?? null
                        property variant rotated2: trackBall.rotationQ?.rotateVector([finalX2, finalY2, finalZ2]) ?? null
                        property variant rotated3: trackBall.rotationQ?.rotateVector([finalX3, finalY3, finalZ3]) ?? null


                        x1: rotated1  ? rotated1[0] : finalX1
                        y1: rotated1  ? rotated1[1] : finalY1
                        x2: rotated2  ? rotated2[0] : finalX2
                        y2: rotated2  ? rotated2[1] : finalY2
                        x3: rotated3  ? rotated3[0] : finalX3
                        y3: rotated3  ? rotated3[1] : finalY3
                        color: model.color
                        rotation: 180
                        z: (rotated1 && rotated2 && rotated3
                            ? rotated1[2] + rotated2[2] + rotated3[2]
                            : finalZ1 + finalZ2 + finalZ3) + 1000000 // last value fixes negative z falling out
                    }
                }

                MouseArea {
                    id: trackBall

                    anchors.fill: parent
                    rotation: 180

                    property variant rotationQ: null
                    property variant start: null
                    property variant lastQ: Quaternion {}
                    property variant currQ: Quaternion {}

                    component Quaternion: QtObject {
                        property double w: 1
                        property double x: 0
                        property double y: 0
                        property double z: 0

                        function normalize() {
                            let norm = Math.sqrt(w * w + x * x + y * y + z * z);
                            norm = 1 / norm;

                            norm = norm < 1e-16 ? 0 : norm;

                            w *= norm;
                            x *= norm;
                            y *= norm;
                            z *= norm;
                        }

                        function mul(w, x, y, z) {
                            let tmp = Object.assign({}, this)

                            tmp.w = this.w * w - this.x * x - this.y * y - this.z * z;
                            tmp.x = this.w * x + this.x * w + this.y * z - this.z * y;
                            tmp.y = this.w * y + this.y * w + this.z * x - this.x * z;
                            tmp.z = this.w * z + this.z * w + this.x * y - this.y * x;

                            return tmp
                        }

                        function rotateVector(v) {
                            var qw = this['w'];
                            var qx = this['x'];
                            var qy = this['y'];
                            var qz = this['z'];

                            var vx = v[0];
                            var vy = v[1];
                            var vz = v[2];

                            // t = 2q x v
                            var tx = 2 * (qy * vz - qz * vy);
                            var ty = 2 * (qz * vx - qx * vz);
                            var tz = 2 * (qx * vy - qy * vx);

                            // v + w t + q x t
                            return [
                              vx + qw * tx + qy * tz - qz * ty,
                              vy + qw * ty + qz * tx - qx * tz,
                              vz + qw * tz + qx * ty - qy * tx];
                        }
                    }


                    function project(x, y) {
                        let r = 1

                        let res = Math.min(width, height) - 1;

                        // map to -1 to 1
                        x = (2 * x - width - 1) / res
                        y = (2 * y - height - 1) / res

                        if (x * x + y * y <= r * r / 2)
                         var z = Math.sqrt(r * r - x * x + y * y);
                        else
                             z = r * r / 2 / Math.sqrt(x * x + y * y);

                        return [x, y, z]
                    }

                    onPressed: {
                        start = { mouseX, mouseY }
                    }

                    onReleased: {
                        lastQ = Object.assign({}, rotationQ)
                    }

                    onMouseXChanged: {
                        let u = project(start.mouseX, start.mouseY)
                        let v = project(mouseX, mouseY)

                        let ux = u[0], uy = u[1], uz = u[2];
                        let vx = v[0], vy = v[1], vz = v[2];

                        let dot = ux * vx + uy * vy + uz * vz;

                        let wx = uy * vz - uz * vy;
                        let wy = uz * vx - ux * vz;
                        let wz = ux * vy - uy * vx;

                        currQ.w = dot + Math.sqrt(dot * dot + wx * wx + wy * wy + wz * wz)
                        currQ.x = wx
                        currQ.y = wy
                        currQ.z = wz
                        currQ.normalize()
                        trackBall.rotationQ = currQ.mul(lastQ.w, lastQ.x, lastQ.y, lastQ.z)
                    }
                }
            }
        }
    }
}
