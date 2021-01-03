#include "controllcontainer.h"

CControllContainer::CControllContainer( CControllContainer* parent) {
    if (parent == nullptr)
        _Parent = this;
    else
        _Parent = parent;

    _Child = nullptr;

    _Height = 0;
}

void CControllContainer::addContainer(CControllContainer * parent) {
    CControllContainer * child = new CControllContainer(parent);
    this->_Child = child;
}

bool CControllContainer::removeContainer(CControllContainer *container) {
    // do somthing later
    return true;
}

void CControllContainer::enableChilds() {

}

void CControllContainer::disableChilds() {

}

void CControllContainer::rename(std::string theNewName){
    _Name = theNewName;
}

bool CControllContainer::addButton(CButton *btn) {
    buttons.push_back(btn);
    return  true;
}

bool CControllContainer::addControll2D(Base2D *controll) {
    controlls2D.push_back(controll);
    return true;
}

bool CControllContainer::addControll3D(BaseObject *baseobject)
{
    controlls3D.push_back(baseobject);
    return  true;
}

bool CControllContainer::addText(std::string text, int resx, int resy){
    TextRender * t = new TextRender(resx,resy);
    t->AddString(text);
    _Height += t->getTextAreaHeight();
    return  true;
}
