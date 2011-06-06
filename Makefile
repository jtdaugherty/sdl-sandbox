
default: app

app: main.o
	ld -lsdl main.o -o app

%.cpp:
	g++ -c $@

clean:
	rm *.o
	rm app