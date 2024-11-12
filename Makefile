all: main.cc
	g++ -lGLEW -lGL -lGLU -lglfw main.cc -o main

clean:
	rm -f clean
