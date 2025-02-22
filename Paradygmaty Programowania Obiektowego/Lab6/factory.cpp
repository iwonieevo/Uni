#include "factory.h"
#include "CharacterGuild.h"
#include <iostream>
using std::cout, std::cin, std::string;

void factory_main(void) {
	string characterType;
	CharacterGuild* Tavern = nullptr;

	cout << "Enter character type (Rogue/Druid/Cleric): ";
	cin >> characterType;

	if (characterType == "Rogue") {
		Tavern = new RogueGuild();
	}

	else if (characterType == "Druid") {
		Tavern = new DruidGuild();
	}

	else if (characterType == "Cleric") {
		Tavern = new ClericGuild();
	}

	else {
		cout << "\nInvalid character type. Shutting down the app...\n";
		return;
	}

	Character* Hero = Tavern->createCharacter();
	cout << Hero->showInfo();
	Hero->set_hp(100);
	Hero->set_main_stat(15);
	cout << Hero->showInfo();

	delete Tavern;
	delete Hero;
}