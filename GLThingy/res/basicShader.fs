#version 120

varying vec2 texCoord0;
varying vec3 normalOut;
uniform sampler2D diffuse;

void main()
{
	float light = dot(normalOut, vec3(1, 1, -1));
	light = clamp(light, 0.2, 1);
	gl_FragColor = texture2D(diffuse, texCoord0) * light;
	
}