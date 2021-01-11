#ifndef CBUTTON_H
#define CBUTTON_H

#include "../base2d/base2d.h"
#include "../colors/colorscheme.h"
#include "../textrenderer/textrender.h"

// -----------------------------------------------
// Base class for all kind of buttons
// derrived classes must overwrite Method Render()
// -----------------------------------------------

const int DEFAULT_BUTTON_WIDTH   = 80;
const int DEFAULT_BUZTTON_HEIGHT = 40;

const float ALPHA_TEXT_ENABLED = 1.0f;
const float ALPHA_TEXT_DISABLED = 0.3f;

const float ALPHA_IMAGE_ENABLED  = 1.0f;
const float ALPHA_IMAGE_DISABLED = 0.3f;

const glm::vec3 BTN_COLOR_DEFAULT_IMAGE = {1.0, 1.0, 1.0};
const glm::vec3 BTN_COLOR_DEFAULT_TEXT  = {0.0, 0.0, 0.0};

const int X_MARGIN = 5;
const int Y_MARGIN = 10;

typedef struct {
    std::string path;
    int PosX;
    int PosY;
    int SizeX;
    int SizeY;
    int Enable;
    float ImageRed;
    float ImageGreen;
    float ImageBlue;
    float TextRed;
    float TextGreen;
    float TextBlue;
} sButtonStruct;

class CButton : public Base2D
{
public:
    CButton(int resx, int resy);
    CButton(int resx, int resy, std::string path, std::string text);
    ~CButton();

    // ********************************************
    // Look and feel
    // ********************************************
    // set
    void setText(std::string t);
    void setPos(int x, int y);
    void enable();
    void disable();

    int Height();
    int Width();

    std::string Text();
    bool Enabled();

    FP clickFunc;  // aufzurufende func für Buttonclick
  //  FPEnableBtn clickFuncEnable;
    void AddHandler(FP handler);

    //*********************************************
    // Virtuals
    // ********************************************
    virtual void Render() = 0;
    virtual void setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol);

    //EventHandling
    virtual void OnClick() = 0 ;  // Muss überschrieben werden !!!!
    virtual void OnRelease() = 0;
    virtual void OnFocus();


protected:

    virtual void animateClick();
    virtual void releaseClick();

    bool _Enabled;
    std::string _Text;
    FLOAT2 textPos;
    float _AlphaText;
    float _Alpha_Image;

    TextRender * btnText;


private:

    void init();

    glm::vec3 _ImageCol;
    glm::vec3 _TextCol;
    //pointStruct _Pos;   // Linke obere Ecke
    CColorScheme colorscheme;
    sButtonScheme _ButtonColors; // die vecs mit den farben
};

// ----------------------------------------------------
// Standard Button zur Verwendung:
// ----------------------------------------------------

class CDefaultButton: public CButton {
  public:
    CDefaultButton( int resx, int resy);
    CDefaultButton( int resx, int resy, std::string path, std::string text);

    void setbuttonColors(glm::vec3 imagecol, glm::vec3 textcol) override;

    void Render()  override;
    void OnClick() override;
    void OnRelease() override;
protected:
    void setSize(int w, int h) override;
    void animateClick() override;
    void releaseClick() override;

    Base2D * textImage;
    void  setPos(int x, int y) override;

};


#endif // CBUTTON_H
