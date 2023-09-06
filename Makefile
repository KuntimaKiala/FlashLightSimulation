CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra
PROJECT = flashlight
OPENGLFLAGS = -ldl -lglfw
OBJ = -o
SRC = flashlight.cpp glad.c shader.cpp WindowManager.cpp stb_image.cpp

$(PROJECT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(OPENGLFLAGS) $(OBJ) $(PROJECT)

.PHONY: clean

clean:
	rm -f $(PROJECT)
