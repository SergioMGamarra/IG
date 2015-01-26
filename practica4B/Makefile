# fichero Makefile
#
# nombre del fichero ejecutable
#
#

TARGETS= practica4

CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

CC = g++

MODULOS:= user_code.o\
         practica3.o\
         jpg_imagen.o file_ply_stl.o\
         jpg_readwrite.o jpg_memsrc.o\

LIBS:= -lglut -ljpeg -lGLU -lGL
CPPFLAGS:=   -g

$(TARGETS): $(MODULOS)	
	$(CC) -o $(TARGETS) $(LDFLAGS) $(MODULOS) $(LIBS) 

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

