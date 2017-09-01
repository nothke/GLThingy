#version 120

varying vec2 texCoord0;
varying vec3 normalOut;
uniform sampler2D diffuse;
uniform sampler2D brdfMap;

void main()
{
	vec4 color = texture2D(diffuse, texCoord0);
	float light = dot(normalOut, vec3(1, 1, -1));

	float l = 0.5 + light * 0.5;

	light = clamp(light, 0.2, 1);

	vec4 brdf = texture2D(brdfMap, vec2(0, l));

	gl_FragColor = brdf;
	//gl_FragColor = color * light;
	
}