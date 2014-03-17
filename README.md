## Overview
Uniform buffers are an alternative way to upload data to GLSL. They are available in openGl 3.2+. Normally Uniform buffers can be tedious to set up because you have to worry about layout differences between client side and GLSL. ofxUbo takes care of all that and makes it easy to use uniform buffers. ofxUbo works with shared and std140 layouts. Tested for openframeworks 0.8.0

#### Advantages over ofShader::setUniform
1. Uniform Buffers are a more organized way to send a "struct" of data
2. If you are sending the same data to multiple shaders, Ubo's can significantly reduce code.
3. With Ubo's, you can send arbitary data to GLSL much more easily. For example sending an array of 4x4 matrices is trivial with ubos, but would be quite difficult with ofShader::setUniform.


## How to use

#### step 1: Use programable renderer

First make sure you are using the programable renderer in openframeworks. Set that in your main function before anything.

```
ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
``` 
#### step 2: Define client side struct

Next define a struct in openframewroks that matches your uniform block in GLSL. For example if your uniform block looks like this in GLSL.

```
uniform RandomData
{
	int x;
	vec2 position;
	float numbers[20];
	mat3 transform;
	mat4 bones[100];
	bool drawMask;
	mat4x3 matrix; // 4 col, 3 row
} ;
``` 

in openframeworks you define something that looks like this. Names do not have to match but the types do.

```
struct RandomData
{
	int x;
	ofVec2f position;
	float numbers[20];
	ofMatrix3x3 transform;
	ofMatrix4x4 bones[100];
	int drawmask // bool in GlSL in actually an int 
	float matrix[4][3] // 4 row, 3 col
}
```
Note that in openframeworks matrices are Row Major, but in GLSL they are Column major. But this ok since ofxUbo uploads a row major matrix as Column major matrix in GLSL. Genral rule is, on client side work in Row Major, and in GLSL work in Column Major.

here is a table to match GLSL types to openframework side types;

GLSL         | Openframeworks| 
------------ | ------------- | 
int			 | int  			|
float       | float	|
bool|int
vec2|ofVec2f or float[2]
vec3| ofVec3f or float [3]
vec4| ofVec4f or float [4]
mat3|ofMatrix3x3 or float[3][3]|
mat4 | ofMatrix4x4 or float[4][4]|
mat2|float[2][2]
mat2x3|float[2][3]
mat2x4|float[2][4]
mat3x2|float[3][2]
mat3x4|float[3][4]
mat4x2|float[4][2]
mat4x3|float[4][3]

Of coarse any of these types can be turned into an array.

#### step 3 ofxUboShader

Instead of ofShader use ofxUboShader, which is just a subclass with 2 extra functions.

```
ofxUboShader shader

```
create an Instance of your struct and set its members

```
RandomData myRandomData
// set members of myRandomData
```

use ofxUboShader::setUniformBuffer to upload your data to GLSL. Should be done inside draw function. The first parameter is the uniform block name, the second is your data.

```
void ofApp::draw(){
	shader.begin();
	shader.setUniformBuffer("RandomData",myRandomData);
	// draw stuff
	shader.end();    
}

```


## Manual padding
By default ofxUbo queries the layout in GLSL and uploads your data accordingly. However if you want to manual pad and upload data yourself you can do that as well.

To get the layout, call ofxUboShader::printLayout. This prints uniform block info to the console

```
// prints the layout of 'Material' to console
shader.printLayout("Material");
```
then use ofxUboShader::setUniformBuffer with an extra boolean argument

```
shader.setUniformBuffer("Material", blueShine, true);

```
for example suppose your srtuct in GLSL looks like this

```
uniform Settings{
	vec2 center;
	vec4 color;
};
```
then shader.printLayout("Settings") will print out this

```
Block Name: Settings
Layout Size: 32
	Settings.center
		GL_FLOAT_VEC2
		offset: 0
		size: 8
		array Stride: 0
		matrix Stride: 0
	Settings.color
		GL_FLOAT_VEC4
		offset: 16
		size: 16
		array Stride: 0
		matrix Stride: 0
```

By looking at the **Offset** info, you know your struct on the cpu side should look like this

```
struct Settings {
    ofVec2f center;
    float pad[2];
    ofVec4f color;
};

```

##Notes
* You can use double types only with manual padding 
* The auto upload does not yet support double types. To do this I need to query alignment of types. C++11 has [alignof](http://en.cppreference.com/w/cpp/language/alignof), but openframeworks currently does not support C++11. I will support doubles as soon as openframeworks upgrades. If someone knows a way to query alignments please let me know. 
* If a struct is not uploading correctly please let me know. Post an issue with both your cpu side struct and the corresponding uniform block. I will look at it. Also try uploading manually.
* Pull requests are encouraged 






    							



 

