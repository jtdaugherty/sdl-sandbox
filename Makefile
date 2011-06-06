
CC=g++

SDLINC=`sdl-config --cflags`
SDLLIB=`sdl-config --libs`

SDLFLAGS=$(SDLINC) $(SDLLIB) -framework Cocoa -lSDL_image
CPPFLAGS=$(SDLINC) -Wall

PROG=app
OBJECTS=main.o
EXTRAS=SDLMain.m

$(PROG): $(OBJECTS)
	$(CC) $(CPPFLAGS) $(SDLFLAGS) $(OBJECTS) $(EXTRAS) -o $(PROG)

%.cpp:
	$(CC) $(CPPFLAGS) -c $@

clean:
	rm -f *.o
	rm -f $(PROG)