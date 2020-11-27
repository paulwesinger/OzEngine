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

   std::string str = "Teststring zum testen";
   std::vector<std::string> parts;
   std::string key = " ";
   getStringParts(str,key,parts);

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
                    CCube * obj = new CCube(glm::vec3(0.0,0.0,0.0),glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w),projection->GetPerspective());

                    //obj->SetColor(glm::vec4(s3D.color.x, s3D.color.y, s3D.color.z, s3D.color.w));
                    if ( s3D.textures == "" )
                        obj->SetHasTextures( false);
                    else
                        obj->SetHasTextures( true);

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

void CEngine::getStringPart(std::string &s,std::string key, std::size_t &p, std::string & part){

    //std::string temp = s;
    p = s.find(key,0);
    if ( p != s.npos  ) {
        char buf[50];
        s.copy(buf,p );

        s.erase(0,p);
        s.erase(0,1);

        part = (std::string) buf;

    }
    else
        part = s;
}

std::string &CEngine::getValueItem(std::string &s, std::string erasestring) {
    return s.erase(0,erasestring.length() ) ;
}

void CEngine::stringPart(std::string &s, std::string key,  std::vector<std::string> & parts) { // Achtung which beginnt bei 1 !!!
    // --------------------------------------------------------------------
    // Argument which = 1. 2. oder n. teilstreing im String..
    // key = trennszeichen zwschen den string part,
    // bsp.: 'Heute ist nebel': Der 3. TeilString "nebel" nach dem 2. "space"
    //----------------------------------------------------------------------

    // erstmal den string zerlegen
    std::size_t pos;
    int i = 0;
    std::string part;

    std::string partstring = "";
    getStringPart(s,key, pos,partstring);

    while (  pos != s.npos && i < 20) {

        //parts.push_back(partstring);
        parts.push_back( s) ;

        getStringPart(s,key, pos, partstring);

        i++;
    }

    parts.push_back( s) ;
}





void CEngine::getStringParts(std::string inputString, std::string key, std::vector<std::string>& partlist){


    std::size_t pos = inputString.find(key);

    int j = 0;

    pos = inputString.find(key);


    while (pos != inputString.npos && j < 10) {

        char buf[30];

        inputString.copy(buf,pos-1);
        inputString.erase(0,pos);

        std::string s(buf);
        partlist.push_back(s);

        j ++;

        logimage("neue stringfunction: " + s);
        logimage("neue stringfunction: " + inputString );
        loginfo("J  : " + IntToString(j));
        logEmptyLine();
        pos = inputString.find(key);
    }
    partlist.push_back(inputString);

    for (uint i=0; i< partlist.size(); i++)
        logimage("neue stringfunction: " + partlist.at(i));



}




bool CEngine::init3DStruct(s3DStruct &d3s, std::vector<std::string> &cfg){
    if (cfg.size() >= CFG_3D_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        loginfo("List.textures:  " + cfg[8]);

        d3s.origin.x = StringToFloat(getValueItem(cfg[0],"originX "));
        d3s.origin.y = StringToFloat(getValueItem(cfg[1],"originY "));
        d3s.origin.z = StringToFloat(getValueItem(cfg[2],"originZ "));

        d3s.color.x = StringToFloat(getValueItem(cfg[3],"colorRed "));
        d3s.color.y = StringToFloat(getValueItem(cfg[4],"colorGreen "));
        d3s.color.z = StringToFloat(getValueItem(cfg[5],"colorBlue "));
        d3s.color.w = StringToFloat(getValueItem(cfg[6],"colorAlpha "));

        d3s.hasLight = StringToInt(getValueItem(cfg[7],"hasLight "));
        d3s.textures = getValueItem(cfg[8], "textures ");

        d3s.trans.translate.x = StringToFloat(getValueItem(cfg[9],"translateX "));
        d3s.trans.translate.y = StringToFloat(getValueItem(cfg[10],"translateY "));
        d3s.trans.translate.z = StringToFloat(getValueItem(cfg[11],"translateZ "));

        d3s.trans.rotate.x = StringToFloat(getValueItem(cfg[12],"rotateX "));
        d3s.trans.rotate.y = StringToFloat(getValueItem(cfg[13],"rotateY "));
        d3s.trans.rotate.z = StringToFloat(getValueItem(cfg[14],"rotateZ "));

        d3s.trans.scale.x = StringToFloat(getValueItem(cfg[15],"scaleX "));
        d3s.trans.scale.y = StringToFloat(getValueItem(cfg[16],"scaleY "));
        d3s.trans.scale.z = StringToFloat(getValueItem(cfg[17],"scaleZ "));

        d3s.firstTranslate = StringToInt(getValueItem(cfg[18],"firstTranslate "));

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





