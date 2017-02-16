SHELL = /bin/sh
prefix = /usr/lib/x86_64-linux-gnu
CC = g++
C++ = g++
GLUT_LIBS = $(prefix)/libglut.so.3
X_LIBADD =  -lXmu -lXext -lXi -lX11
INCLUDES = -Iinclude -I/usr/include  
LDADD = $(GLUT_LIBS) $(prefix)/libGLU.so.1 $(prefix)/libGL.so  -lm
CFLAGS = -g -O2 -Wall -fomit-frame-pointer -ffast-math -fexpensive-optimizations -D_REENTRANT
CPPFLAGS = -g -std=c++11 -Wall -pedantic
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
LINK = $(CC) $(CFLAGS) $(LDFLAGS) -o $@

.SUFFIXES:
.SUFFIXES: .cpp .c .o 

.c.o:
	$(COMPILE) -c $<

.cpp.o:
	$(C++) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) -c $<

all: main

CLI_OBJECTS=main.o Tokenizer.o MoveCommand.o DrawCommand.o ColorCommand.o ReadCommand.o Command.o CLI.o

TIFF_OBJECTS=Utilities.o TiffStatCommand.o

main: $(CLI_OBJECTS) $(TIFF_OBJECTS)
	$(LINK) $(CLI_OBJECTS) $(TIFF_OBJECTS) $(LDADD) $(LIBS)

clean:
	-rm -f *.o $(PROGRAMS)

