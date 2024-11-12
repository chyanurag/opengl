all: main.cc
	g++ -lGLEW -lGL -lGLU -lglfw -lm main.cc -o main

clean:
	rm -f clean
