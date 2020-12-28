#ifndef CMENU_H
#define CMENU_H

#include "../textrenderer/textrender.h"
#include "../controllcontainer/controllcontainer.h"
#include "../buttons/button.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

class CMenu
{
public:
    CMenu();
    void Render();
    void addEntry(std::string text);
    void addButton(CButton * btn);
    void AlignLeft();
    void AlignRight();
protected:
    TextRender * MainMenu;
    CControllContainer * controlls;

    glm::vec4 background;
    glm::vec4 foreground;

    int PosX;
    int PosY;

    bool alignright;
    bool alignleft;

};

#endif // CMENU_H
