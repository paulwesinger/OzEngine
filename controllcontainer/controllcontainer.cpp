#include "controllcontainer.h"
#include "../logs/logs.h"
#include "../utils/utils.h"

CControllContainer::CControllContainer( CControllContainer* parent) {
    if (parent == nullptr)
        _Parent = this;
    else
        _Parent = parent;

    _Child = nullptr;

    _Height = 0;
    _CurrentY = 5;
    _CurrentX = 5;
}

CControllContainer::~CControllContainer() {
    releaseConterItems();
}

void CControllContainer::addContainer(CControllContainer * parent) {
    CControllContainer * child = new CControllContainer(parent);
    this->_Child = child;
}

void CControllContainer::disableControll(Base2D *con){
    if (con != nullptr) {
        con->disable();
    }

}

void CControllContainer::enableControll(Base2D *con){
    if (con != nullptr)
        con->enable();
}

bool CControllContainer::removeContainer(CControllContainer *container) {
    // do somthing later
    return true;
}

// Remove items and give allocated memory free
void CControllContainer::releaseConterItems() {

    if ( ! controlls2D.empty()) {
        for (uint i=0; i< controlls2D.size(); i++) {
            delete controlls2D.at(i);
        }
        controlls2D.clear();
    }

    if (! controlls3D.empty() ) {
        for (uint i=0; i< controlls3D.size(); i++) {
            delete controlls3D.at(i);
        }
        controlls3D.clear();
    }

    if (! buttons.empty() ) {
        for (uint i=0; i< buttons.size(); i++) {
            delete buttons.at(i);
        }
        buttons.clear();
    }

    if (! texts.empty() ) {
        for (uint i=0; i< texts.size(); i++) {
            delete texts.at(i);
        }
        texts.clear();
    }


}

void CControllContainer::setPos(sPoint pos) {
    _Pos = pos;
}
sPoint CControllContainer::Pos() {
    return _Pos;
}

void CControllContainer::setDimensions(sSize size) {
    _Dimensions = size;
}
sSize CControllContainer::Dimensions() {
    return _Dimensions;
}

void CControllContainer::enableChilds() {

}

void CControllContainer::disableChilds() {

}

void CControllContainer::rename(std::string theNewName){
    _Name = theNewName;
}

bool CControllContainer::addButton(CButton *btn) {

    btn->setPos(_CurrentX,_CurrentY);
    // Gesammthöhe des container
    _Height += btn->Height();
    // Nächste Position im Container
    _CurrentY += btn->Height() + 1 ;
    _Dimensions.h = _Height;
    buttons.push_back(btn);

    loginfo("Add Button to Container ...... Done ", "CControllcontainer::addbutton");
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

    sPoint p;
    p.x = _Pos.x+ 1;
    p.y = _CurrentY;


    TextRender * t = new TextRender(resx,resy);
    t->setPos(p);
    t->AddString(text);


    _CurrentY += t->getTextAreaHeight() + 1;
    _Height += t->getTextAreaHeight();
    return  true;
}
