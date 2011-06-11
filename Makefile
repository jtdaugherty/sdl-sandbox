
CC=g++

SDLINC=`sdl-config --cflags`
SDLLIB=`sdl-config --libs`

SDLFLAGS=$(SDLINC) $(SDLLIB) -framework Cocoa -lSDL_image
CPPFLAGS=$(SDLINC) -Wall

BUILD=build
PROG=$(BUILD)/app

OBJECTS=$(BUILD)/main.o $(BUILD)/SpriteSheet.o $(BUILD)/Sprite.o
EXTRAS=SDLMain/SDLMain.m

$(PROG): $(OBJECTS)
	$(CC) $(CPPFLAGS) $(SDLFLAGS) $(OBJECTS) $(EXTRAS) -o $(PROG)

$(BUILD)/main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp -o $(BUILD)/main.o

$(BUILD)/%.o: %.cpp %.h
	$(CC) $(CPPFLAGS) -c $*.cpp -o $(BUILD)/$*.o

clean:
	rm -f $(BUILD)/*.o
	rm -f $(PROG)
	rm -f *~
