#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <glm/glm.hpp>


namespace BUTTON {
    const int X_MARGIN = 5;
    const int Y_MARGIN = 10;
    const int Y_MARGINBTN_TEXT_MEDIUM = 20;
    const float TEXT_SCALE_SMALL = 1.0f;
    const float TEXT_SCALE_MEDIUM = 1.5f;
    const float TEXT_SCALE_BIG = 2.0f;

    const int DEFAULT_WIDTH   = 80;
    const int DEFAULT_HEIGHT = 40;

    const float ALPHA_TEXT_ENABLED = 1.0f;
    const float ALPHA_TEXT_DISABLED = 0.3f;

    const float ALPHA_IMAGE_ENABLED  = 1.0f;
    const float ALPHA_IMAGE_DISABLED = 0.3f;

    const glm::vec3 COLOR_DEFAULT_IMAGE = {1.0, 1.0, 1.0};
    const glm::vec3 COLOR_DEFAULT_TEXT  = {1.0, 1.0, 1.0};
};



const glm::vec4 COLOR_LABEL_TEXT = glm::vec4(0.0);
const glm::vec4 COLOR_LABEL_BACKGROUND = glm::vec4(0.8,0.8, 0.8, 1.0);





#endif // DEFAULTS_H
