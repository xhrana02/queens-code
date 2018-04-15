#version 430

layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 texcoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec2 uv;

void main(){
   uv = texcoords;
   gl_Position = projection * view * model * vec4(pos,1.0);
}