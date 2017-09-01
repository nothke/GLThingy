#version 120

varying vec2 texCoord0;
varying vec3 normalOut;
varying vec3 viewDirOut;

uniform sampler2D diffuseMap;
uniform sampler2D brdfMap;

void main()
{
	vec4 color = texture2D(diffuseMap, texCoord0);
	vec3 lightDir = normalize(vec3(1, 1, -1));
	//lightDir = vec3(0, 1, 0);
	float ndotl = dot(normalize(normalOut), lightDir);

	float l = clamp(0.5 + ndotl * 0.5, 0, 1);

	vec3 viewDir = vec3(0, 0, 1);
	//vec3 viewDir = normalize(viewDirOut);
	vec3 h = normalize(viewDir - lightDir);
	float ndoth = dot(normalize(normalOut), h);
	float spec = pow(ndoth, 2);

	spec = clamp(spec, 0, 1);

	//spec = spec + 0.5;
	//spec = clamp(0.5 + spec * 0.5, 0, 1);

	vec4 brdf = texture2D(brdfMap, vec2(spec, 1 - l));

	//gl_FragColor = vec4(spec, spec, spec, 1);
	gl_FragColor = color * brdf;
	//gl_FragColor = color * light;
	
}