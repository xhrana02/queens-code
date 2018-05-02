#version 430

layout(location=0) out vec4 fragColor;

uniform layout(binding = 0) sampler2D textureMap;
uniform float texRepeat;

uniform vec4 color;

uniform vec3 lightPos;
uniform vec4 lightCol;
	  

in perVertex
{
	vec3 normal;
	vec2 texcoord;
} perVertex_in;

void main()
{
	vec3 normal = normalize(perVertex_in.normal);
	vec4 texCol = texture(textureMap, perVertex_in.texcoord * texRepeat) * color;
	vec4 ambiWeight = vec4(0.6, 0.6, 0.6, 1.0);
	vec4 diffWeight = vec4(0.6, 0.6, 0.6, 1.0);
	
	vec4 ambient = texCol * ambiWeight;
	vec4 diffuse = texCol * diffWeight * lightCol * max(0,dot(normal, normalize(lightPos)));
	
	fragColor = ambient + diffuse;
}