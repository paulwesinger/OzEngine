#ifndef CLOAD3DS_H
#define CLOAD3DS_H

#include <fstream>
#include <iostream>


class CLoad3DS {
public:
    CLoad3DS(std::string filename);
    CLoad3DS(const CLoad3DS& orig);
    virtual ~CLoad3DS();

    bool LoadMesh();
private:
    std::string file;

};

#endif // CLOAD3DS_H
