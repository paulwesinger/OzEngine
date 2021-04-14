
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

    //init();
}
LandScape::LandScape(float rasterx, float rastery)
    : BaseObject() {
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = TERRAIN::PATCH_X;
    _PatchZ = TERRAIN::PATCH_Z;

    //init();
}

LandScape::LandScape(int patchx, int patchy, float rasterx, float rastery)
    :BaseObject(){
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = patchx;
    _PatchZ = patchy;

    //init();
}

LandScape::LandScape(int patchx, int patchy, float rasterx, float rastery, vec3 color)
    :BaseObject(BASE::ZERO_VEC3,BASE::ZERO_VEC3,BASE::ZERO_VEC3, glm::vec4(color,1.0)){

    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = patchx;
    _PatchZ = patchy;

    //init();
}

void LandScape::setPatchX(int px) { _PatchX = px; }
void LandScape::setPatchZ(int pz) { _PatchZ = pz; }
void LandScape::setRasterZ(float rz) { _RasterZ = rz; }
void LandScape::setRasterX(float rx) { _RasterX = rx; }

void LandScape::Draw(Camera *cam) {



    int modellocation = glGetUniformLocation(currentShader,"model");
    int lightlocation = glGetUniformLocation(currentShader,"lightpos");
    int lightcolorlocation = glGetUniformLocation(currentShader,"lightcolor");

    if ( _Light != nullptr) {
        glm::vec3 c =   _Light->getColor();
        glm::vec3 p =   _Light->getPos();
        glUniform3f(lightlocation,p.x,p.y,p.z);
        glUniform3f(lightcolorlocation,c.x,c.y,c.z);
    }
    else {
        glm::vec3 lightpos = vec3(-10.0,2.0,-5.0);
        glm::vec3 lightcolor = glm::vec3( 0.0,1.0,0.0);
        glUniform3f(lightlocation,lightpos.x,lightpos.y,lightpos.z);
        glUniform3f(lightcolorlocation,lightcolor.x,lightcolor.y,lightcolor.z);
    }
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

    loginfo("Create Landscape","Landscape::init");
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
    loginfo("Landscape ........ Done","Landscape::init");
}
