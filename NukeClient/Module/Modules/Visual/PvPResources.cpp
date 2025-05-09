#include "PvPResources.h"

#include "../../DrawUtils.h"
#include "../ModuleManager.h"
// #include "Theme.h"

PvPResources::PvPResources() : IModule(0x0, Category::VISUAL, "Displays items on screen that are used for PVP") {
	// registerBoolSetting("Textual", &this->text, this->text);
	registerFloatSetting("Display on X", &this->pvpX, this->pvpX, 0.f, Game.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("Display on Y", &this->pvpY, this->pvpY, 0.f, Game.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

PvPResources::~PvPResources() {
}

const char* PvPResources::getModuleName() {
	return ("PvPResources");
}

float xDif = -1.f;
float yDif = -1.f;

void PvPResources::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())
		return;
	auto player = Game.getLocalPlayer();
	float testValYe = 40.f * scale;
	float lineWidth2 = 1.f * scale;
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	Vec2 windowSizeReal = Game.getClientInstance()->getGuiData()->windowSizeReal;
	Vec2 mousePosition = *Game.getClientInstance()->getMousePos();
	mousePosition = mousePosition.div(windowSizeReal);
	mousePosition = mousePosition.mul(windowSize);

	if (!text) {
		static float rcolors[4];
		// static auto ThemeMod = moduleMgr->getModule<Theme>();
		// if (ThemeMod->rainbow) {
		if (rcolors[3] < 1) {
			rcolors[0] = 1;
			rcolors[1] = 0.2f;
			rcolors[2] = 0.2f;
			rcolors[3] = 1;
			//}

			Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);  // perfect code, dont question this

			rcolors[0] += 0.0015f;
			if (rcolors[0] >= 1) {
				rcolors[0] = 0;
			}

			Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1.f);
		} else {
			DrawUtils::setColor(1.f, 1.f, 1.f, 1.f);
		}
		DrawUtils::drawRectangle(Vec2(pvpX, pvpY), Vec2(pvpX + (testValYe), pvpY + testValYe), lineWidth2);
		Vec2 centerPoint = Vec2(pvpX + testValYe / 2, pvpY + testValYe / 2);
		DrawUtils::fillRectangle(Vec2(centerPoint.x - lineWidth2 / 2, centerPoint.y - testValYe / 2), Vec2(centerPoint.x + lineWidth2 / 2, centerPoint.y + testValYe / 2));
		DrawUtils::fillRectangle(Vec2(centerPoint.x - testValYe / 2, centerPoint.y - lineWidth2 / 2), Vec2(centerPoint.x + testValYe / 2, centerPoint.y + lineWidth2 / 2));

		if (isThereCrystal()) {
			int gSlot = pullSlot(637);
			DrawUtils::drawItem(Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(gSlot), Vec2(pvpX + (lineWidth2 * scale + 1.f) + testValYe / 2, pvpY + (lineWidth2 * scale - 1.f + testValYe / 2)), 1.f, scale, false);
			std::string yikes = std::to_string(countItem(637));
			DrawUtils::drawText(Vec2(pvpX + (lineWidth2 * scale + 4.f) + testValYe / 2, pvpY + (lineWidth2 * scale + 7.f) + testValYe / 2), &yikes, MC_Color(255, 255, 255), scale);
		}

		if (isThereTotem()) {
			int gSlot = pullSlot(568);
			DrawUtils::drawItem(Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(gSlot), Vec2(pvpX + (lineWidth2 * scale + 1.f), pvpY + (lineWidth2 * scale - 1.f + testValYe / 2)), 1.f, scale, false);
			std::string yikes = std::to_string(countItem(568));
			DrawUtils::drawText(Vec2(pvpX + (lineWidth2 * scale + 4.f), pvpY + (lineWidth2 * scale + 7.f) + 20.f), &yikes, MC_Color(255, 255, 255), scale);
		}

		if (isThereGapples()) {
			int gSlot = pullSlot(259);
			DrawUtils::drawItem(Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(gSlot), Vec2(pvpX + (lineWidth2 * scale + 1.f), pvpY + (lineWidth2 * scale - 1.f)), 1.f, scale, false);
			std::string yikes = std::to_string(countItem(259));
			DrawUtils::drawText(Vec2(pvpX + (lineWidth2 * scale + 4.f), pvpY + (lineWidth2 * scale + 7.f)), &yikes, MC_Color(255, 255, 255), scale);
		}

		if (isThereEffect()) {
			int gSlot = pullSlot(508);
			DrawUtils::drawItem(Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(gSlot), Vec2(pvpX + (lineWidth2 * scale + 1.f) + testValYe / 2, pvpY + (lineWidth2 * scale - 1.f)), 1.f, scale, false);
			std::string yikes = std::to_string(countItem(426));
			DrawUtils::drawText(Vec2(pvpX + (lineWidth2 * scale + 4.f) + testValYe / 2, pvpY + (lineWidth2 * scale + 7.f)), &yikes, MC_Color(255, 255, 255), scale);
		}
		if (isThereObsidian()) {
			int gSlot = pullSlot(49);
			DrawUtils::drawItem(Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(gSlot), Vec2(pvpX + (lineWidth2 * scale + 1.f), pvpY + (lineWidth2 * scale - 1.f + testValYe / 2)), 1.f, scale, false);
			std::string yikes = std::to_string(countItem(49));
			DrawUtils::drawText(Vec2(pvpX + (lineWidth2 * scale + 4.f), pvpY + (lineWidth2 * scale + 7.f) + 20.f), &yikes, MC_Color(255, 255, 255), scale);
		}

	} else {
		// effects
		std::string effects = std::to_string(countItem(426));
		DrawUtils::drawText(Vec2(pvpX, pvpY), &std::string("Effects: " + effects), MC_Color(160, 255, 0), scale);
		// totems
		std::string totems = std::to_string(countItem(568));
		DrawUtils::drawText(Vec2(pvpX, pvpY + 10.f * scale), &std::string("Totems: " + totems), MC_Color(255, 255, 130), scale);
		// Gapples
		std::string gapples = std::to_string(countItem(259));
		DrawUtils::drawText(Vec2(pvpX, pvpY + 20.f * scale), &std::string("Gapples: " + gapples), MC_Color(200, 200, 0), scale);
		// Crystals
		std::string crystals = std::to_string(countItem(637));
		DrawUtils::drawText(Vec2(pvpX, pvpY + 30.f * scale), &std::string("Crystals: " + crystals), MC_Color(215, 0, 235), scale);
		// Obsidians
		std::string obsidians = std::to_string(countItem(49));
		DrawUtils::drawText(Vec2(pvpX, pvpY + 40.f * scale), &std::string("Obsidian: " + obsidians), MC_Color(0.1f, 0.1f, 0.1f), scale);
	}
}

bool PvPResources::isThereTotem() {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		int itemIDC = 568;
		ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDC) {
			int itemCountC = itemToCount->count;
			mafs += itemCountC;
		}
	}
	if (mafs == 0) {
		return false;
	} else {
		return true;
	}
}

bool PvPResources::isThereObsidian() {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		int itemIDC = 49;
		ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDC) {
			int itemCountC = itemToCount->count;
			mafs += itemCountC;
		}
	}
	if (mafs == 0) {
		return false;
	} else {
		return true;
	}
}

bool PvPResources::isThereCrystal() {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		int itemIDC = 637;
		ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDC) {
			int itemCountC = itemToCount->count;
			mafs += itemCountC;
		}
	}
	if (mafs == 0) {
		return false;
	} else {
		return true;
	}
}

bool PvPResources::isThereGapples() {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		int itemIDC = 259;
	          ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDC) {
			int itemCountC = itemToCount->count;
			mafs += itemCountC;
		}
	}
	if (mafs == 0) {
		return false;
	} else {
		return true;
	}
}

bool PvPResources::isThereXp() {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		int itemIDC = 498;
		ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDC) {
			int itemCountC = itemToCount->count;
			mafs += itemCountC;
		}
	}
	if (mafs == 0) {
		return false;
	} else {
		return true;
	}
}

bool PvPResources::isThereEffect() {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		int itemIDC = 426;
		ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDC) {
			int itemCountC = itemToCount->count;
			mafs += itemCountC;
		}
	}
	if (mafs == 0) {
		return false;
	} else {
		return true;
	}
}

int PvPResources::countItem(int itemIDCount) {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDCount) {
			int itemCountC = itemToCount->count;
			mafs += itemCountC;
		}
	}
	return mafs;
	// mafs = 0;
}

int PvPResources::pullSlot(int itemIDPog) {
	int mafs = 0;
	for (int i = 0; i < 36; i++) {
		ItemStack* itemToCount = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemToCount->item != NULL && (*itemToCount->item)->itemId == itemIDPog) {
			return i;
		}
	}
}
