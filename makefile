RC : main.o RCube.o Cube.o Points.o
	g++ -o RC main.o RCube.o Structs.o Cube.o Points.o -lfreeglut -lglu32 -lopengl32
main.o : main.cpp RCube.o Structs.o
	g++ -c -o main.o main.cpp
RCube.o : RCube.cpp Cube.o
	g++ -c -o RCube.o RCube.cpp
Structs.o : Structs.cpp
	g++ -c -o Structs.o Structs.cpp
Cube.o : Cube.cpp Points.o
	g++ -c -o Cube.o Cube.cpp
Points.o : Points.cpp
	g++ -c -o Points.o Points.cpp
clean :
	rm RC.exe main.o RCube.o Cube.o Points.o Structs.o