#ifndef CENGINE_H
#define CENGINE_H

#include "../initgl.h"
#include "../buttons/button.h"
#include "../textrenderer/textrender.h"
#include "../fileutils/fileutil.h"
#include "../defines.h"
#include <vector>

const std::string BUTTONS_CFG = "config/Buttons/";
const std::string OBJECT3D_CFG =  "config/3DObjects/";

class CEngine : public InitGL
{
public:
    CEngine(std::string titel = "OpenGL 4.5 Engine");
    void Run() override;
    void Done() override;

    static void EngineTestFunc1();   // Stellvertretend für alle zukünftigen funcs ->zum testen
    static void EngineTestFunc2();
    static void EngineTestFunc3();

protected:
    void loadButtons();

    // Lists for all objects:
    std::vector<std::string> btnList;
    std::vector<std::string> object2DList;
    std::vector<std::string> object3DList;

private:
    void InitButtons();
    void Init2D();
    void Init3D();

    bool initButtonStruct(sButtonStruct & bs,std::vector<std::string> cfg);
    std::string getBtnValueItem(std::string s, std::string erasestring);

    TextRender * textrenderer;
    fileUtil * fu;
};

#endif // CENGINE_H
