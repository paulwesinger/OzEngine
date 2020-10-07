#ifndef CCUBE_H
#define CCUBE_H

/*
 * File:   CCube.h
 * Author: paul
 *
 * Created on 27. Mai 2018, 11:17
 */

#include <cstdio>
#include <vector>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>

#include "../shaders/shader.h"
#include "../baseobject/baseobject.h"
#include "../camera/camera.h"
#include "../shaders/shader.h"
#include "../lights/light.h"




uint const  MAX_TEXTURES = 2;

using namespace glm;

class CCube : public BaseObject {
public:
    CCube();
    CCube(const CCube& orig,glm::mat4 pro);
    CCube(vec3 origin,glm::mat4 pro) ;
    CCube(vec3 origin , vec4 color, glm::mat4 pro);
    virtual ~CCube();
    virtual void Draw( Camera * cam, GLuint shaderprog);
    virtual void Calc(float roty,float trans_x); // Check for Arguments
    virtual void SetColor(vec4 color);

    void Init();
    //Diese Funktion wird nach dem initialsieren aufgerufen.
    // Liste > 1 Element == Multitextureing
    bool addTexture(std::vector<std::string> path,std::string obj);
    void setActiveShader(ShaderType t);
    void initShader(ShaderType s,GLuint prog);
    void addLight(light * l);

    // Fürs erste ersmal maximal 3    bool addTexture(std::string path);
private:

    GLuint       perspectiveTextureShader,perspectiveColorShader, lightshader, currentShader;
    int          orthoShader;
    GLuint       vao;


    GLuint          position_buffer;
    GLuint          index_buffer;
    GLint           mv_location;
    GLint           ortho_location;
    GLint           color_location; // Farbe im vertex Shader
    GLint           viewlocation;   // viewmatreix für orhomode
    int             vs ;
    int             fs;
    Shader *        shader;

    // Light
    light *  _Light;  // Liste ?

    // Transformations
    vec3           _Trans;
    vec3           _Rotate;
    vec3           _Scale;
    vec4           _Color;
    // flags  --> ins BaseObject ??
    bool left;
    // wenn alles mit liste läuft, ersetzen
   // unsigned int multitex[2];

    uint _CountTextures;  // die Anzehl = Listen länge
    GLuint  _Textures[5];
};


#endif // CCUBE_H
