#include "engine.h"
#include "../utils/utils.h"

/*

#include <stdio.h>
#include <usb.h>
main(){
    struct usb_bus *bus;
    struct usb_device *dev;
    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_busses; bus; bus = bus->next)
        for (dev = bus->devices; dev; dev = dev->next){
            printf("Trying device %s/%s\n", bus->dirname, dev->filename);
            printf("\tID_VENDOR = 0x%04x\n", dev->descriptor.idVendor);
            printf("\tID_PRODUCT = 0x%04x\n", dev->descriptor.idProduct);
        }
}

*/



CEngine::CEngine(std::string titel) :
        InitGL(titel)
{
    // Do some init stuff

}

void CEngine::Done() {
    InitGL::Done();
}

void CEngine::Run() {

    initMenu();
    Init2D();
    Init3D();
    InitButtons();
    //logimage("Erstelle Cockpt............");
    //cockpit= new Base2D(_ResX, _ResY,"images/blackWidowAlpha1920x1200.png");

    InitGL::Run();
}

// ---------------------------------------------------------------
// Place here Functons for button handler..
// ---------------------------------------------------------------
void CEngine::EngineTestFunc1() {
     loginfo("TestFunc1","Engine:: EngineTestFunc 1");
}
void CEngine::EngineTestFunc2() {
     loginfo("TestFunc2","Engine:: EngineTestFunc 2");
}
void CEngine::EngineTestFunc3() {
    loginfo("TestFunc3","Engine:: EngineTestFunc 3");
}

// --------------------------------------------------------------
// Init Methods for Engines
// --------------------------------------------------------------
void CEngine::initMenu(){

}

void CEngine::Init2D() {

    //================================
    // Init 2D Objects
    // ===============================

    // Testweise mal einfügen
    loginfo("============================");
    loginfo("Erstelle 2D Objekte.........");
    loginfo("============================");
    logimage("Erstelle TestIcon..........");
    base2d = new Base2D(_ResX, _ResY,"icons/ibus-setup-hangul.png");
    base2d->setPos(500,400);
    add2Dobject(base2d);
  }

void CEngine::Init3D(){
    logEmptyLine();
    loginfo("============================");
    loginfo("Erstelle 3D Objekte.........");
    loginfo("============================");
   fileUtil * fileutil = new fileUtil();
   bool ok;

   std::string str = "TranslateX: 2.0";
   std::vector<std::string> parts = split(str," ");

   for (int i = 0; i< parts.size(); i++)
       loginfo(parts.at(i));


   ok = fileutil->readLine(OBJECT3D_CFG + "Objects3DList.cfg", object3DList);
   if (ok) {
       loginfo("Lade Datei |ObjectList3D.cfg|","CEngine::Init3D");

        // Liste mit Objekten abarbeiten :
        for (unsigned int i = 0; i < object3DList.size(); i++) {

            std::string path = OBJECT3D_CFG + object3DList[i];

            loginfo("Erstelle Object: .......< " + path+ " >","Engine::Init3D");

            fileUtil * objreader = new fileUtil;
            std::vector<std::string> objconfig;
            objreader->readLine(path, objconfig);


            if( ! objconfig.empty() ) {

                s3DStruct s3D;

                if (init3DStruct(s3D,objconfig)) {

                    CCube * obj = new CCube();
                    //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                    if ( s3D.textures == "" )
                        obj->SetHasTextures( false);
                    else
                        obj->SetHasTextures( true);

                    obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                    obj->SetFirstTranslate( ( s3D.firstTranslate == 1) ? true: false);
                    obj->Rotate(glm::vec3(s3D.trans.rotate.x, s3D.trans.rotate.y, s3D.trans.rotate.z) );
                    obj->Translate(glm::vec3(s3D.trans.translate.x, s3D.trans.translate.y, s3D.trans.translate.z));
                    obj->Scale(glm::vec3(s3D.trans.scale.x, s3D.trans.scale.y, s3D.trans.scale.z));

                    //----------------------------------------
                    // Add textures , if we have some
                    // ---------------------------------------
                    bool texturesok;
                    std::vector<std::string> images;

                    std::string path = s3D.textures;

                    if ( s3D.textures != "" ) {
                        fileUtil fu;

                        texturesok =  fu.readLine(path, images);
                        if (texturesok)
                            obj->addTexture(images,"InitGL::add3DObject");
                        else
                            logwarn("Init::Cube2 :  konnte Textures nicht laden ! ","InitGL::Init::cube2::addTexture");
                    }

                    add3Dobject(obj);
                    loginfo("s3D initialisisert ","CEngine::init3D");
                }
                else
                    logwarn("konnte s3D nicht initialisieren !!", "CEngine::init3D" );
                   // Hier die neuen stringpart functions einbauen

                logEmptyLine();
                loginfo("Prepare for next Object: ","CEngine::init3D");

           }
       }
   }
   else
       logwarn("Fehler: Datei | config/Object3DList.cfg nicht gefunden ! |");

   logEmptyLine() ;
   loginfo("----------------------------");
   loginfo(" Init 3D Objects ");
   loginfo("     READY");
   loginfo("----------------------------");
}



void CEngine::InitButtons() {

    logEmptyLine();
    loginfo("============================");
    loginfo("Erstelle Buttons ...........");
    loginfo("============================");

    loadButtons();

}

void CEngine::loadButtons() {
    // Open file
    bool ok;
    fu = new fileUtil();

    ok = fu->readLine(BUTTONS_CFG + "ButtonList.cfg", btnList);


    if (ok) {
        loginfo("Lade Datei |ButtonList.cfg|","CEngine::loadbuttons");
        logEmptyLine();

        for (unsigned int i = 0; i < btnList.size(); i++  ){

            std::string path = BUTTONS_CFG + btnList[i];

            fileUtil * btnreader = new fileUtil;
            std::vector<std::string> btnconfig;
            btnreader->readLine(path, btnconfig);



            if ( ! btnconfig.empty() ) {

                loginfo("Erstelle Button: .......< " + path+ " >", "Engine::loadButtons");

                sButtonStruct btnStruct;
                if  (initButtonStruct(btnStruct,btnconfig) ) {

                    CButton * btn = new CDefaultButton(_ResX,_ResY ,btnStruct.path);//   btnStruct.path);
                    btn->setPos(btnStruct.PosX,btnStruct.PosY);
                    btn->setSize(btnStruct.SizeX, btnStruct.SizeY);
                    btn->setbuttonColors(glm::vec3(btnStruct.ImageRed,btnStruct.ImageGreen,btnStruct.ImageBlue),
                                         glm::vec3(btnStruct.TextRed,btnStruct.TextGreen,btnStruct.TextBlue));

                    switch (i) {
                        case 0: btn ->AddHandler(EngineTestFunc1); break;
                        case 1: btn ->AddHandler(EngineTestFunc2); break;
                        case 2: btn ->AddHandler(EngineTestFunc3); break;
                    default:
                        btn ->AddHandler(EngineTestFunc1);
                    }
                    if (btnStruct.Enable > 0 )
                        btn->setEnable();
                    else
                        btn->setDisable();
                    btn->setText("Edit");
                    addButton(btn);

                    loginfo(".........Done", "Engine::loadButtons");
                    logEmptyLine();
                }

            }

        }


    }
    else
        logwarn("Fehler: Datei | config/ButtonList nicht gefunden ! |");


    logEmptyLine() ;
    loginfo("----------------------------");
    loginfo(" Load Button Objects ");
    loginfo("        READY");
    loginfo("----------------------------");

}

std::string &CEngine::getValueItem(std::string &s, std::string erasestring) {
    return s.erase(0,erasestring.length() ) ;
}



std::vector<std::string> CEngine::split(std::string const& input, std::string const& separator = " ")
{
  std::vector<std::string> result;
  std::string::size_type position, start = 0;

  while (std::string::npos != (position = input.find(separator, start)))
  {
    result.push_back(input.substr(start, position-start));
    start = position + separator.size();
  }

  result.push_back(input.substr(start));
  return result;
}

bool CEngine::init3DStruct(s3DStruct &d3s, std::vector<std::string> &cfg){
    if (cfg.size() >= CFG_3D_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        for (uint i = 0; i < cfg.size(); i++) {
            std::vector<std::string> parts = split(cfg.at(i));

            if (parts.at(0) == "originX")
                d3s.origin.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "originY")
                d3s.origin.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "originZ")
                d3s.origin.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorRed")
                d3s.color.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorGreen")
                d3s.color.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorBlue")
                d3s.color.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "colorAlpha")
                d3s.color.w = StringToFloat(parts.at(1));

            if (parts.at(0) == "hasLight")
                d3s.hasLight = StringToInt(parts.at(1));

            if (parts.at(0) == "textures")
                d3s.textures = parts.at(1);

            if (parts.at(0) == "translateX")
                d3s.trans.translate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateY")
                d3s.trans.translate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "translateZ")
                d3s.trans.translate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateX")
                d3s.trans.rotate.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateY")
                d3s.trans.rotate.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "rotateZ")
                d3s.trans.rotate.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleX")
                d3s.trans.scale.x = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleY")
                d3s.trans.scale.y = StringToFloat(parts.at(1));

            if (parts.at(0) == "scaleZ")
                d3s.trans.scale.z = StringToFloat(parts.at(1));

            if (parts.at(0) == "firstTranslate")
                d3s.firstTranslate = StringToInt(parts.at(1));


        }
        return true;

    }
    return false;
}

bool CEngine::initButtonStruct(sButtonStruct &bs, std::vector<std::string> cfg) {

    if (cfg.size() >= CFG_BUTTON_SIZE ) {
        bs.path = getValueItem(cfg[0],"Image: ");
        loginfo("Image Path: "+ bs.path);

        bs.PosX = StringToFloat(getValueItem(cfg[1],"PositionX: "));

        bs.PosY = StringToFloat(getValueItem(cfg[2],"PositionY: "));

        bs.SizeX =  StringToFloat(getValueItem(cfg[3],"SizeX: "));

        bs.SizeY =  StringToFloat(getValueItem(cfg[4],"SizeY: "));

        bs.Enable = StringToInt(getValueItem(cfg[5],"Enable: "));

        bs.ImageRed = StringToFloat(getValueItem(cfg[6],"BGRed: "));

        bs.ImageGreen = StringToFloat(getValueItem(cfg[7],"BGGreen: "));

        bs.ImageBlue = StringToFloat(getValueItem(cfg[8],"BGBlue: "));

        bs.TextRed = StringToFloat(getValueItem(cfg[9],"TextColorRed: "));

        bs.TextGreen = StringToFloat(getValueItem(cfg[10],"TextColorGreen: "));

        bs.TextBlue = StringToFloat(getValueItem(cfg[11],"TextColorBlue: "));

        return true;
    }
    else
        return false;
}





