#version 150

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec3 vertexNormal;
out vec3 cameraSpacePosition;
out vec2 TexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

uniform NormalMatrix{
	mat3 normalMatrix;
};

void main(){
	vertexNormal = normalize(normalMatrix * normal);
	cameraSpacePosition = (modelViewMatrix * position).xyz;
	TexCoord = texcoord;
	gl_Position = modelViewProjectionMatrix * position;
}