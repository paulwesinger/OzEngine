# glad.h und glad.c aus ~/Downloads    sonst wird nix gefunden!
INC =  -I/usr/include/ -I/usr/include/glm/ -I/usr/include/freetype2/
SRC = main.cpp  initgl.cpp shaders/shader.cpp cube/cube.cpp baseobject/baseobject.cpp \
base2d/base2d.cpp logs/logs.cpp utils/utils.cpp camera/camera.cpp vecmath/vecmath.cpp \
skybox/skybox.cpp fileutils/fileutil.cpp objectclasses/object.cpp projection/projection.cpp \
plane3D/plane3D.cpp 3DLoader/load3ds.cpp textrenderer/textrender.cpp sphere/sphere.cpp \
imageloader/loadimage.cpp buttons/button.cpp colors/colorscheme.cpp engine/engine.cpp\
lights/light.cpp meshobject/meshobject.cpp objloader/objloader.cpp menu/menu.cpp \
controllcontainer/controllcontainer.cpp

	 

#LIB = -L/usr/local/lib
#LIBS = -L/usr/lib64/ 
#LIB =  -lm -ldl -lSDL2

LIB = -L/usr/lib64/ -lm -ldl -lSDL2 -lSDL2_image -lGL -lGLEW  -lfreetype -lIrrKlang

CC = /usr/bin/g++
BIN = Test
CFLAGS = -Wall -c 'sdl-config --cflags' -std=c++14 
LDFLAGS = -g
OBJ= $(SRC)
$(BIN):
	$(CC) $(INC) $(SRC) $(LIB)  -o $(BIN) $(LIB) $(LDFLAGS) $< 
.Phony: clean

clean:
	 rm -rf $(BIN)




