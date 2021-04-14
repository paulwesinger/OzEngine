#ifndef LANDSCAPE_H
#define LANDSCAPE_H



#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>


#include "../baseobject/baseobject.h"
#include "../defines.h"
#include "../camera/camera.h"
#include "../lights/light.h"

using namespace glm;


/*
 * Beschreibung:
 * Auflösung  des Tile: 32x32
 * Siehe auch Buch Gems 2 !!
 *
*/


class LandScape : public BaseObject
{
public:
    LandScape();
    LandScape(float rasterx, float rastey);
    LandScape(int patchx, int patchy, float rasterx, float rastey);
    LandScape(int patchx, int patchy, float rasterx, float rastey, vec3 color);


    void Draw(Camera *cam);
    // Object Loading:
    // Patches resolution
    void setPatchX(int px);
    void setPatchZ(int pz);
    // Raster margin
    void setRasterX(float rx);
    void setRasterZ(float rz);

    void init();

protected:
    uint _Vao, _Vbo,_Ebo;
private:
    std::vector<sVertexTexture>  vertsTex;
    std::vector<sVertexColor> vertsCol;

    float _RasterX;
    float _RasterZ;

    int _PatchX;
    int _PatchZ;

    void setUp();


};

#endif // LANDSCAPE_H
