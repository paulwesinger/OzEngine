
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "meshobject.h"
#include "../logs/logs.h"
#include "../utils/utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static const GLushort vertex_indices[] =
{
    0, 1, 2,
    2, 1, 3,
    2, 3, 4,
    4, 3, 5,
    4, 5, 6,
    6, 5, 7,
    6, 7, 0,
    0, 7, 1,
    6, 0, 2,
    2, 4, 6,
    7, 5, 3,
    7, 3, 1
};

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
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1, &vao);
}

void CMeshObject::init() {
    load3DS = new C3DSLoad();
    _Filename = "";
    meshLoaded = false;

    _CountTextures = 0;
    _Color = vec4(1.0f,1.0f,1.0f,1.0f);
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
        arraySize = FLOATS_PER_FACE * facecount;
        indexSize = facecount * 3 ;

        std::vector<VECTOR> vecs = load3DS->Vecs();
        std::vector<FACE> faces = load3DS->Faces();
        std::vector<TEXTURECOORDS> textures = load3DS->TextureCoordinates();

        meshFloats =  new float[arraySize];
        meshIndexes = new GLuint[indexSize];

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

            storeInVertexArray(meshFloats, index, v0, norm, t0 );
            storeInVertexArray(meshFloats, index, v1, norm, t1);
            storeInVertexArray(meshFloats, index, v2, norm, t2);
        }


        loginfo("meshfloat " + FloatToString( meshFloats[0]) );
        loginfo("meshfloat " + FloatToString( meshFloats[1]) );
        loginfo("meshfloat " + FloatToString( meshFloats[2]) );
        loginfo("meshfloat " + FloatToString( meshFloats[3]) );
        loginfo("meshfloat " + FloatToString( meshFloats[4]) );
        loginfo("meshfloat " + FloatToString( meshFloats[5]) );
        loginfo("meshfloat " + FloatToString( meshFloats[6]) );
        loginfo("meshfloat " + FloatToString( meshFloats[7]) );
        loginfo("meshfloat " + FloatToString( meshFloats[8]) );
//        loginfo("meshfloat " + FloatToString( meshFloats[9]) );

        // Element Buffer initialisieren
        loginfo("index " + IntToString( index) );
        loginfo("arraysize " + IntToString( arraySize) );
        loginfo("sizeof meshFloats " + IntToString( sizeof(arraySize)) );

        loginfo("sizeof indexes_const " + IntToString( sizeof(vertex_indices)) );

        index =0;
        for (int i= 0; i< facecount; i++){
            meshIndexes[index++] = faces[i].p0;
            meshIndexes[index++] = faces[i].p1;
            meshIndexes[index++] = faces[i].p2;
        }

        loginfo("meshIndex " + IntToString( meshIndexes[0]) );
        loginfo("meshIndex " + IntToString( meshIndexes[1]) );
        loginfo("meshIndex " + IntToString( meshIndexes[2]) );
        loginfo("meshIndex " + IntToString( meshIndexes[3]) );
        loginfo("meshIndex " + IntToString( meshIndexes[4]) );
        loginfo("meshIndex " + IntToString( meshIndexes[5]) );
        loginfo("meshIndex " + IntToString( meshIndexes[6]) );

        // ----------------------------------------
        // Vertex Array
        // ----------------------------------------

        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);

        // ----------------------------------------
        // Vertex Array , Vertex
        // ----------------------------------------

        glCreateBuffers(1, &vbo);
        glNamedBufferStorage(vbo, arraySize * sizeof(float), NULL, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);

        loginfo("meshBuffer  bind   ");

        void * ptr = glMapNamedBuffer(vbo,GL_WRITE_ONLY);
        memcpy(ptr,meshFloats, arraySize * sizeof(float));
        glUnmapNamedBuffer(GL_ARRAY_BUFFER);

        loginfo("meshBuffer erstellt ");

        // ----------------------------------------
        // Element buffer
        // ----------------------------------------
        glCreateBuffers(1,&ebo);
        glNamedBufferStorage(ebo,indexSize * sizeof(GLshort),NULL,GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

        void * indexptr = glMapNamedBuffer(ebo,GL_WRITE_ONLY);
        memcpy(indexptr,meshIndexes,indexSize * sizeof(GLshort));
        glUnmapNamedBuffer(GL_ELEMENT_ARRAY_BUFFER);

        loginfo("IndexBuffer erstellt ");

/*
        glGenBuffers(GL_ARRAY_BUFFER,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);


        glBufferData(GL_ARRAY_BUFFER,
                     arraySize * sizeof(GLfloat) ,
                     meshFloats,
                     GL_STATIC_DRAW);
*/
/*

        // -----------------------------------------
        // Index buffer
        // -----------------------------------------
        glGenBuffers(GL_ELEMENT_ARRAY_BUFFER,&ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     facecount * 3 * sizeof(int),
                     meshIndexes,
                     GL_STATIC_DRAW);
*/
        //------------------------------------------
        // VertexAttribute Ptr
        //------------------------------------------
        // Vectors
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, STRIDE, (void *)0);
        glEnableVertexAttribArray(0);
        //Normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, STRIDE, (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //Textures
        glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, STRIDE, (void*) (6* sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER,0);

        loginfo("meshObject::Init Done ");
    }
}

void CMeshObject::storeInVertexArray(float *arrayvar, int &ind, VECTOR v, VECTOR n, TEXTURECOORDS t) {
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

    glUseProgram( shaderprog);
   // glEnable(GL_CULL_FACE);
   // glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);


    // Locate uniforms in shader
    mv_location = glGetUniformLocation(currentShader, "mv_matrix");
    int projectionloc = glGetUniformLocation(currentShader,"projection");
    int viewloc = glGetUniformLocation(currentShader,"view");

    color_location = glGetUniformLocation(currentShader,"triangleColor");
    ortho_location = glGetUniformLocation(currentShader,"orthomatrix");

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
    if (_IsOrtho) {
        glm::mat4 view = glm::lookAt(vec3(0.0f,0.0f,0.1f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp =  GetProjection() * view * Model;
        glUniformMatrix4fv(ortho_location, 1, GL_FALSE, glm::value_ptr(mvp));
    }
    else {
       glm::mat4 mvp =  GetProjection() * cam ->GetView() *  Model;
       glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mvp));
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


    glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
    glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_Textures[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _Textures[0]);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glDrawElements( GL_TRIANGLES, sizeof(indexSize), GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);

}



















