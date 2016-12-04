#version 400

in vec3 pos_color;
in mat4	camPos;
in vec2 uv;
in vec3 normal;

uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 ambiant;

//uniform sampler2D text;

out vec4 FragColor;

void main(void)
{
	vec3 sunlight = vec3(0, 150, 0);
	vec3 ray;
	vec3 viewDir;
	vec3 reflectDir;
	float specS = 32.0f;
	float spec;
	vec3 frag_Normal;
	vec3 specularResult, diffuseResult;

	frag_Normal = normalize(normal);

	ray = normalize(sunlight - pos_color);
	viewDir = normalize(((vec4(0, 0, 0, 1)).xyz - pos_color));
	reflectDir = reflect(-ray, frag_Normal);

	spec = clamp(pow(max(dot(viewDir, reflectDir), 0.0), specS), 0, 1);

	specularResult = vec3(1, 1, 1) * spec * 20 * specular;
	diffuseResult = clamp(dot(ray, frag_Normal), 0, 1) * diffuse;
	FragColor = vec4(diffuseResult + specularResult + ambiant, 1.0f);
	//FragColor = vec4(texture(text, t).r, texture(text, t).g, texture(text, t).b, 1.0f);
}