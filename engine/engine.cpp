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

   // stringpart testen
   std::string st = "Heute istroter Oktober";
   stringPart(st," ",3);


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
               loginfo(path + ".... Done", "Engine::Init3D");
               logEmptyLine();
               s3DStruct s3D;
           }
       }
   }
   else
       logwarn("Fehler: Datei | config/Object3DList.cfg nicht gefunden ! |");
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

        //std::string st = BUTTONS_CFG + btnList[0];
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

}

std::string CEngine::getStringPart(std::string &s,std::string key, std::size_t &p){

    //std::string temp = s;
    p = s.find(key,0);
    if ( p != s.npos  ) {
        char buf[50];
        s.copy(buf,p );

        s.erase(0,p);
        s.erase(0,1);

        return (std::string) buf;
    }
    return  s;
}

std::string &CEngine::getValueItem(std::string &s, std::string erasestring) {
    return s.erase(0,erasestring.length() ) ;
}

std::string CEngine::stringPart(std::string &s, std::string key,int which) { // Achtung which beginnt bei 1 !!!
    // --------------------------------------------------------------------
    // Argument which = 1. 2. oder n. teilstreing im String..
    // key = trennszeichen zwschen den string part,
    // bsp.: 'Heute ist nebel': Der 3. TeilString "nebel" nach dem 2. "space"
    //----------------------------------------------------------------------

    // erstmal den string zerlegen
    std::vector<std::string> parts;  // Liste mit den String teilen
    std::size_t pos;
    int i = 0;

    std::string partstring = getStringPart(s,key, pos);


    while (  pos != s.npos && i < 20) {

        parts.push_back( partstring) ;

        partstring = getStringPart(s,key, pos);

        i++;
    }

    parts.push_back( partstring) ;


    // ---------------------------------------
    // Testausgabe für string liste
    //----------------------------------------
    for (int i = 0; i < parts.size(); i ++)  {
        loginfo("Parts Liste: " + parts.at(i), "stringPart");
    }


    // Falls i ==  entweder kein "key" im text oder string ist leer
    // wir sind schon wieder fertig
    if ( i == 0 )
        return s;

    std::string returnstring = "";
    for ( int j = 0; j < parts.size();j++) {
        if ( j == which-1)   {
            returnstring = parts.at(j);
            break;
        }
    }

    return returnstring;





}

bool CEngine::init3DStruct(s3DStruct &d3s, std::vector<std::string> cfg){
    if (cfg.size() >= CFG_3D_SIZE ) {

        //+---------------------------------------------------------------------+
        //+     VORGEHEN :                                                      |
        //+     Liste abarbeiten, Teilstring bis " " ermitteln,                 |
        //+     Variablen name = Teilstring --> 2. Teilstring in Wert wandeln   |
        //+     und in der s3DStruct zuweisen                                   |
        //+---------------------------------------------------------------------+

        d3s.origin.x    = StringToFloat(getValueItem(cfg[0], "originX "));
        d3s.origin.y    = StringToFloat(getValueItem(cfg[1], "originY "));
        d3s.origin.z    = StringToFloat(getValueItem(cfg[2], "originZ "));

        d3s.color.x     = StringToFloat(getValueItem(cfg[3], "colorRed "));
        d3s.color.y     = StringToFloat(getValueItem(cfg[4], "colorGreen "));
        d3s.color.z     = StringToFloat(getValueItem(cfg[5], "colorBlue "));
        d3s.color.w     = StringToFloat(getValueItem(cfg[6], "colorAlpha "));

        d3s.hasLight    = StringToInt(getValueItem(cfg[7], "hasLight "));

        // Irgendwie anders machen --> dynamischer !!!
        return true;
    }
    return false;
}

bool CEngine::initButtonStruct(sButtonStruct &bs, std::vector<std::string> cfg) {

    if (cfg.size() >= CFG_BUTTON_SIZE ) {
        bs.path = getValueItem(cfg[0],"Image: ");
        loginfo("Image Path: "+ bs.path);

        bs.PosX = StringToFloat(getValueItem(cfg[1],"PositionX: "));
        loginfo("PosX: "+ cfg[1] );

        bs.PosY = StringToFloat(getValueItem(cfg[2],"PositionY: "));
        loginfo("PosY: "+ cfg[2]);

        bs.SizeX =  StringToFloat(getValueItem(cfg[3],"SizeX: "));
        loginfo("SizeX: "+ cfg[3]);

        bs.SizeY =  StringToFloat(getValueItem(cfg[4],"SizeY: "));
        loginfo("SizeY: "+ cfg[4]);

        bs.Enable = StringToInt(getValueItem(cfg[5],"Enable: "));
        loginfo("Enabled: "+ cfg[5]);

        bs.ImageRed = StringToFloat(getValueItem(cfg[6],"BGRed: "));
        loginfo("Image Red: "+ cfg[6]);

        bs.ImageGreen = StringToFloat(getValueItem(cfg[7],"BGGreen: "));
        loginfo("ImageGreen: "+ cfg[7]);

        bs.ImageBlue = StringToFloat(getValueItem(cfg[8],"BGBlue: "));
        loginfo("ImageBLue " + cfg[8]);

        bs.TextRed = StringToFloat(getValueItem(cfg[9],"TextColorRed: "));
        loginfo("Textred: "+ cfg[9]);

        bs.TextGreen = StringToFloat(getValueItem(cfg[10],"TextColorGreen: "));
        loginfo("TextGreen: "+ cfg[10]);

        bs.TextBlue = StringToFloat(getValueItem(cfg[11],"TextColorBlue: "));
        loginfo("TextBlue: "+ cfg[11]);

        return true;
    }
    else
        return false;
}





