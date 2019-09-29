#version 330 core

in vec3 interpolateColor;

out vec3 color;

void main()
{
	color = interpolateColor; //vec3( 0.0, 0.0, 1.0);
}
