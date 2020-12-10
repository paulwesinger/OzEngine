#include "sphere.h"


/*
 * File:   CSphere.cpp
 * Author: paul
 *
 * Created on 27. Oktober 2019, 20:03
 */

//#include <glm/glm.hpp>
//#include <glm/detail/type_mat4x4.hpp>
//#include <glm/ext/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "sphere.h"
#include "../logs/logs.h"
#include "../utils/utils.h"
#include "../vecmath/vecmath.h"

using namespace glm;


static const GLchar * vs_source = {
"#version 440 core                              \n"
"layout (location=0) in vec3 vertex;            \n"
"layout (location=1) in vec3 color;             \n"
"layout (location=2) in vec2 tex;               \n"

"uniform mat4 mv;                               \n"
"out vec4 outcolor;                             \n"
"out vec2 texKoord;                             \n"

"void main(void) {                              \n"
"    float alpha = 1.0f;                         \n"
"    gl_Position = mv * vec4(vertex,1.0);       \n"
"    if (vertex.z < 0 ) {                       \n"
"       alpha = 0.3f;                           \n"
"    }                                          \n"
"    //vs_out.color = vec4(color,1.0);          \n"
"    outcolor = vec4(color,alpha);                \n"
"    texKoord = tex;                            \n"
"}"
};

static const GLchar * fs_source = {
"#version 440 core                              \n"

"in vec4 outcolor;                              \n"
"out vec4 fragcolor;                            \n"
"uniform vec4 changecolor;                      \n"

"void main(void) {                              \n"
"    fragcolor =  changecolor;                  \n"
"}                                              "
};
CSphere::CSphere() :
    BaseObject((vec3(0.0,0.0,0.0)),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
   _CountPoints = 36;
   _Radius = 20.0f;

   float radians = glm::radians(45.0f);
   float aspect = 4.0f / 3.0f;
   float near= 0.1f ;
   float far = 100.0f;
   glm::mat4 pro = perspective(radians,aspect,near,far); //Standard
   SetProjection(pro);
   setUp();
}

CSphere::CSphere( int points) :
        BaseObject((vec3(0.0,0.0,0.0)),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
   _CountPoints = points;
   _Radius      = 20.0f;
   float radians = glm::radians(45.0f);
   float aspect = 4.0f / 3.0f;
   float near= 0.1f ;
   float far = 100.0f;
   glm::mat4 pro = perspective(radians,aspect,near,far); //Standard
   SetProjection(pro);
   setUp();
}
CSphere::CSphere( int points, GLfloat rad)
        : BaseObject((vec3(0.0,0.0,0.0)),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec4(0.5,0.2,0.6,1.0)) {
   _CountPoints = points;
   _Radius      = rad;
   float radians = glm::radians(45.0f);
   float aspect = 4.0f / 3.0f;
   float near= 0.1f ;
   float far = 100.0f;
   glm::mat4 pro = perspective(radians,aspect,near,far); //Standard
   SetProjection(pro);
   setUp();
}

CSphere::CSphere(const CSphere& orig) {
}

CSphere::CSphere(vec3 origin, glm::mat4 pro)
    : BaseObject(origin,origin,origin,vec4(0.5,0.2,0.6,1.0))
{
    _CountPoints = 36;
    _Radius      = 20.0f;
    SetProjection( pro);
    setUp();
}
CSphere::CSphere(vec3 origin, glm::mat4 pro, int points)
    : BaseObject(origin,origin,origin,vec4(0.5,0.2,0.6,1.0))
{
    _CountPoints = points;
    _Radius      = 20.0f;
    SetProjection( pro);
    setUp();
}
CSphere::CSphere(vec3 origin, glm::mat4 pro, int points, GLfloat rad, Shader * shad)
    : BaseObject(origin,origin,origin,vec4(0.5,0.2,0.6,1.0))
{
    shader = shad;
    _CountPoints = points;
    _Radius      = rad;
    SetProjection( pro);
    setUp();
}

CSphere::CSphere(vec3 origin, vec4 color, glm::mat4 pro)
    : BaseObject(origin,origin,origin,color) {
    _Radius      = 20.0f;
    _CountPoints = 36;
    SetProjection(pro);
    setUp();
}
CSphere::CSphere(vec3 origin, vec4 color, glm::mat4 pro ,int points)
    : BaseObject(origin,origin,origin,color) {
    _Radius      = 20.0f;
    _CountPoints = points;
    SetProjection(pro);
    setUp();
}
CSphere::CSphere(vec3 origin, vec4 color, glm::mat4 pro ,int points,GLfloat rad,Shader * shad)
    : BaseObject(origin,origin,origin,color) {
    shader = shad;
    _Radius      = rad;
    _CountPoints = points;
    SetProjection(pro);
    setUp();
}

CSphere::~CSphere() {
    glDeleteVertexArrays(1, &_Vao);
    glDeleteBuffers(1, &_VertexBuffer);
    //glDeleteBuffers(1, &index_buffer);
    glDeleteProgram(shaderprogram);
}

void CSphere::SetColor(vec4 color) {
    _color = color; // in Baseobject
}
//virtuale MEthoden
void CSphere::Draw(Camera* cam ){//, GLuint &shaderprog) {

    glUseProgram(shaderprogram);
    mv_location     = glGetUniformLocation(shaderprogram,"mv");
    color_location  = glGetUniformLocation(shaderprogram,"changecolor");

   // mv_location     = glGetUniformLocation(shaderprog,"mv_matrix");
   // color_location  = glGetUniformLocation(shaderprog,"trianglecolor");

    glUniform4f(color_location,GetColor().r,GetColor().g,GetColor().b,GetColor().a);

    glm::mat4 Model(1);

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

    glm::mat4 mvp = GetProjection() * cam->GetView() * Model;
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);

    // Alle indices binden:
    // Nordpol
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Ebo_npol);
    glDrawElements( GL_TRIANGLE_FAN, _CountPoints * 2 + 2 , GL_UNSIGNED_SHORT, 0);

    // Südpol
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Ebo_spol);
    glDrawElements( GL_TRIANGLE_FAN, _CountPoints * 2 + 2 , GL_UNSIGNED_SHORT, 0);

    // Body

    glUniform4f(color_location,1.0,0.0,GetColor().b,0.3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_BodyPoints);
    glDrawElements(GL_TRIANGLE_STRIP,body.size(),GL_UNSIGNED_SHORT,0);


    glPointSize(8.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
    glDrawArrays(GL_POINTS, 0 , countVertex);

    glUniform4f(color_location,1.0,0.0,GetColor().b,GetColor().a);

    glPointSize(16.0f);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
    glDrawArrays(GL_POINTS, 0 , 4);

    glUniform4f(color_location,1.0,0.0,0.0,GetColor().a);
    glDrawArrays(GL_POINTS, 25 , 2);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

// ===============================================
// Protected Functions
//================================================

// Adds adds the values to the given array ind couznts up index
void CSphere::Add2GPU(float* v, int &index, GLfloat vx, GLfloat vy, GLfloat vz) {
    v[index]    = vx;
    v[index+1]  = vy;
    v[index+2]  = vz;
    index +=3;
}

// Overloaded:
void CSphere::Add2GPU(float* v, int &index, glm::vec3 vec) {
    v[index]    = vec.x;
    v[index+1]  = vec.y;
    v[index+2]  = vec.z;
    index +=3;
}

void CSphere::Add2GPU(float* v, int &index, glm::vec2 vec) {
    v[index]    = vec.x;
    v[index+1]  = vec.y;
    index +=2;
}



void CSphere::calc(GLfloat * v) {

// Erstmal NordPol festlegen
glm::vec3 npol = glm::vec3(0.0,_Radius ,0.0);
float winkel_laenge = 180.0f / (_CountPoints -1 ) ;
float winkel_breite = 360.0f / (_CountPoints * 2) ;
float laengenwinkel = 90.0f - winkel_laenge;
float breitenwinkel = winkel_breite;
// Nordpol ins array für vertexbuffer eintragen
// Vertex
int index = 0;
Add2GPU(v,index, npol);
Add2GPU(v,index, GetColor().x, GetColor().y, GetColor().z);
// Dummy für Texture
Add2GPU(v,index, glm::vec2(1.0,1.0));

countVertex = 1;
// Erstmal eine 2D-Sehne für den Längengrad erstellen und in ein array eintragen
// Entspricht x und y koordinate
glm::vec2 laengensehne[_CountPoints-1];  //
glm::vec2 breitensehne[_CountPoints*2];  //

//glm::vec2 laengensehne[_CountPoints];  //
//glm::vec2 breitensehne[_CountPoints*2];  // *2+1


//laengensehne[0].x = 0.0;
//laengensehne[0].y = _Radius;

glm::vec3 laengengrad;
glm::vec3 breitengrad;

for (int i = 0; i < _CountPoints - 2; i++) {
    calccircle(_Radius, laengenwinkel, laengensehne[i]);
    laengenwinkel -= winkel_laenge;
    if ( laengenwinkel < 0.0f )
        laengenwinkel += 360.0f;

    laengengrad.x = laengensehne[i].x;
    laengengrad.y = laengensehne[i].y;
    laengengrad.z = 0.0;

    Add2GPU(v, index, laengengrad);
    Add2GPU(v, index, GetColor().x, GetColor().y, GetColor().z);
    Add2GPU(v,index,glm::vec2(1.0,1.0));

    countVertex ++;
   // ========================================================
   // Jetzt den Breitengrad für jeden längengrad punkt rechnen
   // diesmal CountPoints * 2
   //---------------------------------------------------------
   for (int j = 0; j < _CountPoints * 2 - 1; j++) {
        // sehne  :
        calccircle(laengengrad.x,breitenwinkel,breitensehne[j]);
        breitenwinkel += winkel_breite;

        // Man könnte das ganze auch gleich direkt in das array fürden GPU Mem schreiben
        // .. ist aber so leichter zu lesen
        breitengrad.x = breitensehne[j].x;
        breitengrad.y = laengengrad.y;
        breitengrad.z = breitensehne[j].y;

        Add2GPU(v, index, breitengrad);
        Add2GPU(v, index, GetColor().x, GetColor().y, GetColor().z);
        Add2GPU(v, index, glm::vec2(1.0,1.0));

        countVertex ++;
   }

   breitenwinkel = winkel_breite;
}

    Add2GPU(v,index,0.0, -(_Radius),0.0);  // "Südpol"
    Add2GPU(v, index, GetColor().x, GetColor().y, GetColor().z);
    Add2GPU(v, index, glm::vec2(1.0,1.0));
    countVertex++;
}
void CSphere::setUp() {

    int vs,fs;

    vs = shader->compileVertexShader(vs_source);
    fs = shader->compileFragmentShader(fs_source);
    shaderprogram = shader->CreateProgram(vs,fs);


    //            Nordpol und südpol abziehen          letzer breitegrad = 1. breiten grad , + nord und südpol
    int countverts =         ((_CountPoints - 2)         *      (_CountPoints * 2 ))  + 2 ;

    int count = countverts * 8;   // pro vertex 3 float vektor, 3float color, 2 float textur
    GLfloat verts[count];

    calc(verts);

    glGenVertexArrays(1,&_Vao);
    glBindVertexArray(_Vao);
    // Vertex Buffer
    glGenBuffers(1,&_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(verts),
                verts,
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

    //-------------------------------------------
    // Element buffer  --> NordPol - Triangle Fan
    //-------------------------------------------
    GLushort npol_indices[_CountPoints * 2 + 2];

    for (GLushort i = 0; i < _CountPoints * 2 + 1; i++)
        npol_indices[i] = i;
    npol_indices[_CountPoints * 2 + 1] = 1;
    // und in den buffer...
    glGenBuffers(1,&_Ebo_npol);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_Ebo_npol);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  sizeof (npol_indices),
                  npol_indices,
                  GL_DYNAMIC_DRAW);

    //-------------------------------------------
    // Element buffer südpol  zum aufwärmen:
    //-------------------------------------------
    GLushort spol_indices[_CountPoints * 2 + 2];
    spol_indices[0] = countVertex-1;

    for (GLushort i = 1; i < _CountPoints * 2 +2; i++)
        spol_indices[i] = countVertex - i;

    spol_indices[_CountPoints * 2 + 1] = countVertex - 2;
    // ab in den Buffer..
    glGenBuffers(1,&_Ebo_spol);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_Ebo_spol);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                  sizeof (spol_indices),
                  spol_indices,
                  GL_DYNAMIC_DRAW);


    // -------------------------------------
    // Sphere body
    //--------------------------------------
/*
    body.push_back(25);
    body.push_back(49);
    body.push_back(26);
    body.push_back(50);
    body.push_back(27);
    body.push_back(51);
    body.push_back(28);
    body.push_back(52);
  */

    int hlp = _CountPoints * 2;
    int step = hlp;
    //-----------------------------------------
    // "Testkranz"
    //-----------------------------------------
    for (int i= 0; i< hlp; i++ ) {
        body.push_back(i+step + 1);
        body.push_back(i + step*2 +1);
    }
    // anschliessen an die erstenbeiden
    body.push_back(step+1);
    body.push_back(step*2 +1);
    //------------------------------------------

    glGenBuffers(1,&_BodyPoints);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_BodyPoints);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        body.size() * sizeof(GLushort),
                        &body[0],
                        GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesEBO.size() * sizeof(<data type>), &m_indicesEBO[0], GL_STATIC_DRAW);



    // Alles reseten
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);


}
