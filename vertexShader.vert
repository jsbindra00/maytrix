#version 330 core
layout (location = 0) in vec3 vertexPos;

uniform mat4 viewMatrix_;
uniform mat4 projectionMatrix_;
uniform mat4 modelMatrix_;
void main()
{
	gl_Position = projectionMatrix_*viewMatrix_*modelMatrix_*vec4(vertexPos, 1.0);
}