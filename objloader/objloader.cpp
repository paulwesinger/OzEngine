#include <stdio.h>
#include <cstring>
#include "objloader.h"
#include "../fileutils/fileutil.h"
#include "../utils/utils.h"
#include "../logs/logs.h"

COBJLoader::COBJLoader() {
    _FileName = "NO FILE";
}

COBJLoader::COBJLoader(std::string filename) {
    _FileName = filename;
}

COBJLoader::~COBJLoader(){
    texCoords.clear();
    faces.clear();
    vecs.clear();
}

int COBJLoader::LoadOBJ() {
    fileUtil * fu = new fileUtil();
    std::vector<std::string> lines;
    if (_FileName == NO_FILE )
        return NO_FILENAME;

    if ( ! fu->readLine(_FileName,lines) )
        return READ_ERROR;

    if (lines.empty())
        return  EMPTY_FILE;
    // Bis jetzt alles gut ...


    for ( uint i = 0; i < lines.size(); i++) {

        //std::string line = lines.at(i);
        std::string line = lines.at(i);
        // checken ob  '#', 'v' 'vt' 'f' oder andere...... die nicht ausgewertet werden
        // erstmal die ersten 3 zeichen in den Buffer kopieren und testen:
        char * cstr = new char [line.length()+1];
        std::strcpy (cstr, line.c_str());

        // Viele if's...

        std::string st;
        st.append(cstr,2);


        logimage("cstr " + st + "|");

        if (st == "v " ) {  // Vectors
            line.erase(0,2);  // erease v+leer -> übrig ist x, y, z
            VECTOR v = ReadVec(line," ");
            logimage("Vector : x= " + FloatToString(v.x) + " y= " + FloatToString(v.y) + " z= " + FloatToString(v.z));
        }
        else
            if (st == "vt") {// textures

            }
            else
                if ( st == "vn") { // normale

                }




        //vecs.push_back()
        logwarn("lines[" +IntToString(i) + "] " + line);

    }
    return NO_ERROR;
}

VECTOR COBJLoader::ReadVec(std::string line, std::string key) {


    VECTOR v;
    bool ok;
    // Format: "x y z"
    // Finde den das nächste leerzeichen:
    v.x = ParseStringToFloat(line, key, ok);

    v.y = ParseStringToFloat(line, key,ok);

    v.z = ParseStringToFloat(line,"",ok);

    return  v;

}
float COBJLoader::ParseStringToFloat(std::string &line, std::string key, bool & ok) {

    ok = false;
    char buffer[20];

    if ( key != "") {
        std::size_t pos = line.find(key,0);
        if (pos != line.npos ){ // ende der zeile

            line.copy(buffer,pos-1);
            line.erase(0, pos+1);
            return StringToFloat((std::string) buffer);
        }
        return 0.0f;
    }
    return StringToFloat(line);

}

TEXTURECOORDS  COBJLoader::ReadTex(std::string line, std::string key) {
    // FORMAT vt u v
    TEXTURECOORDS tex;


    return tex;
}
void COBJLoader::SetOBJFileName(std::string filename) {
    _FileName = filename;
}


