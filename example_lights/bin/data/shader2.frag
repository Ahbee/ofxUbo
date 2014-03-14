#version 150

in vec3 vertexNormal;
in vec3 cameraSpacePosition;
in vec2 TexCoord;

out vec4 outputColor;

uniform Material
{
	vec4 diffuseColor;
	vec4 specularColor;
	float specularShininess;
} Mtl;

struct PerLight
{
	vec3 cameraSpaceLightPos;
	vec4 lightIntensity;
};

const int numberOfLights = 2;

uniform Light
{
	vec4 ambientIntensity;
	float lightAttenuation;
	PerLight lights[numberOfLights];
} Lgt;

uniform sampler2D tex;


float CalcAttenuation(in vec3 cameraSpacePosition,
	in vec3 cameraSpaceLightPos,
	out vec3 lightDirection)
{
	vec3 lightDifference =  cameraSpaceLightPos - cameraSpacePosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);
	lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
	
	return (1 / ( 1.0 + Lgt.lightAttenuation * sqrt(lightDistanceSqr)));
}

vec4 ComputeLighting(in PerLight lightData, in vec3 cameraSpacePosition,
	in vec3 cameraSpaceNormal)
{
	vec3 lightDir;
	vec4 lightIntensity;
	
	float atten = CalcAttenuation(cameraSpacePosition,
	lightData.cameraSpaceLightPos.xyz, lightDir);
	lightIntensity = atten * lightData.lightIntensity;

	vec3 surfaceNormal = normalize(cameraSpaceNormal);
	float cosAngIncidence = dot(surfaceNormal, lightDir);
	cosAngIncidence = clamp(cosAngIncidence,0,1);
	
	vec3 viewDirection = normalize(-cameraSpacePosition);
	
	vec3 halfAngle = normalize(lightDir + viewDirection);
	float angleNormalHalf = acos(dot(halfAngle, surfaceNormal));
	float exponent = angleNormalHalf / Mtl.specularShininess;
	exponent = -(exponent * exponent);
	float gaussianTerm = exp(exponent);
	
	vec4 diffuseColorTex = texture(tex,TexCoord);
	vec4 lighting = diffuseColorTex * lightIntensity * cosAngIncidence;
	lighting += Mtl.specularColor * lightIntensity * gaussianTerm;
	
	return lighting;
}

void main()
{
	vec4 diffuseColorTex = texture(tex,TexCoord);
	vec4 accumLighting = diffuseColorTex * Lgt.ambientIntensity;
	for(int light = 0; light < numberOfLights; light++)
	{
		accumLighting += ComputeLighting(Lgt.lights[light],
			cameraSpacePosition, vertexNormal);
	}
	outputColor = accumLighting;
}