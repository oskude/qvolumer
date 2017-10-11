import QtQuick 2.7
import QtQuick.Window 2.2

Rectangle {
	property int div: 8
	property int size: Screen.desktopAvailableWidth < Screen.desktopAvailableHeight ? Screen.desktopAvailableWidth / div : Screen.desktopAvailableHeight / div
	property bool muted: false
	property double volume: 0.5
	property var mainColor: "#cc6e00"
	onVolumeChanged: ring.requestPaint()
	width: size
	height: size
	color: "black"
	Canvas {
		id: ring
		width: parent.width
		height: parent.height
		onPaint: {
			var ctx = getContext("2d")
			ctx.clearRect(0, 0, parent.width, parent.height)
			ctx.lineWidth = parent.height / 16
			ctx.lineCap = "round"
			ctx.strokeStyle = mainColor
			ctx.translate(parent.width/2, parent.height/2)
			ctx.rotate(90 * Math.PI / 180)
			ctx.beginPath()
			ctx.arc(
				0, // x
				0, // y
				parent.height / 3, // radius
				0, // startAngle
				volume * 6.28318531, // endAngle
				false // anticlockwise
			);
			ctx.stroke()
			ctx.setTransform(1, 0, 0, 1, 0, 0)
		}
	}
	Text {
		text: Math.round(volume * 100)
		color: mainColor
		anchors.centerIn: parent
		font.family: "monospace"
		font.pointSize: parent.height / 5
	}
	Text {
		text: "X"
		visible: muted
		color: mainColor
		anchors.centerIn: parent
		font.family: "monospace"
		font.pointSize: parent.height / 2
	}
}
