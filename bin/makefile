OBJ = Display.o Camera.o Component.o LMath.o Scene.o Shader.o Buffer.o Texture.o ExternalComponents.o \
Player.o Text.o Bullet.o Enemy.o GameScene.o Health.o MainMenu.o GameOver.o
PROJECT_NAME = NeutralSpace
LIBS = -lglfw -ldl -lpthread -lX11 -lGLEW -lm -lGL -lSOIL
all: $(OBJ)
	gcc -o $(PROJECT_NAME) $(OBJ) $(LIBS)
clean:
	rm -f $(OBJ) $(PROJECT_NAME) vgcore.*
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
ExternalComponents.o: ../ExternalComponents.h ../ExternalComponents.c ../Display.h
	gcc -c ../ExternalComponents.c
Player.o: ../Player.h ../Player.c ../Display.h ../Component.h
	gcc -c ../Player.c
Text.o: ../Text.h ../Text.c ../Component.h ../Display.h
	gcc -c ../Text.c
Bullet.o: ../Bullet.h ../Bullet.c ../Component.h ../Display.h ../Player.h
	gcc -c ../Bullet.c
Enemy.o: ../Enemy.h ../Enemy.c ../Component.h ../Display.h
	gcc -c ../Enemy.c
GameScene.o: ../GameScene.h ../GameScene.c ../Display.h
	gcc -c ../GameScene.c
Health.o: ../Health.h ../Health.c ../Display.h ../Component.h ../Player.h
	gcc -c ../Health.c
MainMenu.o: ../MainMenu.h ../MainMenu.c ../Scene.h ../Display.h
	gcc -c ../MainMenu.c
GameOver.o: ../GameOver.h ../GameOver.c ../Scene.h ../Display.h
	gcc -c ../GameOver.c