UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    COMPILER = g++
    FLAGS = -std=c++1y -Wall
    GL_FLAGS = -lGL -lglfw -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lassimp
endif

INCLUDES = shader.h camera.h stb_image.h model.h mesh.h cube.h skybox.h alphabot.h
FILES = main.cpp
LIB = libalphabot.a
OBJS = shader.o camera.o model.o mesh.o cube.o skybox.o alphabot.o

all: $(LIB)

shader.o: shader.cpp shader.h
	$(COMPILER) -c $(FLAGS) $(INCLUDES) shader.cpp

camera.o: camera.cpp camera.h
	$(COMPILER) -c $(FLAGS) $(INCLUDES) camera.cpp

mesh.o: mesh.cpp mesh.h
	$(COMPILER) -c $(FLAGS) $(INCLUDES) mesh.cpp

cube.o: cube.cpp cube.h
	$(COMPILER) -c $(FLAGS) $(INCLUDES) cube.cpp

skybox.o: skybox.cpp skybox.h
	$(COMPILER) -c $(FLAGS) $(INCLUDES) skybox.cpp

alphabot.o: alphabot.cpp alphabot.h
	$(COMPILER) -c $(FLAGS) $(INCLUDES) alphabot.cpp

model.o: model.cpp model.h
	$(COMPILER) -c $(FLAGS) $(INCLUDES) model.cpp

$(LIB): $(OBJS) glad.o
	$(AR) rvs $(LIB) $(OBJS) glad.o 

main.o: main.cpp
	$(COMPILER) -c $(FLAGS) $(INCLUDES) main.cpp

glad.o: glad.c
	$(COMPILER) -c $(FLAGS) $(INCLUDES) glad.c


main: $(OBJS) main.o
	$(COMPILER) $(OBJS) main.o glad.o -o main $(GL_FLAGS) $(GLAD_FLAGS)

.PHONY: clean run
clean:
	rm opengl-app

run: opengl-app
	./opengl-app
