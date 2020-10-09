// ---------------------------------------------------------
// description:
// This class loads a 3DS mesh without normals !!
// it give back a list with this stucture:
// vx vy vz  nx ny nz tx tz -> Vecs, normals, texturecoords
// Normals will be calced during reading the faces^1
// Additional:
// count faces
//---------------------------------------------------------

#ifndef CMESHOBJECT_H
#define CMESHOBJECT_H


#include <string>
#include <list>
#include <GL/gl.h>
//#include <GL/glew.h>
#include "../defines.h"
#include "../baseobject/baseobject.h"
#include "../3DLoader/load3ds.h"
#include "../camera/camera.h"

const int GL_DATA_SIZE = 8; // 3*Vector, 3 * NORMALE, 2* Texture
const int FACESIZE = 3;
const int FLOATS_PER_FACE = GL_DATA_SIZE * FACESIZE;  // Needed floats per face

class CMeshObject : public BaseObject{
public:
    CMeshObject();
    CMeshObject(std::string filename);

    ~CMeshObject();
    virtual void Draw( Camera * cam, GLuint shaderprog);
    bool Load3DSMesh(std::string filename);

private:
    void init();
    bool meshLoaded;
    void initMesh();

    void storeInArray(float* arrayvar, int & ind, VECTOR v, VECTOR n,TEXTURECOORDS t);


    C3DSLoad * load3DS;
    std::string _Filename;
};

#endif // CMESHOBJECT_H
