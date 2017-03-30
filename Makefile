SHELL = /bin/sh
prefix = /usr/lib/x86_64-linux-gnu
CC = gcc
C++ = g++
GLUT_LIBS = $(prefix)/libglut.so.3
X_LIBADD =  -lXmu -lXext -lXi -lX11
INCLUDES = -Iinclude -I/usr/include  
LDADD = $(GLUT_LIBS) $(prefix)/libGLU.so.1 $(prefix)/libGL.so  -lm
CFLAGS = -g -O2 -Wall -fomit-frame-pointer -ffast-math -fexpensive-optimizations -D_REENTRANT
CPPFLAGS = -g -std=c++11 -Wall -pedantic
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
LINK = $(C++) $(CFLAGS) $(LDFLAGS) -o $@

.SUFFIXES:
.SUFFIXES: .cpp .c .o 

.c.o:
	$(COMPILE) -c $<

.cpp.o:
	$(C++) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) -c $<

all: main

CLI_OBJECTS=main.o Tokenizer.o MoveCommand.o DrawCommand.o ColorCommand.o ReadCommand.o Command.o CLI.o

TIFF_OBJECTS=Utilities.o TiffStatCommand.o TiffReadCommand.o TiffImageData.o TiffWriteCommand.o ResizeCommand.o Filter.o

3D_OBJECTS=Matrix44.o Vector4.o Vector3.o lines.o PushCommand.o PopCommand.o TranslateCommand.o ScaleCommand.o RotateCommand.o OrthoCommand.o PerspectiveCommand.o LookatCommand.o

main: $(CLI_OBJECTS) $(TIFF_OBJECTS) $(3D_OBJECTS)
	$(LINK) $(CLI_OBJECTS) $(TIFF_OBJECTS) $(3D_OBJECTS) $(LDADD) $(LIBS)

clean:
	-rm -f *.o $(PROGRAMS)

