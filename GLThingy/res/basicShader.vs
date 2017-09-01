#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normalOut;
varying vec3 viewDirOut;

uniform mat4 transform;
uniform vec3 cameraPosition;

void main()
{
	vec3 worldPos = (transform * vec4(position, 1.0)).xyz;
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	//normalOut = normal;
	normalOut = (transform * vec4(normal, 0.0)).xyz;
	viewDirOut = worldPos - cameraPosition;
}