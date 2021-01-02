#include "menu.h"



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

    PosX = 0;
    PosY = 0;

    Width =  width;
    Height = height;

    backgroundColor = bg;
    foregroundColor = fg;

    init();
}

void CMenu::init() {
    controlls = new CControllContainer();

    menuBackground = new Base2D(_resX, _resY);
    menuBackground->setPos(PosX, PosY);
    menuBackground->setSize(Width, Height);
    menuBackground->setColor(backgroundColor);


}
void CMenu::Render() {
    menuBackground ->Render();
}

void CMenu::addEntry(std::string text) {

}

void CMenu::addButton(CButton *btn) {
   // controlls->addButton(btn);
}

void CMenu::AlignLeft() {

    alignleft = true;
    alignright = false;
}

void CMenu::AlignRight() {

    alignright = true;
    alignleft = false;
}
