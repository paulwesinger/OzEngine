#include "menu.h"
#include "../logs/logs.h"
#include "../utils/utils.h"



CMenu::CMenu(int resX, int resY) {
    _resY = resY;
    _resX = resX;

    PosX = 0;
    PosY = 0;

    Width =  MENU_WIDTH;
    Height = MENU_HEIGHT;

    backgroundColor = glm::vec4(0.0,0.0,0.0,1.0);
    foregroundColor = glm::vec4(1.0,1.0,1.0,1.0);

    init();
}

CMenu::CMenu(int resX, int resY, int width, int height) {
    _resY = resY;
    _resX = resX;

    PosX = 0;
    PosY = 0;

    Width =  width;
    Height = height;

    backgroundColor = glm::vec4(0.0,0.0,0.0,1.0);
    foregroundColor = glm::vec4(1.0,1.0,1.0,1.0);

    init();
}

CMenu::CMenu(int resX, int resY, int width, int height, glm::vec4 bg, glm::vec4 fg) {

    _resY = resY;
    _resX = resX;
    _currentY = 0;

    PosX = 0;
    PosY = 0;

    Width =  width;
    Height = height;

    backgroundColor = bg;
    foregroundColor = fg;

    init();
}

void CMenu::init() {

    menuBackground = new Base2D(_resX, _resY);
    menuBackground->setPos(PosX, PosY);
    menuBackground->setSize(Width, Height);
    menuBackground->setColor(backgroundColor);


}
void CMenu::Render() {
    menuBackground ->Render();
    if (! containerList.empty() ) {
        for(int i=0; i < containerList.size(); i++) {

            if ( ! containerList.at(i) ->buttons.empty()) {
                for (int j=0; j < containerList.at(i)->buttons.size(); j++){
                    containerList.at(i)->buttons.at(j) ->Render();
                }
            }
        }
    }

}

void CMenu::setMenuHeader(std::string name) {
    sMenuStruct ms;
    ms.text = new TextRender(_resX,_resY);
    ms.text->AddString(name);

    _currentY += ms.text->getTextAreaHeight();
}


void CMenu::addButton(CControllContainer* con, CButton *btn) {

    if ( con == nullptr  || btn == nullptr )
        return;

    con->addButton(btn);
}

void CMenu::addConatiner(CControllContainer *con) {

    if ( con == nullptr )
        return;
    containerList.push_back(con);
    _currentY += con->Dimensions().h + 1;
    loginfo("Add Controllcontainer to Menu .... Done"  ,"CMenu::addContainer");

}

void CMenu::addTextItem(CControllContainer *con, std::string text) {
    if ( con == nullptr)
        return;

    // Hier eigentlich header text..! container anpassen !!
}


void CMenu::AlignLeft() {

    alignleft = true;
    alignright = false;
}

void CMenu::AlignRight() {

    alignright = true;
    alignleft = false;
}
