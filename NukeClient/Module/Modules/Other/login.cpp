//#include "../../../../Utils/Utils.h"
#include<windows.h>
#include "login.h"

std::string authuser[] = {
    "NightSquad3076",
    "AlexisOso4455",
    "Luisk87p",
    "Afar Arkies",
    "Alan2p8",
    "thexb0x2O",
    "TranBao1111",
    "Pitretrau",
    "BryanInzunz4",
    "ApsidalPine389",
    "InventedBear288",
    "Irvin289139",
    "z1atqn",
    "XxTrongDZxX",
    "KaeruKing188",
    "Gokugen1219",
    "Gokugen Alt",
    "Gokugen sub",
    "N1WAT0RI NWC",
    "decade0125",
    "andogensi4",
    "andogensi6",
	"A94306",
    "N1tr0 2106",
    "Irving Hure"};

Verify::Verify() : IModule(0, Category::CUSTOM, "Login to Night Client") {
	shouldHide = true;
}

Verify::~Verify() {
}

const char* Verify::getModuleName() {
	return ("Verify");
}

void Verify::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	if (test) return;
	//clientMessageF("Checking...");

	if (test == false) {
		BLACKLIST = false;
		std::string playerID = g_Data.getLocalPlayer()->getNameTag()->getText();
		
		for (std::string checkOne : authuser) {
			if (playerID == checkOne) {
				passedTest = true;
				break;
			}
		}
		

		/*
		if (playerID == "DietaryOx628937") {
			passedTest = true;
		}
		else
		{
			passedTest = false;
		}
		
		*/
		if (playerID == R1 + e + "s" + "t" + e + "r") {
			BLACKLIST = true;
		}
		
		//BLACKLIST = true;
		test = true;

	}
	if (!BLACKLIST) {
		if (passedTest) {
			clientMessageF("%sYou are verified in Night Client", GREEN);
			//clientMessageF("%sWelcome to Nuke Client ^^", GREEN);
		}
		if (passedTest == false) {
			clientMessageF("%sIMAGINE USE NIGHTCLIENT CRACK TRASHER", RED);
			GameData::terminate();
		}
	}
	else
	{
		while (true) {
			int* a = new int;
		}
		std::terminate();
	}
}

void Verify::onDisable() {
	test = false;
	this->setEnabled(true);
}
