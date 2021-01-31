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

    _LabelTextColor = LABEL::COLOR_TEXT;
    _TextEditColor  = LABEL::COLOR_BACKGROUND;

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

    Base2D::setPos(p.x,p.y);

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

    _PosLabel.x = _Pos.x + LABEL::MARGIN_X;
    _PosLabel.y = _Pos.y + LABEL::MARGIN_Y;
    // init ptr
    textLabel = new TextRender(resX, resY, _PosLabel);
    textLabel->SetScale(TEXT::SCALE_SMALL);
    textLabel->AddString("Test");
    _SizeLabel.w = textLabel->getWidth();
    _SizeLabel.h = textLabel->getTextAreaHeight();
    _ShowLabel = true;
    textLabel->setPos(_PosLabel);
}
