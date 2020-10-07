#include "baseobject.h"


/*
 * File:   baseobject.cpp
 * Author: paul
 *
 * Created on 11. August 2018, 16:31
 */

#include "baseobject.h"

BaseObject::BaseObject() {
    vec3 v = vec3(0.0,0.0,0.0);
    Translate(v);
    Scale(v);
    Rotate(v);
    SetColor(vec4(v,1.0));
    _IsOrtho = false;
    _FirstTranslate = true;
    _HasTextures = false;
}

BaseObject::BaseObject(const BaseObject& orig) {

}

BaseObject::BaseObject(vec3 pos,vec3 rotate,vec3 scale , vec4 col) {
    Translate(pos);
    Rotate(rotate);
    Scale(scale);
    SetColor(col);

    _IsOrtho = false;
    _FirstTranslate = true;
    _HasTextures = false;
}

BaseObject::~BaseObject() {
}



 // Transormatioons

 vec3 BaseObject::GetRotate()       { return _rotate; }
 vec3 BaseObject::GetScale()        { return _scale ; }
 vec3 BaseObject::GetTranslate ()    { return _translate;}

 void BaseObject::Rotate(vec3 rotate)    {  _rotate    = rotate; }
 void BaseObject::Scale(vec3 scale)      {  _scale     = scale;  }
 void BaseObject::Translate(vec3 trans)  {  _translate = trans;  }

 void BaseObject::SetColor( vec4 col)       { _color = col;         }
 vec4 BaseObject::GetColor()                { return _color;        }

 void BaseObject::StepRotate(vec3 step)     { _rotate_step = step; _rotate += step; }
 void BaseObject::StepTranslate(vec3 step)  { _trans_step = step;  _translate += step; }
 void BaseObject::StepScale(vec3 step)      { _scale_step = step; _scale += step;  }

 void BaseObject::SetFirstTranslate(bool ok){ _FirstTranslate = ok;    }
 bool BaseObject::GetFirstTranslate()       { return _FirstTranslate;  }

 void BaseObject::SetProjection(glm::mat4 pro, bool orthomode )  {      _Projection = pro; _IsOrtho = orthomode;  }
 glm::mat4 & BaseObject::GetProjection()    {  return _Projection;      }

 bool BaseObject::HasTextures()              { return  _HasTextures; }
 void BaseObject::SetHasTextures(bool hasATexture) { _HasTextures = hasATexture; }

