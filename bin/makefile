OBJ = Display.o Camera.o Component.o LMath.o Scene.o Shader.o Buffer.o Texture.o
PROJECT_NAME = NeutralSpace
LIBS = -lglfw -ldl -lpthread -lX11 -lGLEW -lm -lGL -lSOIL
all: $(OBJ)
	gcc -o $(PROJECT_NAME) $(OBJ) $(LIBS)
clean:
	rm -f $(OBJ) $(PROJECT_NAME)
Buffer.o: ../Buffer.h ../Buffer.c ../Component.h
	gcc -c ../Buffer.c
Display.o: ../Display.h ../Display.c ../Scene.h
	gcc -c ../Display.c
Camera.o: ../Camera.h ../Camera.c ../LMath.h ../Shader.h
	gcc -c ../Camera.c
Component.o: ../Component.h ../Component.c
	gcc -c ../Component.c
LMath.o: ../LMath.h ../LMath.c
	gcc -c ../LMath.c
Scene.o: ../Scene.h ../Scene.c ../Component.h ../Camera.h ../Shader.h
	gcc -c ../Scene.c
Shader.o: ../Shader.h ../Shader.c
	gcc -c ../Shader.c
Texture.o: ../Texture.h ../Texture.c ../Component.h
	gcc -c ../Texture.c