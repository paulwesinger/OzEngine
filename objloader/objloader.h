#ifndef COBJLOADER_H
#define COBJLOADER_H

#include <stdio.h>
#include <vector>
#include <string>

#include "../defines.h"
#include "glm/vec3.hpp"

enum {
    NO_ERROR = 0,
    NO_FILENAME,
    NO_VECDATA,
    NO_FACEDATA,
    NO_TEXTUREDATA,
    EMPTY_FILE,
    READ_ERROR
} OBJ_LOAD_ERRORS;

class COBJLoader
{
public:
    COBJLoader();
    COBJLoader(std::string filename);
    ~COBJLoader();

    void SetOBJFileName(std::string filename);
    int LoadOBJ();

    std::vector<TEXTURECOORDS>& TextureCoordinates();
    std::vector<VECTOR> & Vecs();
    std::vector<FACE> & Faces();
protected:
    std::vector<TEXTURECOORDS> texCoords;
    std::vector<VECTOR> vecs;
    std::vector<FACE> faces;

private:
    std::string _FileName;
};

#endif // COBJLOADER_H
