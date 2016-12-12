#version 400

in vec3 pos_color;
in vec3	camPos;
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

	vec3 sunlight = vec3(0, 0, 200);
	vec3 ray;

	vec3 viewDir;
	vec3 reflectDir;
	float specS = 32.0f;
	float spec;
	vec3 frag_Normal;
	vec3 specularResult, diffuseResult;

	frag_Normal = normalize(normal);

	ray = normalize(sunlight - pos_color);
	viewDir = normalize(camPos + pos_color);
	reflectDir = reflect(-ray, frag_Normal);

	spec = clamp(pow(max(dot(viewDir, reflectDir), 0.0), specS), 0, 1);
	specularResult = spec * specular * 2;
	specularResult *= clamp(dot(ray, frag_Normal), 0, 1);
	if (has_diffuse == 0)
		diffuseResult = clamp(dot(ray, frag_Normal), 0, 1) * diffuse;
	else
		diffuseResult = clamp(dot(ray, frag_Normal), 1, 1) * texture(textDiffuse, uv).rgb;
	FragColor = vec4(diffuseResult + (specularResult) + ambiant, 1);
}
