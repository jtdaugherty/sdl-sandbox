
CC=g++

SDLINC=`sdl-config --cflags`
SDLLIB=`sdl-config --libs`

EXTRAS ?=
SDLFLAGS ?= $(SDLINC) $(SDLLIB) -lSDL_image

CPPFLAGS=$(SDLINC) -Wall

BUILD=build
PROG=$(BUILD)/app

OBJECTS=$(BUILD)/main.o $(BUILD)/SpriteSheet.o $(BUILD)/Sprite.o \
	$(BUILD)/Board.o $(BUILD)/BoardUI.o $(BUILD)/Timer.o \
	$(BUILD)/Param.o $(BUILD)/Animation.o

$(PROG): $(OBJECTS)
	$(CC) $(CPPFLAGS) $(SDLFLAGS) $(OBJECTS) $(EXTRAS) -o $(PROG)

$(BUILD)/main.o: src/main.cpp
	$(CC) $(CPPFLAGS) -c src/main.cpp -o $(BUILD)/main.o

$(BUILD)/%.o: src/%.cpp src/%.h
	$(CC) $(CPPFLAGS) -c src/$*.cpp -o $(BUILD)/$*.o

clean:
	rm -f $(BUILD)/*.o
	rm -f $(PROG)
	rm -f *~
