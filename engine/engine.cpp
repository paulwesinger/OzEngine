#include "engine.h"
#include "../utils/utils.h"


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
   fileUtil * fileutil = new fileUtil();
   bool ok;
   ok = fileutil->readLine(BUTTONS_CFG + "Objects3DList.cfg", object3DList);
   if (ok) {
       loginfo("Lade Datei |ObjectList3D.cfg|","CEngine::Init3D");
       logEmptyLine();

       // Liste mit Objekten abarbeiten :
       for (unsigned int i = 0; i < object3DList.size(); i++) {

           std::string path = OBJECT3D_CFG + object3DList[i];

           fileUtil * objreader = new fileUtil;
           std::vector<std::string> objconfig;
           objreader->readLine(path, objconfig);

           if( ! objconfig.empty() ) {
               loginfo("Erstelle Object: .......< " + path+ " >", "Engine::Init3D");
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

bool CEngine::initButtonStruct(sButtonStruct &bs, std::vector<std::string> cfg) {

    if (cfg.size() >= 12 ) {
        bs.path = getBtnValueItem(cfg[0],"Image: ");
        loginfo("Image Path: "+ bs.path);

        bs.PosX = StringToFloat(getBtnValueItem(cfg[1],"PositionX: "));
        loginfo("PosX: "+ cfg[1] );

        bs.PosY = StringToFloat(getBtnValueItem(cfg[2],"PositionY: "));
        loginfo("PosY: "+ cfg[2]);

        bs.SizeX =  StringToFloat(getBtnValueItem(cfg[3],"SizeX: "));
        loginfo("SizeX: "+ cfg[3]);

        bs.SizeY =  StringToFloat(getBtnValueItem(cfg[4],"SizeY: "));
        loginfo("SizeY: "+ cfg[4]);

        bs.Enable = StringToInt(getBtnValueItem(cfg[5],"Enable: "));
        loginfo("Enabled: "+ cfg[5]);

        bs.ImageRed = StringToFloat(getBtnValueItem(cfg[6],"BGRed: "));
        loginfo("Image Red: "+ cfg[6]);

        bs.ImageGreen = StringToFloat(getBtnValueItem(cfg[7],"BGGreen: "));
        loginfo("ImageGreen: "+ cfg[7]);

        bs.ImageBlue = StringToFloat(getBtnValueItem(cfg[8],"BGBlue: "));
        loginfo("ImageBLue " + cfg[8]);

        bs.TextRed = StringToFloat(getBtnValueItem(cfg[9],"TextColorRed: "));
        loginfo("Textred: "+ cfg[9]);

        bs.TextGreen = StringToFloat(getBtnValueItem(cfg[10],"TextColorGreen: "));
        loginfo("TextGreen: "+ cfg[10]);

        bs.TextBlue = StringToFloat(getBtnValueItem(cfg[11],"TextColorBlue: "));
        loginfo("TextBlue: "+ cfg[11]);

        return true;
    }
    else
        return false;
}

std::string CEngine::getBtnValueItem(std::string s, std::string erasestring) {
    return s.erase(0,erasestring.length() ) ;
}



