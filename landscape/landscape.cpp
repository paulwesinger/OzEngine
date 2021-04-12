
#include <GL/glew.h>
//#include <GL/gl.h>


#include "landscape.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../imageloader/loadimage.h"
#include "../vecmath/vecmath.h"
#include "../defaults.h"

LandScape::LandScape(){
    _RasterX = TERRAIN::RASTER_X;
    _RasterZ = TERRAIN::RASTER_Z;
    _PatchX = TERRAIN::PATCH_X;
    _PatchZ = TERRAIN::PATCH_Z;

    init();
}
LandScape::LandScape(float rasterx, float rastery){
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = TERRAIN::PATCH_X;
    _PatchZ = TERRAIN::PATCH_Z;

    init();
}

LandScape::LandScape(int patchx, int patchy, float rasterx, float rastery){
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = patchx;
    _PatchZ = patchy;

    init();
}

void LandScape::Draw(Camera *cam) {

}

void LandScape::setUp() {

    float y = 0.0f;
    sVertexTexture vt;
    sVertexColor vc;

    //------------------------------------------
    // erstmal ein paar setups für die geometrie
    // landscape im mittelpunkt definieren
    //------------------------------------------
    float sizeX = (static_cast<float>(_PatchX) * _RasterX) / 2 ;
    float sizeZ = (static_cast<float>(_PatchZ) * _RasterZ) / 2 ;

    float startX = -sizeX; //Linke seite negative
    float startZ = -sizeZ;

    float texU = 1.0f / _RasterX;
    float texV = 1.0f / _RasterZ;

    for (int j = 0; j < _PatchZ; j++ ) {
        for (int i = 0; i < _PatchX; i++) {

            // ------------------------------------------------------
            // Vektoren
            // ------------------------------------------------------
            vt.vector.x = startX +(static_cast<float>(i) * _RasterX);
            vt.vector.y = y ;   // hier generator für höhe einbauen
            vt.vector.z = startZ + (static_cast<float>(j) * _RasterZ);

            // daten für colorverts sind gleich
            vc.vector = vt.vector;

            // -------------------------------------------------------
            // Color
            // -------------------------------------------------------
            vt.color.r = 1.0f;
            vt.color.g = 1.0f;
            vt.color.b = 1.0f;

            vc.color = vt.color;

            //--------------------------------------------------------
            //Texture coordinaten - nur für texshader landscape
            //--------------------------------------------------------
            vt.tex.x = (static_cast<float>(i) * texU);
            vt.tex.y = (static_cast<float>(j) * texV);

            vertsTex.push_back(vt);
            vertsCol.push_back(vc);
        }
    }
}

void LandScape::init(){

    setUp();

    glGenVertexArrays(1,&_Vao);
    glBindVertexArray(_Vao);
    // Vertex Buffer
    glGenBuffers(1,&_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertsTex.size() * sizeof(sVertexTexture),
                 &vertsTex[0],
                 GL_DYNAMIC_DRAW);


    // Vertex
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //Color
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(float), (void*)(6 *sizeof(float)));
    glEnableVertexAttribArray(2);
}
