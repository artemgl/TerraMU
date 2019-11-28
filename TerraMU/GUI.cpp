#include "Gui.h"

Gui::Gui(GLFWwindow* window) : visiblePanels({}) {
	/*float aspect = (float)Display::getWidth() / (float)Display::getHeight();
	bars = GuiElementFactory::createGuiElement("bars.png", vec3(0.0f, aspect * 70.0f / 611.0f - 1.0f, 0.0f), 0.0f, 0.0f, 0.0f,
		vec3(2.0f, 2.0f * aspect * 70.0f / 611.0f, 1.0f));*/

		//cursor = GuiElementFactory::createGuiElement("Player.png", vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(0.01f/*0.4f*/ / Camera::getWidth() * 2, 0.01f/*0.4f*/, 1.0f));
	cursor = new Cursor(window, "cursor.png");

	inventory = GuiItemBuilder::buildInventory();
	bars = GuiItemBuilder::buildBars();
	points = GuiItemBuilder::buildPoints();
}

Gui::~Gui() {
	delete cursor;
	delete bars;
	delete inventory;
	//delete chest;
	delete points;
}

list<GuiElement*> Gui::getGuiElements() {
	list<GuiElement*> guis;

	for (GuiElement* gui : bars->getIcons()) {
		guis.push_back(gui);
	}

	for (GuiItem* item : visiblePanels) {
		for (GuiElement* gui : item->getIcons()) {
			guis.push_back(gui);
		}
	}

	return guis;
}

void Gui::placed(float x, float y) {
	for (GuiItem* panel : visiblePanels) {
		panel->placed(x, y);
	}
	bars->placed(x, y);
}

void Gui::unplaced(float x, float y) {
	inventory->unplaced(x, y);
	bars->unplaced(x, y);
	points->unplaced(x, y);
}

void Gui::clicked(float x, float y) {
	for (GuiItem* panel : visiblePanels) {
		panel->clicked(x, y);
	}
	bars->clicked(x, y);
}

void Gui::unclicked(float x, float y) {
	inventory->unclicked(x, y);
	bars->unclicked(x, y);
	points->unclicked(x, y);
}

//void Gui::reset() {
//	visibleGuis.clear();
//	visibleGuis.push_front(bars);
//}
//
//void Gui::changeVisibility(list<GuiElement*> guis) {
//	inventory->changeVisibility();
//}
//
//void Gui::changeInventoryVisibility() {
//	inventory->changeVisibility();
//}
//
//void Gui::changeChestVisibility() {
//	//add inventory
//	chest->changeVisibility();
//}
//
//void Gui::changePointsVisibility() {
//	points->changeVisibility();
//}