all: stb.o
	g++ -lGLEW -lglfw -lGL -lglm -lm main.cc stb.o -o main

stb.o:
	g++ -c stb.cc -o stb.o

clean:
	rm -f main
