#version 400

in vec3 pos_color;
in vec2 uv;
in vec3 normal;

//uniform sampler2D text;

out vec4 FragColor;

void main(void)
{
	//FragColor = vec4(texture(text, t).r, texture(text, t).g, texture(text, t).b, 1.0f);
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}