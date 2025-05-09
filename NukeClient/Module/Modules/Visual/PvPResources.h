#pragma once
#include "Module.h"
class PvPResources : public IModule {
public:
	PvPResources();
	~PvPResources();

	float scale = 1.f;
	float pvpX = 0.f;
	float pvpY = 250.f;
	bool text = true;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual bool isThereCrystal();
	virtual bool isThereGapples();
	virtual bool isThereTotem();
	virtual bool isThereXp();
	virtual bool isThereEffect();
	virtual bool isThereObsidian();
	// virtual bool isThereShield();
	int pullSlot(int itemIDPog);
	virtual int countItem(int itemIDCount);
};
