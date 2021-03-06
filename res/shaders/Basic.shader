#shader vertex
#version 330 core 


layout(location = 0) in vec4 postion;
layout(location = 1) in vec2 texCoord;

out vec2 v_TextCoord;

uniform mat4 u_MVP;

void main(){
   gl_Position = u_MVP * postion;
   v_TextCoord = texCoord;
};




#shader fragment
#version 330 core 

layout(location = 0) out vec4 color;

in vec2 v_TextCoord;


uniform vec4 u_Color;
uniform sampler2D  u_Texture;

void main(){
   vec4 texColor = texture(u_Texture, v_TextCoord);
   color = texColor;
   // color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};