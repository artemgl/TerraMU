#pragma once
class Map;
class Player;
//class Creature;
#include "Map.h"
//#include "MapObject.h"
#include "Entity.h"
#include "WayHandler.h"
#include "Creature.h"
#include "Player.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
//#include <iostream>
//using namespace std;

class GameController {
private:
	static Map* map;

	static Entity* cursor;
	static Camera* camera;

	static vec2 mousePosition;
	static vec2 lastMouseClick;

	static Player* player;
public:
	static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorEnterCallback(GLFWwindow* window, int entered);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static void setMap(Map* map) { GameController::map = map; };
	static void setPlayer(Player* player) { GameController::player = player; };
	static void setCursor(Entity* cursor) { GameController::cursor = cursor; };
	static void setCamera(Camera* camera) { GameController::camera = camera; };

	static void go(float coordX, float coordY);
	static void changeVisibility(int posX, int posY);

	static Camera* getCamera() { return GameController::camera; };
	static Map* getMap() { return GameController::map; };
	static Player* getPlayer() { return GameController::player; };

};