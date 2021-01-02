#ifndef CMENU_H
#define CMENU_H

#include "../textrenderer/textrender.h"
#include "../controllcontainer/controllcontainer.h"
#include "../buttons/button.h"
#include "../base2d/base2d.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>


const int MENU_WIDTH  = 150;
const int MENU_HEIGHT = 500;

class CMenu
{
public:
    CMenu(int resX, int resY);
    CMenu(int resX, int resY, int width, int height);
    CMenu(int resX, int resY, int width, int height, glm::vec4 bg, glm::vec4 fg);
    void Render();
    void addEntry(std::string text);
    void addButton(CButton * btn);
    void AlignLeft();
    void AlignRight();
protected:

    CControllContainer * controlls;

    Base2D * menuBackground;

    glm::vec4 backgroundColor;
    glm::vec4 foregroundColor;

    int PosX;
    int PosY;
    int Width;
    int Height;


    bool alignright;
    bool alignleft;
private:
    void init();
    int _resX;
    int _resY;
};

#endif // CMENU_H
