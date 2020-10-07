#include "load3ds.h"

//#include <fstream>
//#include <iostream>

using namespace std;

#include "load3ds.h"
#include "../logs/logs.h"
#include "../utils/utils.h"

CLoad3DS::CLoad3DS(std::string filename) {
    file = filename;
}

CLoad3DS::CLoad3DS(const CLoad3DS& orig) {
}

CLoad3DS::~CLoad3DS() {
}

bool CLoad3DS::LoadMesh() {
    FILE * m_File;
    unsigned short l_chunk_id;
    unsigned int l_chunk_length;
    unsigned short numVertices;

    if (( m_File = fopen(file.c_str(),"rb")) == NULL)
        return false;

    fseek(m_File, 0L, SEEK_END);
    int size;
    size = ftell(m_File);
    fseek(m_File,0,SEEK_SET);
    int  id_beginning;

    while (ftell (m_File) < size ) {//Loop to scan the whole file
        fread (&l_chunk_id, 2, 1, m_File);
        fread (&l_chunk_length, 4, 1, m_File);

        switch (l_chunk_id) {
            case 0x4d4d :
                printf("\nID : %hx\n", l_chunk_id);
                printf("Length: %u\n",l_chunk_length);

                break;
            case 0x3d3d :
                printf("\nID : %hx\n", l_chunk_id);
                printf("Length: %u\n",l_chunk_length);
                break;

            case 0x4000: {
                int i=0;
                unsigned char l_char;
                char name[50];
                do
                {
                   fread (&l_char, 1, 1, m_File);
                   name[i]=l_char;
                   i++;
                }while(l_char != '\0' && i<50);

                loginfo("Objectname " + std::string(name), "CLoad3DS::0x4000 ");
                break;
            }

            case 0x4100 :   // Muss gelesen werden um zum nächsten Subchunk zu kommen
                break;

            case 0x4110: {
                fread (&numVertices, sizeof (unsigned short), 1, m_File);
                //p_object->vertices_qty = l_qty;
                loginfo("Number of vertices: " + IntToString((int)numVertices),"CLoad3DS::0x4110 HEX");
                float x,y,z;

                for (int i=0; i<numVertices; i++) {
                    fread (&x, sizeof(float), 1, m_File);
                    fread (&y, sizeof(float), 1, m_File);
                    fread (&z, sizeof(float), 1, m_File);
                 //   if ( i < 100 )
                 //       printf("Vertices : %f %f %f ... Ein Teil davon.\hochzeit des figaro andre rieun", x,y,z);
                }
                break;
            }

            case 0x4140: {
                float u,v;  // Kann sein , die Reihenfolge auf vu zu wechseln
                fread(&numVertices,sizeof(unsigned short),1, m_File);
                loginfo("Number of Textures uV " + IntToString((int) numVertices) ,"CLoad3DS:: 0x4140 HEX" );
                for (int i = 0; i < numVertices; i ++) {
                    fread(&u, sizeof(float),1, m_File);
                    fread(&v, sizeof(float),1, m_File);
                }
                break;

            }

            case 0xAFFF: { // MAterial Block
                printf("\nID : %hx\n", l_chunk_id);
                printf("Length: %u\n",l_chunk_length);
                break;
            }

            case 0xA000: {
                printf("switching Chunk to 0xA000");
                printf("\nID : %hx\n", l_chunk_id);
                printf("Length: %u\n",l_chunk_length);
                int i=0;
                unsigned char l_char;
                char name[50];
                do
                {
                   fread (&l_char, 1, 1, m_File);
                   name[i]=l_char;
                   i++;
                }while(l_char != '\0' && i<100);

                loginfo("Materialname " + std::string(name), "CLoad3DS::0xA000 ");
                break;
            }

            case 0xA010: {
                printf("\nswitching Chunk to 0xA010");
                printf("\nID : %hx\n", l_chunk_id);
                printf("Length: %u\n",l_chunk_length);

                float colorX,colorY, colorZ, shiness;  // ambient,specular, diffuse
                int floatread = 0;
                char name[100];
                unsigned char l_char;
                int i = 0;
             //   fread(&numVertices,sizeof(unsigned short),1 ,m_File);
             //   printf("Num Material %hu \n", numVertices);
                do
                {
                //   fread (&l_char, 1, 1, m_File);
                //   name[i]=l_char;
                   fread(&colorX,sizeof(float),1, m_File);
                   fread(&colorY,sizeof(float),1, m_File);
                   fread(&colorZ,sizeof(float),1, m_File);
                   printf("ColorX ColorY CoorZ  %3.2f %3.2f %3.2f \n", colorX, colorY, colorZ);

                   i += 3 * sizeof(float) ;
                }while( i < l_chunk_length );
                printf("i = %d \n",i);



               /*
                while (floatread + 4 <= l_chunk_length ) { //
                    fread(&colorX,sizeof(float), 1, m_File);
                    fread(&colorY,sizeof(float), 1, m_File);
                    fread(&colorZ,sizeof(float), 1, m_File);
                    fread(&shiness,sizeof(float), 1, m_File);
                    printf("(Ambient,Diffuse,Specular, Shiness) - Light %f %f %f %f  \n", colorX, colorY, colorZ, shiness);
                    floatread += 4;
                }
                if ( floatread != l_chunk_length) {
                    unsigned int diff = l_chunk_length - floatread;
                    for ( unsigned int i = 0; i < diff; i++ ) {
                        fread(&shiness,sizeof(float),1,m_File);
                        printf("Rest Shiness ? %f \n", shiness);
                    }
                }


                printf ("Grösse Float %2d \n", sizeof(float)); // ergibt derzeit 4
                */

                break;
            }

            case 0xA020 : {
                printf("switching Chunk to 0xA020");
                printf("\nID : %hx\n", l_chunk_id);
                printf("Length: %u\n",l_chunk_length);
                break;
            }

            default:
                fseek(m_File, l_chunk_length-6, SEEK_CUR);
                break;
        }
    }
    fclose(m_File);
    return true;
}
