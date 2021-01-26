#include "textedit.h"

TextEdit::TextEdit(int resx, int resy)
    :Base2D(resx,resy){

}
TextEdit::TextEdit(int resx, int resy, sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol)
    :Base2D(resx,resy){

}
TextEdit::TextEdit(int resx, int resy,std::string path, sPoint p, sSize s, glm::vec4 labelcol, glm::vec4 editcol)
    :Base2D(resx,resy){

}
void TextEdit::Render() {

}
