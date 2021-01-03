#ifndef CCONTROLLCONTAINER_H
#define CCONTROLLCONTAINER_H

#include <vector>
#include "../base2d/base2d.h"
#include "../baseobject/baseobject.h"
#include "../buttons/button.h"
#include "../textrenderer/textrender.h"

// Container Class für
// 2D Steuerelemente(Buttons ,...
class CControllContainer
{
public:
    CControllContainer(CControllContainer *parent = nullptr);

    void addContainer(CControllContainer *container);
    bool removeContainer(CControllContainer *container);
    void rename(std::string theNewName);

    void enableChilds();
    void disableChilds();

    bool addControll2D(Base2D *control);
    bool addControll3D(BaseObject * baseobject);
    bool addButton(CButton * btn);
    bool addText(std::string text,int resx, int resy);
private:
    CControllContainer * _Child;
    CControllContainer * _Parent;
    std::vector<Base2D *> controlls2D;
    std::vector<BaseObject*> controlls3D;
    std::vector<CButton* > buttons;
    std::vector<TextRender*> texts;
    std::string _Name;

    int _Height;



};

#endif // CCONTROLLCONTAINER_H
