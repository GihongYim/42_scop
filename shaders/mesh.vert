#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 3) in vec2 aUv;

uniform mat4 uMVP;

out vec3 vColor;
out vec2 vUv;

void main()
{
	vColor = aColor;
	vUv = aUv;
	gl_Position = uMVP * vec4(aPosition, 1.0);
}
