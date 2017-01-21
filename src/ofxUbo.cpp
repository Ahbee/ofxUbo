
#include "ofxUbo.h"

vector<bool> ofxUboSingeltons::bindingPointSlots;
map<int, int> ofxUboSingeltons::spGLSLTypeSize;
map<int,string> ofxUboSingeltons::spGLSLType;
map<int, int> ofxUboSingeltons::matrixRowSize;
map<int,int> ofxUboSingeltons::matrixRowCount;
bool ofxUboSingeltons::__spInit = ofxUboSingeltons::init();

//--------------------------------------------------------------

bool ofxUboSingeltons::init(){
    spGLSLTypeSize[GL_FLOAT] = sizeof(float);
	spGLSLTypeSize[GL_FLOAT_VEC2] = sizeof(float)*2;
	spGLSLTypeSize[GL_FLOAT_VEC3] = sizeof(float)*3;
	spGLSLTypeSize[GL_FLOAT_VEC4] = sizeof(float)*4;
    
	spGLSLTypeSize[GL_DOUBLE] = sizeof(double);
	spGLSLTypeSize[GL_DOUBLE_VEC2] = sizeof(double)*2;
	spGLSLTypeSize[GL_DOUBLE_VEC3] = sizeof(double)*3;
	spGLSLTypeSize[GL_DOUBLE_VEC4] = sizeof(double)*4;
    
	spGLSLTypeSize[GL_SAMPLER_1D] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_3D] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_CUBE] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_1D_SHADOW] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D_SHADOW] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_1D_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_1D_ARRAY_SHADOW] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D_ARRAY_SHADOW] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D_MULTISAMPLE] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D_MULTISAMPLE_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_CUBE_SHADOW] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_BUFFER] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D_RECT] = sizeof(int);
	spGLSLTypeSize[GL_SAMPLER_2D_RECT_SHADOW] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_1D] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_2D] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_3D] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_CUBE] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_1D_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_2D_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_2D_MULTISAMPLE] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_BUFFER] = sizeof(int);
	spGLSLTypeSize[GL_INT_SAMPLER_2D_RECT] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_1D] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_3D] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_CUBE] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_1D_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_BUFFER] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_RECT] = sizeof(int);
	spGLSLTypeSize[GL_BOOL] = sizeof(int);
	spGLSLTypeSize[GL_INT] = sizeof(int);
	spGLSLTypeSize[GL_BOOL_VEC2] = sizeof(int)*2;
	spGLSLTypeSize[GL_INT_VEC2] = sizeof(int)*2;
	spGLSLTypeSize[GL_BOOL_VEC3] = sizeof(int)*3;
	spGLSLTypeSize[GL_INT_VEC3] = sizeof(int)*3;
	spGLSLTypeSize[GL_BOOL_VEC4] = sizeof(int)*4;
	spGLSLTypeSize[GL_INT_VEC4] = sizeof(int)*4;
    
	spGLSLTypeSize[GL_UNSIGNED_INT] = sizeof(int);
	spGLSLTypeSize[GL_UNSIGNED_INT_VEC2] = sizeof(int)*2;
	spGLSLTypeSize[GL_UNSIGNED_INT_VEC3] = sizeof(int)*2;
	spGLSLTypeSize[GL_UNSIGNED_INT_VEC4] = sizeof(int)*2;
    
	spGLSLTypeSize[GL_FLOAT_MAT2] = sizeof(float)*4;
	spGLSLTypeSize[GL_FLOAT_MAT3] = sizeof(float)*9;
	spGLSLTypeSize[GL_FLOAT_MAT4] = sizeof(float)*16;
	spGLSLTypeSize[GL_FLOAT_MAT2x3] = sizeof(float)*6;
	spGLSLTypeSize[GL_FLOAT_MAT2x4] = sizeof(float)*8;
	spGLSLTypeSize[GL_FLOAT_MAT3x2] = sizeof(float)*6;
	spGLSLTypeSize[GL_FLOAT_MAT3x4] = sizeof(float)*12;
	spGLSLTypeSize[GL_FLOAT_MAT4x2] = sizeof(float)*8;
	spGLSLTypeSize[GL_FLOAT_MAT4x3] = sizeof(float)*12;
	spGLSLTypeSize[GL_DOUBLE_MAT2] = sizeof(double)*4;
	spGLSLTypeSize[GL_DOUBLE_MAT3] = sizeof(double)*9;
	spGLSLTypeSize[GL_DOUBLE_MAT4] = sizeof(double)*16;
    
    spGLSLType[GL_FLOAT] = "GL_FLOAT";
	spGLSLType[GL_FLOAT_VEC2] = "GL_FLOAT_VEC2";
	spGLSLType[GL_FLOAT_VEC3] = "GL_FLOAT_VEC3";
	spGLSLType[GL_FLOAT_VEC4] = "GL_FLOAT_VEC4";
	spGLSLType[GL_DOUBLE] = "GL_DOUBLE";
	spGLSLType[GL_DOUBLE_VEC2] = "GL_DOUBLE_VEC2";
	spGLSLType[GL_DOUBLE_VEC3] = "GL_DOUBLE_VEC3";
	spGLSLType[GL_DOUBLE_VEC4] = "GL_DOUBLE_VEC4";
	spGLSLType[GL_SAMPLER_1D] = "GL_SAMPLER_1D";
	spGLSLType[GL_SAMPLER_2D] = "GL_SAMPLER_2D";
	spGLSLType[GL_SAMPLER_3D] = "GL_SAMPLER_3D";
	spGLSLType[GL_SAMPLER_CUBE] = "GL_SAMPLER_CUBE";
	spGLSLType[GL_SAMPLER_1D_SHADOW] = "GL_SAMPLER_1D_SHADOW";
	spGLSLType[GL_SAMPLER_2D_SHADOW] = "GL_SAMPLER_2D_SHADOW";
	spGLSLType[GL_SAMPLER_1D_ARRAY] = "GL_SAMPLER_1D_ARRAY";
	spGLSLType[GL_SAMPLER_2D_ARRAY] = "GL_SAMPLER_2D_ARRAY";
	spGLSLType[GL_SAMPLER_1D_ARRAY_SHADOW] = "GL_SAMPLER_1D_ARRAY_SHADOW";
	spGLSLType[GL_SAMPLER_2D_ARRAY_SHADOW] = "GL_SAMPLER_2D_ARRAY_SHADOW";
	spGLSLType[GL_SAMPLER_2D_MULTISAMPLE] = "GL_SAMPLER_2D_MULTISAMPLE";
	spGLSLType[GL_SAMPLER_2D_MULTISAMPLE_ARRAY] = "GL_SAMPLER_2D_MULTISAMPLE_ARRAY";
	spGLSLType[GL_SAMPLER_CUBE_SHADOW] = "GL_SAMPLER_CUBE_SHADOW";
	spGLSLType[GL_SAMPLER_BUFFER] = "GL_SAMPLER_BUFFER";
	spGLSLType[GL_SAMPLER_2D_RECT] = "GL_SAMPLER_2D_RECT";
	spGLSLType[GL_SAMPLER_2D_RECT_SHADOW] = "GL_SAMPLER_2D_RECT_SHADOW";
	spGLSLType[GL_INT_SAMPLER_1D] = "GL_INT_SAMPLER_1D";
	spGLSLType[GL_INT_SAMPLER_2D] = "GL_INT_SAMPLER_2D";
	spGLSLType[GL_INT_SAMPLER_3D] = "GL_INT_SAMPLER_3D";
	spGLSLType[GL_INT_SAMPLER_CUBE] = "GL_INT_SAMPLER_CUBE";
	spGLSLType[GL_INT_SAMPLER_1D_ARRAY] = "GL_INT_SAMPLER_1D_ARRAY";
	spGLSLType[GL_INT_SAMPLER_2D_ARRAY] = "GL_INT_SAMPLER_2D_ARRAY";
	spGLSLType[GL_INT_SAMPLER_2D_MULTISAMPLE] = "GL_INT_SAMPLER_2D_MULTISAMPLE";
	spGLSLType[GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
	spGLSLType[GL_INT_SAMPLER_BUFFER] = "GL_INT_SAMPLER_BUFFER";
	spGLSLType[GL_INT_SAMPLER_2D_RECT] = "GL_INT_SAMPLER_2D_RECT";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_1D] = "GL_UNSIGNED_INT_SAMPLER_1D";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D] = "GL_UNSIGNED_INT_SAMPLER_2D";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_3D] = "GL_UNSIGNED_INT_SAMPLER_3D";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_CUBE] = "GL_UNSIGNED_INT_SAMPLER_CUBE";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_1D_ARRAY] = "GL_UNSIGNED_INT_SAMPLER_1D_ARRAY";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_ARRAY] = "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE] = "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_BUFFER] = "GL_UNSIGNED_INT_SAMPLER_BUFFER";
	spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_RECT] = "GL_UNSIGNED_INT_SAMPLER_2D_RECT";
	spGLSLType[GL_BOOL] = "GL_BOOL";
	spGLSLType[GL_INT] = "GL_INT";
	spGLSLType[GL_BOOL_VEC2] = "GL_BOOL_VEC2";
	spGLSLType[GL_INT_VEC2] = "GL_INT_VEC2";
	spGLSLType[GL_BOOL_VEC3] = "GL_BOOL_VEC3";
	spGLSLType[GL_INT_VEC3] = "GL_INT_VEC3";
	spGLSLType[GL_BOOL_VEC4] = "GL_BOOL_VEC4";
	spGLSLType[GL_INT_VEC4] = "GL_INT_VEC4";
	spGLSLType[GL_UNSIGNED_INT] = "GL_UNSIGNED_INT";
	spGLSLType[GL_UNSIGNED_INT_VEC2] = "GL_UNSIGNED_INT_VEC2";
	spGLSLType[GL_UNSIGNED_INT_VEC3] = "GL_UNSIGNED_INT_VEC3";
	spGLSLType[GL_UNSIGNED_INT_VEC4] = "GL_UNSIGNED_INT_VEC4";
	spGLSLType[GL_FLOAT_MAT2] = "GL_FLOAT_MAT2";
	spGLSLType[GL_FLOAT_MAT3] = "GL_FLOAT_MAT3";
	spGLSLType[GL_FLOAT_MAT4] = "GL_FLOAT_MAT4";
	spGLSLType[GL_FLOAT_MAT2x3] = "GL_FLOAT_MAT2x3";
	spGLSLType[GL_FLOAT_MAT2x4] = "GL_FLOAT_MAT2x4";
	spGLSLType[GL_FLOAT_MAT3x2] = "GL_FLOAT_MAT3x2";
	spGLSLType[GL_FLOAT_MAT3x4] = "GL_FLOAT_MAT3x4";
	spGLSLType[GL_FLOAT_MAT4x2] = "GL_FLOAT_MAT4x2";
	spGLSLType[GL_FLOAT_MAT4x3] = "GL_FLOAT_MAT4x3";
	spGLSLType[GL_DOUBLE_MAT2] = "GL_DOUBLE_MAT2";
	spGLSLType[GL_DOUBLE_MAT3] = "GL_DOUBLE_MAT3";
	spGLSLType[GL_DOUBLE_MAT4] = "GL_DOUBLE_MAT4";
    
    matrixRowSize[GL_FLOAT_MAT2] = sizeof(float) * 2;
    matrixRowSize[GL_FLOAT_MAT3] = sizeof(float) * 3;
    matrixRowSize[GL_FLOAT_MAT4] = sizeof(float) * 4;
    matrixRowSize[GL_FLOAT_MAT2x3] = sizeof(float) * 2;
    matrixRowSize[GL_FLOAT_MAT2x4] = sizeof(float) * 2;
    matrixRowSize[GL_FLOAT_MAT3x2] = sizeof(float) * 3;
    matrixRowSize[GL_FLOAT_MAT3x4] = sizeof(float) * 3;
    matrixRowSize[GL_FLOAT_MAT4x2] = sizeof(float) * 4;
    matrixRowSize[GL_FLOAT_MAT4x3] = sizeof(float) * 4;
    matrixRowSize[GL_DOUBLE_MAT2] = sizeof(double) * 2;
    matrixRowSize[GL_DOUBLE_MAT3] = sizeof(double) * 3;
    matrixRowSize[GL_DOUBLE_MAT4] = sizeof(double) * 4;
    
    
    matrixRowCount[GL_FLOAT_MAT2] =  2;
    matrixRowCount[GL_FLOAT_MAT3] =  3;
    matrixRowCount[GL_FLOAT_MAT4] =  4;
    matrixRowCount[GL_FLOAT_MAT2x3] =  2;
    matrixRowCount[GL_FLOAT_MAT2x4] =  2;
    matrixRowCount[GL_FLOAT_MAT3x2] =  3;
    matrixRowCount[GL_FLOAT_MAT3x4] =  3;
    matrixRowCount[GL_FLOAT_MAT4x2] =  4;
    matrixRowCount[GL_FLOAT_MAT4x3] =  4;
    matrixRowCount[GL_DOUBLE_MAT2] =  2;
    matrixRowCount[GL_DOUBLE_MAT3] =  3;
    matrixRowCount[GL_DOUBLE_MAT4] =  4;
    
    return true;
}

//--------------------------------------------------------------

GLuint ofxUboSingeltons::findFirstAvaliableBindingSpot(){
    for (int i = 0; i < bindingPointSlots.size(); i++) {
        if (bindingPointSlots[i] == false){
            bindingPointSlots[i] = true;
            return i;
        }
    }
    bindingPointSlots.push_back(true);
    return (bindingPointSlots.size() - 1);
}

//--------------------------------------------------------------

ostream& operator<<(ostream& stream, const ofxUboLayout& layout){
    string output = "\nBlock Name: " + layout.blockName + "\nLayout Size: " + ofToString(layout.size) + "\n";
    for (int i = 0; i < layout.uniformData.size(); i++) {
        ofxUniformInfo uniformInfo = layout.uniformData[i];
        output+= "\t" + uniformInfo.name + "\n" +
        "\t\t" + "type: " + ofxUboSingeltons::spGLSLType[uniformInfo.type] + "\n" + "\t\t"
        + "offset: " + ofToString(uniformInfo.offest) + "\n" + "\t\t"
        + "size: " + ofToString(uniformInfo.size) + "\n" + "\t\t"
        + "array Stride: " + ofToString(uniformInfo.arrayStride) + "\n" + "\t\t"
        + "matrix Stride: " + ofToString(uniformInfo.matrixStride) + "\n";
    }
    return stream << output;
}
//--------------------------------------------------------------


ofxUboShader::ofxUboShader():ofShader(){
    
}

//--------------------------------------------------------------


ofxUboShader::~ofxUboShader(){
}

//--------------------------------------------------------------

ofxUboShader::ofxUboShader(const ofxUboShader &mom):ofShader(mom){
    ubos = mom.ubos;
    for (auto it = ubos.begin(); it!=ubos.end(); it++) {
        const string &name = it->first;
        shared_ptr<ofxUboBase> uboRef = it->second;
        bindToLocation(name, uboRef->getBindingPoint());
    }
}

//--------------------------------------------------------------

ofxUboShader& ofxUboShader::operator=(const ofxUboShader &mom){
    ofShader::operator=(mom);
    ubos = mom.ubos;
    for (auto it = ubos.begin(); it!=ubos.end(); it++) {
        const string &name = it->first;
        shared_ptr<ofxUboBase> uboRef = it->second;
        bindToLocation(name, uboRef->getBindingPoint());
    }
    return *this;
}

//--------------------------------------------------------------

void ofxUboShader::printLayout(const string &blockname){
    ofxUboLayout layout = getLayout(blockname);
    cout << layout << endl;
}

//--------------------------------------------------------------

void ofxUboShader::bindToLocation(const string &blockName, GLuint location){
    GLuint blockIndex = glGetUniformBlockIndex(getProgram(),blockName.c_str());
    glUniformBlockBinding(getProgram(),blockIndex,location);
}

//--------------------------------------------------------------

ofxUboLayout ofxUboShader::getLayout(const string &blockName){
    ofxUboLayout layout;
    layout.blockName = blockName;
    
    // get block Index
    GLuint blockIndex = glGetUniformBlockIndex(getProgram(),blockName.c_str());
    if (blockIndex == GL_INVALID_INDEX) {
        ofLogError("ofxUbo") << "The block '" << blockName << "' does not exist in program:" << getProgram() <<
        " make sure you are actually using the block '" << blockName << "' inside your GLSL program, otherwise openGL will not consider your block active";
        layout.blockName = "";
        layout.size = -99;
        return layout;
    }
    
    // get the Size of the Uniform Block
    int uboSize;
    glGetActiveUniformBlockiv(getProgram(), blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
    layout.size = uboSize;
    
    // get the number of active uniforms of the Uniform Block
    int activeUnif;
    glGetActiveUniformBlockiv(getProgram(), blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUnif);
    
    // get each unifom inside the Uniform block
    unsigned int *indices = new unsigned int[activeUnif];
    glGetActiveUniformBlockiv(getProgram(), blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (int *)indices);
    
    // loop through all active Uniforms and get each, uniform's name,type,offset,size,arrayStride,and MatrixStride
    int actualLen, index, uniType,uniSize, uniMatStride, uniArrayStride, uniOffset;
	char name[256];
    
    for (int k = 0; k < activeUnif; ++k) {
		glGetActiveUniformName(getProgram(), indices[k], 256, &actualLen, name);
        glGetActiveUniformsiv(getProgram(), 1, &indices[k], GL_UNIFORM_TYPE, &uniType);
        glGetActiveUniformsiv(getProgram(), 1, &indices[k], GL_UNIFORM_OFFSET, &uniOffset);
        
        // This function retrives array length, not the actual size;
        glGetActiveUniformsiv(getProgram(), 1, &indices[k], GL_UNIFORM_SIZE, &uniSize);
        glGetActiveUniformsiv(getProgram(), 1, &indices[k], GL_UNIFORM_ARRAY_STRIDE, &uniArrayStride);
        glGetActiveUniformsiv(getProgram(), 1, &indices[k], GL_UNIFORM_MATRIX_STRIDE, &uniMatStride);
        
        int auxSize;
        if (uniArrayStride > 0)
            auxSize = uniArrayStride * uniSize;
        
        else if (uniMatStride > 0) {
            
            switch(uniType) {
                case GL_FLOAT_MAT2:
                case GL_FLOAT_MAT2x3:
                case GL_FLOAT_MAT2x4:
                case GL_DOUBLE_MAT2:
                    auxSize = 2 * uniMatStride;
                    break;
                case GL_FLOAT_MAT3:
                case GL_FLOAT_MAT3x2:
                case GL_FLOAT_MAT3x4:
                case GL_DOUBLE_MAT3:
                    auxSize = 3 * uniMatStride;
                    break;
                case GL_FLOAT_MAT4:
                case GL_FLOAT_MAT4x2:
                case GL_FLOAT_MAT4x3:
                case GL_DOUBLE_MAT4:
                    auxSize = 4 * uniMatStride;
                    break;
            }
        }
        else
            auxSize = ofxUboSingeltons::spGLSLTypeSize[uniType];
        
        ofxUniformInfo info;
        info.name = name;
        info.type = uniType;
        info.offest = uniOffset;
        info.size = auxSize;
        info.arrayStride = uniArrayStride;
        info.matrixStride = uniMatStride;
        layout.uniformData.push_back(info);
    }
    // Sort unifoms based on offset. Some opengl drivers seem to fetch uniforms in a non sequential order.
    // The offset data is still correct but glGetActiveUniformBlockiv feeds you uniforms in a random order.
    ofSort(layout.uniformData);
    
    delete[] indices;
    return layout;
}

//-------------------------------------------------------------






