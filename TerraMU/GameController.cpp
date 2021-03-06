#include "GameController.h"
#include "Display.h"
#include "WayHandler.h"
#include "Maths.h"
#include "Converter.h"
#include "Map.h"
#include "Gui.h"
#include "Creature.h"
#include "Monster.h"
#include "MobSpawner.h"
#include "GuiItem.h"
#include "Camera.h"
#include "Player.h"
#include "Action.h"
#include "Cursor.h"

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	gui->unplaced(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());

	/*camera->increaseYaw((xPos - mousePosition.x) * 0.1f);
	camera->increasePitch((yPos - mousePosition.y) * 0.1f);*/

	mousePosition = vec2(xPos, yPos);

	gui->placed(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());
}

void GameController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	vec2 mousePosMap = Converter::fromDisplayToMap(mousePosition);
	vec2 mousePosGui = Converter::fromDisplayToGui(mousePosition);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		gui->getCursor()->makeRed();
		if (!gui->clicked(mousePosGui.x, mousePosGui.y)) {
			if (!player->isInMotion()) {
				player->getAvatar()->getAnimation()->play();
			}
			player->nullWay();

			map->interact(mousePosMap.x, mousePosMap.y);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		gui->getCursor()->reset();
		gui->unclicked(mousePosGui.x, mousePosGui.y);
	}
}

void GameController::cursorEnterCallback(GLFWwindow* window, int entered) {

}

void GameController::processPanel(GuiItem* currPanel) {
	list<GuiItem*> visiblePanels = *gui->getVisiblePanels();
	bool exists = false;
	for (GuiItem* panel : visiblePanels) {
		if (panel == currPanel) {
			exists = true;
			break;
		}
	}

	vec3 cameraOffset(0.0f);
	for (GuiItem* panel : visiblePanels) {
		cameraOffset += vec3(-panel->getScale().x * Camera::getWidth() / 2 / 2, 0.0f, 0.0f);
	}

	if (exists) {
		*gui->getVisiblePanels() = {};
	}
	else {
		*gui->getVisiblePanels() = {currPanel};
		cameraOffset += vec3(currPanel->getScale().x * Camera::getWidth() / 2 / 2, 0.0f, 0.0f);
	}
	camera->increasePosition(cameraOffset);
}

void GameController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		GameController::processPanel(gui->getInventory());
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		GameController::processPanel(gui->getPoints());
	}

	/*if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		camera->increasePosition(0.0f, 0.0f, -0.02f);
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		camera->increasePosition(-0.02f, 0.0f, 0.0f);
	}
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		camera->increasePosition(0.0f, 0.0f, 0.02f);
	}
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		camera->increasePosition(0.02f, 0.0f, 0.0f);
	}*/
}

//void GameController::clearActions() {
//	actions.clear();
//}
//
//void GameController::setActions(list<Action*> actions) {
//	clearActions();
//	for (Action* action : actions) {
//		addAction(action);
//	}
//}

void GameController::update(float deltaTime) {
	/*if (!actions.empty() && !player->isInMotion()) {
		actions.front()->execute();
		actions.pop_front();
	}*/

	player->update(deltaTime);
	for (MobSpawner* spawner : *map->getSpawners()) {
		spawner->update(deltaTime);
	}
	map->nullMobMap();
}