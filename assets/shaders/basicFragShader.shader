#version 400

in vec3 pos_color;
in mat4	camPos;
in vec2 uv;
in vec3 normal;

uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 ambiant;

uniform sampler2D textDiffuse;

uniform int has_diffuse;

out vec4 FragColor;

void main(void)
{

	vec3 sunlight = vec3(0, 200, 200);
	vec3 ray;

	vec3 viewDir;
	vec3 reflectDir;
	float specS = 2.0f;
	float spec;
	vec3 frag_Normal;
	vec3 specularResult, diffuseResult;

	frag_Normal = normalize(normal);

	ray = normalize(sunlight - pos_color);
	viewDir = normalize((((-vec4(camPos[0][3], camPos[1][3], camPos[2][3],  1)) + vec4(pos_color.xyz, 1.0f)))).xyz;
	reflectDir = reflect(-ray, frag_Normal);

	spec = clamp(pow(max(dot(viewDir, reflectDir), 0.0), specS), 0, 1);
	specularResult = spec * 2 * specular;
	specularResult *= clamp(dot(ray, frag_Normal), 0, 1);
	if (has_diffuse == 0)
		diffuseResult = clamp(dot(ray, frag_Normal), 0, 1) * diffuse;
	else
		diffuseResult = clamp(dot(ray, frag_Normal), 0, 1) * texture(textDiffuse, uv).rgb;
	FragColor = vec4(diffuseResult + (specularResult) + ambiant, 1);
}
