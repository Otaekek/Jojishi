#version 400

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_uv;
layout(location = 3) in vec3 in_Normal;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 pos_color;
out vec2 uv;
out vec3 normal;

void main(void)
{
	uv = in_uv;
    gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
    gl_Position *= M;
    gl_Position *= V;
    gl_Position *= P;
	pos_color = gl_Position.xyz;
	normal = in_Normal;
}