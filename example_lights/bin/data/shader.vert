#version 330

in vec4 position;
in vec3 normal;

out vec3 vertexNormal;
out vec3 cameraSpacePosition;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

uniform NormalMatrix{
	mat3 matrix;
}normalMatrix;

void main(){
	vertexNormal = normalize(normalMatrix.matrix * normal);
	cameraSpacePosition = (modelViewMatrix * position).xyz;
	gl_Position = modelViewProjectionMatrix * position;
}
