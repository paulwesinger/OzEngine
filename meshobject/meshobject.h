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

#include "../defines.h"
#include <string>
#include <list>

class CMeshObject{
public:
    CMeshObject();
    CMeshObject(std::string filename);
    ~CMeshObject();

    bool Load3DS(std::string filenmame);
    int faceCount();
    std::string Objectname();


private:
    int _FaceCount;
    int _Vertexcount;
    std::string _Filename;
    std::string _Objectname;

    std::list<TEXTURECOORDS> texCoords;
    std::list<VECTOR> vecs;
    std::list<FACE> faces;

    std::_List_iterator<TEXTURECOORDS> * textureIter;
    std::_List_iterator<VECTOR3D> * vecIter;
    std::_List_iterator<FACE> * faceIter;

    long filelength(int f);
};

#endif // CMESHOBJECT_H
