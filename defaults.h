#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <glm/glm.hpp>

namespace CONTROLL {
    const int HEIGHT = 40;
};


namespace BUTTON {
    const int X_MARGIN = 5;
    const int Y_MARGIN = 10;
    const int Y_MARGINBTN_TEXT_MEDIUM = 20;

    const int DEFAULT_WIDTH   = 80;
    const int DEFAULT_HEIGHT = 40;

    const float ALPHA_IMAGE_ENABLED  = 1.0f;
    const float ALPHA_IMAGE_DISABLED = 0.3f;

    const glm::vec3 COLOR_DEFAULT_IMAGE = {1.0, 1.0, 1.0};
    const glm::vec3 COLOR_DEFAULT_TEXT  = {1.0, 1.0, 1.0};
};

namespace LABEL {
    const glm::vec4 COLOR_TEXT = glm::vec4(0.0);
    const glm::vec4 COLOR_BACKGROUND = glm::vec4(0.8,0.8, 0.8, 1.0);
    const int MARGIN_X  = 2;
    const int MARGIN_Y  = 5;
}

namespace TEXT {
    const float SCALE_SMALL = 1.0f;
    const float SCALE_MEDIUM = 1.5f;
    const float SCALE_BIG = 2.0f;

    const float ALPHA_ENABLED = 1.0f;
    const float ALPHA_DISABLED = 0.3f;
}

#endif // DEFAULTS_H
