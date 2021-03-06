#pragma once
#include <list>
class Slot;
#include "GuiItem.h"

class SlotArray : public GuiItem {
private:
	int columns;
	int rows;

	void prepareForGettingIcons() override;

	list<Slot*> slots = {};

public:
	SlotArray(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale);

	SlotArray(int columns, int rows, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		SlotArray(columns, rows, position, rotationX, rotationY, rotationZ, vec3(scale)) {};

	list<Slot*> getSlots() { return slots; };

};