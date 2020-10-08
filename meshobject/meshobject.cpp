#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "meshobject.h"
#include "../logs/logs.h"
#include "../utils/utils.h"



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

            VECTOR crossproduct; // aus den 3 vektoren errrechnen
            meshFloats[index++] = v0.x;
            meshFloats[index++] = v0.y;
            meshFloats[index++] = v0.z;
            // Hier die normale einschleusen
            //.....
            //------
            meshFloats[index++] = t0.u;  // oder v ?
            meshFloats[index++] = t0.v;
           //-----------------------------------------
           // das ganze jetzt noch mit v1,v2, , function erstellen !!!

        }
    }
}

void CMeshObject::Draw(Camera *cam, GLuint shaderprog){

}



















