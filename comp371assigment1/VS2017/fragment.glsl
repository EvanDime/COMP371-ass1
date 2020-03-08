#version 330 core
in vec3 vertexColor;
in vec2 vertexUV;
uniform sampler2D textureSampler;
out vec4 FragColor;
void main()
{
	FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);
	vec4 textureColor = texture( textureSampler, vertexUV );
}