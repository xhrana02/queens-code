#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 tex;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

out perVertex
{
	vec3 normal;
	vec2 texcoord;
} perVertex_out;

void main(){
	perVertex_out.normal = norm;
	perVertex_out.texcoord = tex;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos,1.0);
}