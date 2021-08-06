#version 330 core
in vec2 outTexCoord;
out vec4 FragColor;

uniform sampler2D textureID;
void main()
{
	
	FragColor = vec4(1.0,0.0,0.0,1.0);
	//FragColor = texture(textureID, outTexCoord);
}