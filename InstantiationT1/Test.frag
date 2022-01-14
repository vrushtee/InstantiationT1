#version 330 core 

out vec4 colorTemp; 
in vec3 color;

void main()  //5 must add paranthesis
{
colorTemp = vec4(color,1);
} 

