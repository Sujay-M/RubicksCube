RC : main.o RubicksCube.o Cube.o Points.o
	g++ -o RC main.o RubicksCube.o Cube.o Points.o -lfreeglut -lglu32 -lopengl32
main.o : main.cpp RubicksCube.o
	g++ -c -o main.o main.cpp
RubicksCube.o : RubicksCube.cpp Cube.o
	g++ -c -o RubicksCube.o RubicksCube.cpp
Cube.o : Cube.cpp Points.o
	g++ -c -o Cube.o Cube.cpp
Points.o : Points.cpp
	g++ -c -o Points.o Points.cpp
clean :
	rm RC.exe main.o RubicksCube.o Cube.o Points.o