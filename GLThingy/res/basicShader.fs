#version 120

varying vec2 texCoord0;
varying vec3 normalOut;
uniform sampler2D diffuse;
uniform sampler2D brdfMap;

void main()
{
	vec4 color = texture2D(diffuse, texCoord0);
	vec3 lightDir = normalize(vec3(1, 1, -1));
	float ndotl = dot(normalize(normalOut), lightDir);

	float l = clamp(0.5 + ndotl * 0.5, 0, 1);

	vec4 brdf = texture2D(brdfMap, vec2(l, 1 - l));

	gl_FragColor = brdf;
	//gl_FragColor = color * light;
	
}