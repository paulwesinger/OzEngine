
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

LandScape::LandScape()
    :BaseObject() {
    _RasterX = TERRAIN::RASTER_X;
    _RasterZ = TERRAIN::RASTER_Z;
    _PatchX = TERRAIN::PATCH_X;
    _PatchZ = TERRAIN::PATCH_Z;
}
LandScape::LandScape(float rasterx, float rastery)
    : BaseObject() {
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = TERRAIN::PATCH_X;
    _PatchZ = TERRAIN::PATCH_Z;
}

LandScape::LandScape(int patchx, int patchy, float rasterx, float rastery)
    :BaseObject(){
    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = patchx;
    _PatchZ = patchy;
}

LandScape::LandScape(int patchx, int patchy, float rasterx, float rastery, vec3 color)
    :BaseObject(BASE::ZERO_VEC3,BASE::ZERO_VEC3,BASE::ZERO_VEC3, glm::vec4(color,1.0)){

    _RasterX = rasterx;
    _RasterZ = rastery;

    _PatchX = patchx;
    _PatchZ = patchy;
}

LandScape::~LandScape(){
    glDeleteVertexArrays(1, &_Vao);
    glDeleteBuffers(1, &_Vbo);
    glDeleteBuffers(1, &_Ebo);
    glDeleteProgram(perspectiveColorShader);
    glDeleteProgram(perspectiveTextureShader);
}

void LandScape::setPatchX(int px) { _PatchX = px; }
void LandScape::setPatchZ(int pz) { _PatchZ = pz; }
void LandScape::setRasterZ(float rz) { _RasterZ = rz; }
void LandScape::setRasterX(float rx) { _RasterX = rx; }

void LandScape::Draw(Camera *cam) {

    glUseProgram( currentShader);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    // Locate uniforms in shader
    mv_location = glGetUniformLocation(currentShader, "mv_matrix");
    int projectionloc = glGetUniformLocation(currentShader,"projection");
    int viewloc = glGetUniformLocation(currentShader,"view");


    // Model  Lightning
    int modellocation = glGetUniformLocation(currentShader,"model");
    int lightlocation = glGetUniformLocation(currentShader,"lightpos");
    int lightcolorlocation = glGetUniformLocation(currentShader,"lightcolor");


    glUniform4f(color_location,_Color.r,_Color.g, _Color.b, _Color.a);
    //Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model= glm::mat4(1.0f);

    if (  GetFirstTranslate() ) {

        Model = glm::translate(Model,GetTranslate());
        //printf ( "Cube::Draw glm::translate :  %f, %f ,%f \n",GetTranslate().x,GetTranslate().y,GetTranslate().z);
        Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));
    }
    else {
        Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));

        Model = glm::translate(Model,GetTranslate());
    }

      // -----------------------------------------
    // Lightning
    // -----------------------------------------
    glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(Model));

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


    glFrontFace(GL_CCW);
   // glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
   //glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));
   //   glm::mat4 mvp = GetProjection() * cam->GetView() * Model;




    glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
    glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_Textures[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _Textures[0]);


    glPointSize(8.0);
    glBindVertexArray(_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_Ebo);

    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, nullptr);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);



}

void LandScape::setUp() {

    float y = -10.0f;
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


    logwarn("Size _PatchX : "+ IntToString(_PatchX),"Landscape:: setUP");
    logwarn("Size _PatchZ : "+ IntToString(_PatchZ),"Landscape:: setUP");
    logwarn("Size _RasterX : "+ IntToString(_RasterX),"Landscape:: setUP");
    logwarn("Size _RasterZ : "+ IntToString(_RasterZ),"Landscape:: setUP");



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
            // Color  (Normals)
            // -------------------------------------------------------
            vt.color.r = 0.0f;
            vt.color.g = 1.0f;
            vt.color.b = 0.0f;

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

    _CountTextures = 0;
    setUp();

    loginfo("size of Landscape " + IntToString(_PatchX) + " x "+ IntToString(_PatchZ) ,"Landscape::init");
    loginfo("size of List " + IntToString(vertsTex.size()) ,"Landscape::init");


    for (int i = 0; i < 900; i++) {
        logimage("_VBO.x [" + IntToString(i) + "]  " + FloatToString(vertsTex[i].vector.x) );
        logimage("_VBO.y [" + IntToString(i) + "]  " + FloatToString(vertsTex[i].vector.y) );
        logimage("_VBO.y [" + IntToString(i) + "]  " + FloatToString(vertsTex[i].vector.z) );
        logEmptyLine();
    }


    glGenVertexArrays(1,&_Vao);
    // Vertex Buffer
    glGenBuffers(1,&_Vbo);
    glGenBuffers(1,&_Ebo);

    glBindVertexArray(_Vao);

    glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertsTex.size() * sizeof(sVertexTexture),
                 &vertsTex[0],
                 GL_DYNAMIC_DRAW);



    // Vertex
    glVertexAttribPointer(0,3,GL_FLOAT, GL_TRUE, 8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //Color
    glVertexAttribPointer(1,3,GL_FLOAT, GL_TRUE, 8*sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture
    glVertexAttribPointer(2,2,GL_FLOAT,GL_TRUE,8 * sizeof(float), (void*)(6 *sizeof(float)));
    glEnableVertexAttribArray(2);

    // -----------------------------------------
    // generate indices
    //------------------------------------------
    // -------------------------------------
    // Sphere body
    //--------------------------------------
    GLushort x = 0;
    GLushort patchx = static_cast<GLushort>(_PatchX) ;
    GLushort hlp = static_cast<GLushort>(_PatchZ);

    ushort i, j;

    for (j = 0; j < _PatchX-1; j++) {  // -3

        for (i= 0; i < hlp-1; i++){
            indices.push_back(i +  x);
            indices.push_back(i+x+patchx);
        }

        x += patchx;
    }

    for (int i = 0; i < 900; i++) {
        logimage("_Ebo.x [" + IntToString(i) + "]  " + IntToString(indices[i]) );
        if ((i | 32) == 0)
            logEmptyLine();

    }


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(GLushort),
                 &indices[0],
                GL_DYNAMIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    loginfo("Sizeof Indicis " + IntToString(indices.size()) ,"Landscape::init");
    loginfo("Landscape ........ Done","Landscape::init");
}
