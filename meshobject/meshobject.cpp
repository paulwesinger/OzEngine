#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "meshobject.h"
#include "../logs/logs.h"
#include "../utils/utils.h"
#include <glm/glm.hpp>



CMeshObject::CMeshObject()
    :BaseObject(){
    init();
}
CMeshObject::CMeshObject(std::string filename)
    :BaseObject() {
    init();
}

CMeshObject::~CMeshObject() {
    delete  load3DS;
}

void CMeshObject::init() {
    load3DS = new C3DSLoad();
    _Filename = "";
    meshLoaded = false;
}

bool CMeshObject::Load3DSMesh(std::string filename) {

    _Filename = filename;
    meshLoaded = load3DS->Load3DS(filename);
    initMesh();
    return meshLoaded;
}

void CMeshObject::initMesh(){
    if (meshLoaded) {
        //----------------------------------------------------------
        // Alle listen (Texture,faces, vektoren) vom 3DSLoader holen
        // ein array mit der Grösse countfaces * 3 * 8 deklarieren
        // mesh einlesen:
        // face liste durchlaufen
        // vektoren pro face holen in mesh eintragen,
        // normale berechnen (gilt für alle 3 vektoren)
        // und eintragen in mesh
        // korrespondierende texturecoords mit vertexnummer
        // in die mesh eintragen(u,v) -> 8 floats * 3 = 1 polygon
        //----------------------------------------------------------
        int veccount = load3DS->VertexCount();
        int facecount = load3DS->FaceCount();
        int texturecount = load3DS->TextureCount();
        int arraySize = FLOATS_PER_FACE * facecount;

        std::vector<VECTOR> vecs = load3DS->Vecs();
        std::vector<FACE> faces = load3DS->Faces();
        std::vector<TEXTURECOORDS> textures = load3DS->TextureCoordinates();

        float meshFloats[arraySize];
        int index = 0;  // indexvariable für meshfloats

        for (int i=0; i<facecount; i++){
            // indexes für facevektoren
            int p0 = faces[i].p0;
            int p1 = faces[i].p1;
            int p2 = faces[i].p2;
            // die vektoren pro face
            VECTOR v0 = vecs.at(p0);
            VECTOR v1 = vecs.at(p1);
            VECTOR v2 = vecs.at(p2);
            // Texture koordinaten der vektoren
            TEXTURECOORDS t0 = textures.at(p0);
            TEXTURECOORDS t1 = textures.at(p1);
            TEXTURECOORDS t2 = textures.at(p2);


            glm::vec3 d1,d2;
            d1.x = v0.x; d1.y = v0.y; d1.z = v0.z;
            d2.x = v1.x; d2.y = v1.y; d2.z = v1.z;

            glm::vec3 crossproduct = glm::cross(glm::normalize(d1),glm::normalize(d2));
            //crossproduct
            VECTOR norm;
            norm.x = crossproduct.x; norm.y = crossproduct.y; norm.z = crossproduct.z;


            storeInArray(meshFloats, index,v0, norm, t0 );
            /*
            meshFloats[index++] = v0.x;
            meshFloats[index++] = v0.y;
            meshFloats[index++] = v0.z;
            // Hier die normale einschleusen
            //.....
            //------
            meshFloats[index++] = t0.u;  // oder v ?
            meshFloats[index++] = t0.v;

            */
           //-----------------------------------------
           // das ganze jetzt noch mit v1,v2, , function erstellen !!!

        }
        logwarn("index: " + IntToString(index));
    }
}

void CMeshObject::storeInArray(float *arrayvar, int &ind, VECTOR v, VECTOR n, TEXTURECOORDS t) {
    arrayvar[ind++] = v.x;
    arrayvar[ind++] = v.y;
    arrayvar[ind++] = v.z;

    // NormVektor
    arrayvar[ind++] = n.x;
    arrayvar[ind++] = n.y;
    arrayvar[ind++] = n.z;

    // Textures
    arrayvar[ind++] = t.u;  // oder v ?
    arrayvar[ind++] = t.v;

}
void CMeshObject::Draw(Camera *cam, GLuint shaderprog){

}



















