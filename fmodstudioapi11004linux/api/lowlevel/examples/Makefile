#########################################################
#                                                       #
#                 Makefile for linux gcc                #
#                                                       #
#########################################################

#########################################################
##
##               specify the include paths
##
#########################################################

#INCLUDE_DIR= -I/usr/local/include -I./include

#-I/usr/X11R6/include -I./include
#########################################################
##
##              specify the lib directories
##
#########################################################

#LIB_DIR= -L/usr/local/lib -L./lib/

#########################################################
##
##             specify the librarys to link
##
#########################################################

#LIBS= -lfmod -lGL -lGLU -lglut -lXmu -lXi -lstdc++ -lm

#########################################################
##
## specify a line to compile the source files. The first
## version produces a release build. The second produces
## a debug build
##
#########################################################
#LIBS= -lfmod -lGL -lGLU -lglut -lXmu -lXi -lstdc++ -lm

CC=gcc
CFLAGS=-I.
LIBS=-lfmod -lGL -lGLU -lglut -lXmu -lXi -lstdc++ -lm
_DEPS = glm.h dirent32.h gltb.h
DEPS = $(_DEPS)
_OBJ = main.o gltb.o glm.o
OBJ = $(_OBJ)
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)


