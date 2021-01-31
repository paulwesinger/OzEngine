#include "textedit.h"
#include "../defaults.h"

TextEdit::TextEdit(int resx, int resy)
    :Base2D(resx,resy){
    resX = resx;
    resY = resy;

    _Pos.x = 100;
    _Pos.y = 100;
    _Size.w = 100;
    _Size.h = 50;

    _LabelTextColor = COLOR_LABEL_TEXT;
    _TextEditColor  = COLOR_LABEL_BACKGROUND;

    init();
}
TextEdit::TextEdit(int resx, int resy, sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol)
    :Base2D(resx,resy){

    resX = resx;
    resY = resy;
    _Pos    = p;
    _Size   = s;
    _LabelTextColor = labelcol;
    _TextEditColor  = editcol;

    init();


}
TextEdit::TextEdit(int resx, int resy,std::string path, sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol)
    :Base2D(resx,resy,path){

    resX = resx;
    resY = resy;
    _Pos    = p;
    _Size   = s;
    _LabelTextColor = labelcol;
    _TextEditColor  = editcol;
    init();

}
void TextEdit::Render() {
    Base2D::Render();

    if (textLabel != nullptr && _ShowLabel)
        textLabel->Render();

    if (editLabel != nullptr)
        editLabel->Render();

}

void TextEdit::showLabel(bool show){
    _ShowLabel = show;
}

void TextEdit::init() {

    textLabel = nullptr;
    editLabel = nullptr;

    _PosLabel.x =_Pos.x + 2;
    _PosLabel.y =_Pos.y + 2;
    // init ptr
    textLabel = new TextRender(resX, resY, _PosLabel);
    textLabel->AddString("Test");
    _SizeText.w = textLabel->getWidth();
    _SizeText.h = textLabel->getTextAreaHeight();
    _ShowLabel = true;
    textLabel->SetScale(BUTTON::TEXT_SCALE_SMALL);

}
