#ifndef CENGINE_H
#define CENGINE_H

#include "../initgl.h"
#include "../buttons/button.h"
#include "../textrenderer/textrender.h"
#include "../fileutils/fileutil.h"
#include "../textedit/textedit.h"
#include "../defines.h"
#include "../defaults.h"
#include <vector>
#include "../controllcontainer/controllcontainer.h"
#include "../menu/menu.h"



const std::string BUTTONS_CFG = "config/Buttons/";
const std::string OBJECT3D_CFG =  "config/3DObjects/";



const int CFG_BUTTON_SIZE = 11;
const int CFG_3D_SIZE = 18;
const glm::vec4 BTN_ENABLE = glm::vec4(0.2, 0.2, 0.2, 1.0);
const glm::vec4 BTN_DISABLE = glm::vec4(0.2, 0.2, 0.2, 0.3);

const int MENU_SPACER = 10;


//--------------------------------------
// Look and feel
//--------------------------------------
const int BTN_WIDTH = 100;
const int BTN_HEIGHT = 50;

class CEngine : public InitGL
{
public:
    CEngine(std::string titel = "OpenGL 4.5 Engine");
    ~CEngine();
    void Run() override;
    void Done() override;

protected:
    void loadButtons();
    // Lists for all objects:
    std::vector<std::string> btnList;
    std::vector<std::string> object2DList;
    std::vector<std::string> object3DTexturedList;
    std::vector<std::string> object3DColoredList;


    CControllContainer *con1;
    CControllContainer *con2;

    CButton * fogBtn;
    static void funcFog();

 private:

    void InitButtons();
    void Init2D();
    void Init3D();
    void initMenu();

    bool initButtonStruct(sButtonStruct & bs,std::vector<std::string> cfg);
    bool init3DStruct(s3DStruct & d3s, std::vector<std::string> &cfg);

    bool loadTexturedCubes();
    bool loadColorCubes();
    //----------------------------------------------------------------
    // Menu controlls
    //----------------------------------------------------------------
    TextEdit * txtEdit;

    std::string &getValueItem(std::string &s, std::string erasestring);

    TextRender * textrenderer;

    fileUtil * fu;
};

#endif // CENGINE_H
