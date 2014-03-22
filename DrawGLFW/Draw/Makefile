
CC = g++
CFLAGS = -Wall -ggdb
LINKLIB = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
INCLUDE = -I . ../include
OTHER = ../lib/x64/libLeap.so -Wl,-rpath,../lib/x64

all: cscope draw 
#objloader 

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c $< 

draw: draw.o objloader.o 
	$(CC) $^ $(LINKLIB) -o $@ $(OTHER)

#objloader: draw.o objloader.o
#	$(CC) $^ $(LINKLIB)  -o $@ $(OTHER)

cscope:
	cscope -Rqb

clean:
	$(RM) draw
	$(RM) *.o
	$(RM) cscope.*

