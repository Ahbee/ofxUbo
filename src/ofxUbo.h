
#pragma once

#include "ofMain.h"

// This struct contains useful singeltons needed to implement a Ubo interface;
// 1. It knows which bindng points are avaible for use, and can find the first avaliable binding spot;
// 2. It contains maps from glsl types to client stide openframework types
struct ofxUboSingeltons {
    static bool __spInit;
    static vector<bool> bindingPointSlots;
    static GLuint findFirstAvaliableBindingSpot();
    static std::map<int, int> spGLSLTypeSize;
    static std::map<int, int> matrixRowSize;
    static std::map<int,int> matrixRowCount;
    static std::map<int, std::string> spGLSLType;
    static bool init();
};

//--------------------------------------------------------------


// used to hold inforamtion about a uniform
struct ofxUniformInfo {
    string name;
    GLint type;
    GLint offest;
    GLint size;
    GLint arrayStride;
    GLint matrixStride;
    bool operator<(const ofxUniformInfo &a) const{
        return offest < a.offest;
    }
};

//--------------------------------------------------------------

// used to store block Layout information
struct ofxUboLayout {
    int size;
    string blockName;
    vector<ofxUniformInfo> uniformData;
};

// prints a Uniform block Layout to the console
ostream& operator<<(ostream& stream, const ofxUboLayout& layout);

//--------------------------------------------------------------

// base class for ofxUbo. It is needed to have continers which store all ofxUbo types;
class ofxUboBase{
public:
    virtual GLuint getBindingPoint() = 0;
    
};

// class used to wrap a ubo, end users do not use this class
// it is used by ofxUboShader internally;
template <class T>
class ofxUbo:public ofxUboBase{
public:
    ofxUbo(const ofxUboLayout &layout);
    virtual ~ofxUbo();
    void loadData(const T &newData);
    void loadDataManually(const T &nemwData);
    GLuint  getBindingPoint(){return bindingPoint;};
    friend class ofxUboShader;
private:
    ofxUboLayout bufferLayout;
    GLuint uboId;
    GLuint bindingPoint;
};

//--------------------------------------------------------------
template <class T>
ofxUbo<T>::ofxUbo(const ofxUboLayout &layout){
    bindingPoint = ofxUboSingeltons::findFirstAvaliableBindingSpot();
    bufferLayout = layout;
    vector<char> buffer(layout.size);
    glGenBuffers(1,&uboId);
    glBindBuffer(GL_UNIFORM_BUFFER,uboId);
    glBufferData(GL_UNIFORM_BUFFER,layout.size,buffer.data(),GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER,bindingPoint,uboId);
}
//--------------------------------------------------------------

template <class T>
ofxUbo<T>::~ofxUbo(){
    glDeleteBuffers(1,&uboId);
    ofxUboSingeltons::bindingPointSlots[bindingPoint] = false;
}
//--------------------------------------------------------------
template <class T>
void ofxUbo<T>::loadData(const T &newData){
    char* dataPtr = (char*)&newData;
    // start with a zero buffer equal to the size of the layout
    vector<char> buffer(bufferLayout.size,'0');
    
    int dataOffest = 0;
    // loop through each unifom of bufferLayout, and add them to buffer
    for (int i = 0; i < bufferLayout.uniformData.size(); i++) {
        const ofxUniformInfo &uniform = bufferLayout.uniformData[i];
        // There are 4 basics types to handle: matrix, matrix array, regular type, and regular type array.
        if (uniform.arrayStride > 0 && uniform.matrixStride > 0) { // is it a matrix array
            int matrixOffset = uniform.offest;
            int arrayCount = uniform.size/uniform.arrayStride;
            for (int j = 0; j < arrayCount; j++) {
                int rowOffset = matrixOffset;
                // This loop uploads one matrix,one row at a time
                for (int k = 0; k < ofxUboSingeltons::matrixRowCount[uniform.type]; k++) {
                    memcpy(buffer.data() + rowOffset, dataPtr + dataOffest, ofxUboSingeltons::matrixRowSize[uniform.type]);
                    dataOffest+=ofxUboSingeltons::matrixRowSize[uniform.type];
                    rowOffset+=uniform.matrixStride;
                }
                matrixOffset+=uniform.arrayStride;
            }
        }else if (uniform.arrayStride == 0 && uniform.matrixStride > 0 ){ // is it a matrix
            int rowOffset = uniform.offest;
            for (int k = 0; k < ofxUboSingeltons::matrixRowCount[uniform.type]; k++) {
                memcpy(buffer.data() + rowOffset, dataPtr + dataOffest, ofxUboSingeltons::matrixRowSize[uniform.type]);
                dataOffest+=ofxUboSingeltons::matrixRowSize[uniform.type];
                rowOffset+=uniform.matrixStride;
            }
        }else if (uniform.arrayStride >0 && uniform.matrixStride == 0){// is it a regular array
            int offset = uniform.offest;
            int arrayCount = uniform.size/uniform.arrayStride;
            for (int j = 0; j < arrayCount; j++) {
                memcpy(buffer.data() + offset, dataPtr + dataOffest, ofxUboSingeltons::spGLSLTypeSize[uniform.type]);
                dataOffest+=ofxUboSingeltons::spGLSLTypeSize[uniform.type];
                offset+=uniform.arrayStride;
            }
        }else if (uniform.arrayStride == 0 && uniform.matrixStride == 0){// is it a regular type
            int offset = uniform.offest;
            memcpy(buffer.data() + offset, dataPtr + dataOffest, ofxUboSingeltons::spGLSLTypeSize[uniform.type]);
            dataOffest+= ofxUboSingeltons::spGLSLTypeSize[uniform.type];
        }
    }
    glBindBuffer(GL_UNIFORM_BUFFER,uboId);
    glBufferSubData(GL_UNIFORM_BUFFER,0,bufferLayout.size,buffer.data());
}
//--------------------------------------------------------------

template <class T>
void ofxUbo<T>::loadDataManually(const T &newData){
    glBindBuffer(GL_UNIFORM_BUFFER,uboId);
    glBufferSubData(GL_UNIFORM_BUFFER,0,bufferLayout.size,(char*)(&newData));
}

//--------------------------------------------------------------

// subclass of ofShader
// allows one to send data from openframeworks to GLSL uniform blocks
class ofxUboShader:public ofShader{
public:
    ofxUboShader();
    ~ofxUboShader();
    ofxUboShader(const ofxUboShader& mom);
    ofxUboShader & operator=(const ofxUboShader& mom);
    
    // you can call this if you want but it is not necessary because
    // a ubo will be allocated on the first call to setUniformBuffer
    template <class T>
    bool allocateUbo(const string &blockName);
    
    // uploads data to the specified uniform block.
    template <class T>
    void setUniformBuffer(const string &blockName, const T &data, bool manualPadding = false);
    
    // prints the layout of the specified uniform block to the console. Useful for manual padding
    // should be marked const,will be fixed in 8.1
    void printLayout(const string &blockname);
    
private:
    // retrives the layout for the specified block
    // should be marked const will be fixed in 8.1
    ofxUboLayout getLayout(const string &blockName);
    
    // binds block to specified location
    void bindToLocation(const string& blockName, GLuint location);
    
private:
    // each uniform block gets its own ubo, the shader keeps track of them;
    // maps a blockName to a shared pointer to ofxUbo.
    map<string,shared_ptr<ofxUboBase> > ubos;
    
};

//-------------------------------------------------------------

template <class T>
void ofxUboShader::setUniformBuffer(const string &blockName, const T &data, bool manualPadding){
    if (ubos.find(blockName) != ubos.end()) {
        shared_ptr<ofxUbo<T> > uboRef = dynamic_pointer_cast<ofxUbo<T> >(ubos[blockName]);
        manualPadding ? uboRef->loadDataManually(data):uboRef->loadData(data);
    }else{
        if(allocateUbo<T>(blockName)){
            shared_ptr<ofxUbo<T> > uboRef = dynamic_pointer_cast<ofxUbo<T> >(ubos[blockName]);
            manualPadding ? uboRef->loadDataManually(data):uboRef->loadData(data);
        }
    }
}

//-------------------------------------------------------------

template <class T>
bool ofxUboShader::allocateUbo(const string &blockName){
    ofxUboLayout layout = getLayout(blockName);
    if (layout.blockName == "") {
        return false;
    }
    shared_ptr<ofxUboBase > uboRef(new ofxUbo<T>(layout));
    ubos[blockName] = uboRef;
    bindToLocation(blockName, uboRef->getBindingPoint());
    
}





