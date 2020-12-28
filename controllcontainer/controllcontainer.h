#ifndef CCONTROLLCONTAINER_H
#define CCONTROLLCONTAINER_H

#include <vector>
#include "../base2d/base2d.h"
#include "../baseobject/baseobject.h"
#include "../buttons/button.h"

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
private:
    CControllContainer * _Child;
    CControllContainer * _Parent;
    std::vector<Base2D *> controlls2D;
    std::vector<BaseObject*> controlls3D;
    std::vector<CButton* > buttons;
    std::string _Name;


};

#endif // CCONTROLLCONTAINER_H
