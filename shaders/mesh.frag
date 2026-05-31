#version 330 core

in vec3 vColor;
in vec2 vUv;

uniform sampler2D uTexture;
uniform float uTextureMix;

out vec4 FragColor;

void main()
{
	vec4 textured = texture(uTexture, vUv);
	FragColor = mix(vec4(vColor, 1.0), textured, clamp(uTextureMix, 0.0, 1.0));
}
