TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        3DLoader/load3ds.cpp \
        base2d/base2d.cpp \
        baseobject/baseobject.cpp \
        buttons/button.cpp \
        camera/camera.cpp \
        colors/colorscheme.cpp \
        controllcontainer/controllcontainer.cpp \
        cube/colorcube.cpp \
        cube/cube.cpp \
        engine/engine.cpp \
        fileutils/fileutil.cpp \
        imageloader/loadimage.cpp \
        initgl.cpp \
        lights/light.cpp \
        logs/logs.cpp \
        main.cpp \
        menu/menu.cpp \
        meshobject/meshobject.cpp \
        objectclasses/object.cpp \
        objloader.cpp \
        objloader/objloader.cpp \
        plane3D/plane3D.cpp \
        projection/projection.cpp \
        shaders/shader.cpp \
        skybox/skybox.cpp \
        sphere/sphere.cpp \
        textedit/textedit.cpp \
        textrenderer/textrender.cpp \
        utils/utils.cpp \
        vecmath/vecmath.cpp

HEADERS += \
    3DLoader/load3ds.h \
    base2d/base2d.h \
    baseobject/baseobject.h \
    buttons/button.h \
    camera/camera.h \
    colors/colorscheme.h \
    controllcontainer/controllcontainer.h \
    cube/colorcube.h \
    cube/cube.h \
    defaults.h \
    defines.h \
    engine/engine.h \
    fileutils/fileutil.h \
    functions.h \
    imageloader/loadimage.h \
    include/ik_ESoundEngineOptions.h \
    include/ik_ESoundOutputDrivers.h \
    include/ik_EStreamModes.h \
    include/ik_IAudioRecorder.h \
    include/ik_IAudioStream.h \
    include/ik_IAudioStreamLoader.h \
    include/ik_IFileFactory.h \
    include/ik_IFileReader.h \
    include/ik_IRefCounted.h \
    include/ik_ISound.h \
    include/ik_ISoundDeviceList.h \
    include/ik_ISoundEffectControl.h \
    include/ik_ISoundEngine.h \
    include/ik_ISoundMixedOutputReceiver.h \
    include/ik_ISoundSource.h \
    include/ik_ISoundStopEventReceiver.h \
    include/ik_IVirtualRefCounted.h \
    include/ik_SAudioStreamFormat.h \
    include/ik_irrKlangTypes.h \
    include/ik_vec3d.h \
    include/irrKlang.h \
    initgl.h \
    lights/light.h \
    logs/logs.h \
    menu/menu.h \
    meshobject.h \
    meshobject/meshobject.h \
    objectclasses/object.h \
    objloader.h \
    objloader/objloader.h \
    plane3D/plane3D.h \
    projection/projection.h \
    shaders/shader.h \
    skybox/skybox.h \
    sphere/sphere.h \
    textedit/textedit.h \
    textrenderer/textrender.h \
    utils/utils.h \
    vecmath/vecmath.h \
    defaults.h

DISTFILES += \
    BtnInstances/Button0.txt \
    BtnInstances/Button2.txt \
    Description.txt \
    Makefile \
    Meshes/spaceship.3ds \
    ShaderSources/colorshader.frg \
    ShaderSources/cubefragmentshaderMulti.frg \
    ShaderSources/cubefragmentshaderMultinormals.frg \
    ShaderSources/cubevertexnormalshader.vex \
    ShaderSources/cubevertexshader.vex \
    ShaderSources/fragmentnormalcolorshader.frg \
    ShaderSources/vertexnormalcolorshader.vex \
    config/2DObjects/2DObjects.txt \
    config/3DObjects/Cube1.txt \
    config/3DObjects/Cube2.txt \
    config/3DObjects/Cube3.txt \
    config/3DObjects/Cube4.txt \
    config/3DObjects/Objects3DList.cfg \
    config/Buttons/Button1.txt \
    config/Buttons/Button2.txt \
    config/Buttons/Button3.txt \
    config/Buttons/ButtonList.cfg \
    config/cube2textures.cfg \
    config/cubetextures.cfg \
    icons/256x256/vlc.png \
    icons/QtProject-qtcreator.png \
    icons/chromium-browser.png \
    icons/ekiga.png \
    icons/gnome-color-manager.png \
    icons/google-chrome.png \
    icons/hb-icon.png \
    icons/ibus-hangul.png \
    icons/ibus-setup-hangul.png \
    icons/linguist.png \
    icons/preferences-color.png \
    icons/smplayer.png \
    images/Add.png \
    images/Add.xcf \
    images/Andromeda200x150.png \
    images/Bottom.png \
    images/Bottom.xcf \
    images/Headline.png \
    images/Headline.xcf \
    images/HochtzeitFred3.JPG \
    images/HochzeitFred1.JPG \
    images/HochzeitFred2.JPG \
    images/HochzeitFred4.JPG \
    images/HochzeitFredTorte.JPG \
    images/HochzeitFredTorte.png \
    images/Rahmen.xcf \
    images/Textfeld.png \
    images/Textfeld.xcf \
    images/Textfeld_neu.png \
    images/Textfeld_neu.xcf \
    images/button_green.png \
    images/button_green.xcf \
    images/button_white.png \
    images/darkgray.png \
    images/error.png \
    images/errorAlpha.png \
    images/free-vector-web-buttons-30.jpg \
    images/redButton.png \
    images/set-of-colorful-web-buttons-vector-1539551.jpg \
    images/testszeneAlpha.png \
    images/text_add_Yellow.png \
    images/text_add_Yellow.xcf \
    images/textfeldrahmen.png \
    images/the_delicate_web_buttons_sinks_01_vector_180084.jpg \
    images/wall.png \
    images/wallAlpha.png \
    libs/ikpFlac.so \
    libs/ikpMP3.so \
    libs/libIrrKlang.so \
    skybox/desert/desert_bk.tga \
    skybox/desert/desert_dn.tga \
    skybox/desert/desert_ft.tga \
    skybox/desert/desert_lf.tga \
    skybox/desert/desert_rt.tga \
    skybox/desert/desert_up.tga \
    skybox/orbital/orbital-element_bk.tga \
    skybox/orbital/orbital-element_dn.tga \
    skybox/orbital/orbital-element_ft.tga \
    skybox/orbital/orbital-element_lf.tga \
    skybox/orbital/orbital-element_rt.tga \
    skybox/orbital/orbital-element_up.tga
