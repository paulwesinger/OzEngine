#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

/*
 * This class holds the positon , translation and scale
 * for ech object
 * every object shouldbe derrived from this object !
 */
using namespace glm;

class BaseObject {
public:
    BaseObject();
    BaseObject(const BaseObject& orig);
    BaseObject(vec3 pos,vec3 rotate,vec3 scale,vec4 col );
    virtual ~BaseObject();
    // transormations
    virtual vec3 GetTranslate();
    virtual vec3 GetRotate();
    virtual vec3 GetScale();

    virtual vec4 GetColor();


    virtual void Translate(vec3 trans);
    virtual void Rotate(vec3 rotate);  // ACHTUN : Hält nur den aktuell zu drehenden
                                //Winkel für jede Achse
    virtual void Scale(vec3 scale);

    virtual void SetColor(vec4 col);
    virtual void StepTranslate(vec3 step);
    virtual void StepRotate(vec3 step);
    virtual void StepScale(vec3 step);

    // Flags
    void SetFirstTranslate(bool ok);
    bool GetFirstTranslate();
    bool HasTextures();
    void SetHasTextures(bool hasATexture);

    void SetProjection(glm::mat4 pro,bool orthomode = false);
    glm::mat4 & GetProjection();


protected:
    // This vectors holds the current translation,rotation,scale
    vec3 _rotate;
    vec3 _translate;
    vec3 _scale;
    //Steps for animations,will be added to the vecors _rotate,
    //_translate,_scale
    vec3 _trans_step;
    vec3 _rotate_step;
    vec3 _scale_step;

    vec4 _color; // inkl. Alpha
    bool _FirstTranslate;  // Flag ,ob erst veschoben oder rotiert werden soll

    glm::mat4 _Projection;
    bool _IsOrtho;
    bool _HasTextures;


};


#endif // BASEOBJECT_H
