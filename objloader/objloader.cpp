#include "objloader.h"
#include "../fileutils/fileutil.h"

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
    for ( int i = 0; i < lines.size(); i++) {
        std::string line = lines.at(i);
        // checken ob  '#', 'v' 'vt' 'f'

    }
}

void COBJLoader::SetOBJFileName(std::string filename) {
    _FileName = filename;
}


