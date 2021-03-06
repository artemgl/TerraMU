#include "RoundButton.h"
#include "GuiElementFactory.h"
#include "Maths.h"
#include "GuiElement.h"

RoundButton::RoundButton(bool isEnable, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) : 
	GuiItem(position, rotationX, rotationY, rotationZ, scale), isEnable(isEnable) {
	icon = GuiElementFactory::createGuiElement("round_button.png", position, rotationX, rotationY, rotationZ, scale);
	icon->setTextureMatrix(Maths::createTextureMatrix(vec2(0.0f, 0.0f), vec2(1.0f / 3.0f, 1.0f)));
	icons.push_back(icon);
}

void RoundButton::placed(float x, float y) {
	GuiItem::placed(x, y);
	if (isEnable) {
		icon->setTextureMatrix(Maths::createTextureMatrix(vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 1.0f)));
	}
}

void RoundButton::unplaced(float x, float y) {
	GuiItem::unplaced(x, y);
	if (isEnable) {
		icon->setTextureMatrix(Maths::createTextureMatrix(vec2(0.0f, 0.0f), vec2(1.0f / 3.0f, 1.0f)));
	}
}

bool RoundButton::clicked(float x, float y) {
	if (GuiItem::clicked(x, y)) {
		if (isEnable) {
			icon->setTextureMatrix(Maths::createTextureMatrix(vec2(2.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 1.0f)));
		}

		return true;
	}

	return false;
}

void RoundButton::unclicked(float x, float y) {
	GuiItem::unclicked(x, y);

	if (isEnable) {
		icon->setTextureMatrix(Maths::createTextureMatrix(vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 1.0f)));
	}
}

void RoundButton::prepareForGettingIcons() {
	icon->setPosition(position);
	icon->setRotationX(rotationX);
	icon->setRotationY(rotationY);
	icon->setRotationZ(rotationZ);
	icon->setScale(scale);
}