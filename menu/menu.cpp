#include "menu.h"

CMenu::CMenu(){
    controlls = new CControllContainer();
    AlignRight();

    background = glm::vec4(0.0,0.0,0.0,1.0);
    foreground = glm::vec4(1.0,1.0,1.0,1.0);

}

void CMenu::Render() {

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
