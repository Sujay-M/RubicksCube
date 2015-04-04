BIN = .\bin
INCLUDE = .\includes
SOURCE = .\src
BUILD = .\build
OBJECTS = $(BUILD)\main.o $(BUILD)\RCube.o $(BUILD)\Structs.o $(BUILD)\mouseHelper.o \
	$(BUILD)\displayHelper.o $(BUILD)\Cube.o $(BUILD)\Points.o
LIBS = -lfreeglut -lglu32 -lopengl32
$(BIN)\RC : $(OBJECTS)
	g++ -I $(INCLUDE) -o $(BIN)\RC $(OBJECTS) $(LIBS)

$(BUILD)\main.o : $(INCLUDE)\RCube.hpp $(INCLUDE)\Structs.h $(INCLUDE)\mouseHelper.h $(INCLUDE)\displayHelper.h
	g++ -I $(INCLUDE) -c -o $(BUILD)\main.o $(SOURCE)\main.cpp

$(BUILD)\RCube.o : $(INCLUDE)\Cube.hpp
	g++ -I $(INCLUDE) -c -o $(BUILD)\RCube.o $(SOURCE)\RCube.cpp

$(BUILD)\Structs.o : $(INCLUDE)\Structs.h
	g++ -I $(INCLUDE) -c -o $(BUILD)\Structs.o $(SOURCE)\Structs.cpp

$(BUILD)\displayHelper.o : $(INCLUDE)\displayHelper.h
	g++ -I $(INCLUDE) -c -o $(BUILD)\displayHelper.o $(SOURCE)\displayHelper.cpp

$(BUILD)\mouseHelper.o : $(INCLUDE)\mouseHelper.h
	g++ -I $(INCLUDE) -c -o $(BUILD)\mouseHelper.o $(SOURCE)\mouseHelper.cpp

$(BUILD)\Cube.o : $(INCLUDE)\Points.hpp
	g++ -I $(INCLUDE) -c -o $(BUILD)\Cube.o $(SOURCE)\Cube.cpp

$(BUILD)\Points.o :
	g++ -I $(INCLUDE) -c -o $(BUILD)\Points.o $(SOURCE)\Points.cpp

clean :
	rm $(BIN)\RC.exe $(OBJECTS)