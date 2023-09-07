COMPILER =nvcc
PROJECT = flashlight
OPENGLFLAGS = -ldl -lglfw
OBJ = -o
SRC = flashlight.cpp glad.c shader.cpp WindowManager.cpp  KernelLauncher.cu

$(PROJECT): $(SRC)
	$(COMPILER)  $(SRC) $(OPENGLFLAGS) $(OBJ) $(PROJECT)

.PHONY: clean

clean:
	rm -f $(PROJECT)
