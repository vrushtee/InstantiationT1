#version 330 core 
layout (location=0) in vec2 position; // 3 must need semicolon
layout (location=1) in vec3 colorVal; // this is for color
layout (location=2) in vec2 OffsetVal; //this is for instance offset

out vec3 color;

void main()  // 4 must add paranthesis
{ 
color = colorVal;
gl_Position = vec4(position + OffsetVal, 0.0,1.0);
} 

