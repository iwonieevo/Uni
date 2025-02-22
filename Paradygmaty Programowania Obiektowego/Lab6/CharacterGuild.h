#pragma once

#include <string>
using std::string, std::to_string;

class Character
{
private:
	int hp_ = 1;
	int main_stat_ = 1;
public:
	virtual string showInfo(void) = 0;
	virtual ~Character() {};

	int get_hp(void) const{
		return hp_;
	}

	int get_main_stat(void) const {
		return main_stat_;
	}

	void set_hp(int x) {
		hp_ = x;
	}

	void set_main_stat(int x) {
		main_stat_ = x;
	}
};

class Rogue : public Character
{
public:
	string showInfo(void) override {
		return "\n\nRogue - proficiency in daggers.\nHealth points = " + to_string(this->get_hp()) + "\nDexterity = " + to_string(this->get_main_stat()) + "\n";
	}
};

class Druid : public Character
{
public:
	string showInfo(void) override {
		return "\n\nDruid - proficiency in staffs.\nHealth points = " + to_string(this->get_hp()) + "\nInteligence = " + to_string(this->get_main_stat()) + "\n";
	}
};

class Cleric : public Character
{
public:
	string showInfo(void) override {
		return "\n\nCleric - proficiency in maces.\nHealth points = " + to_string(this->get_hp()) + "\nKnowledge = " + to_string(this->get_main_stat()) + "\n";
	}
};

class CharacterGuild
{
public:
	virtual Character* createCharacter(void) = 0;
	virtual ~CharacterGuild() {};
};

class RogueGuild : public CharacterGuild
{
	Character* createCharacter(void) override{
		return new Rogue();
	}
};

class DruidGuild : public CharacterGuild
{
	Character* createCharacter(void) override {
		return new Druid();
	}
};

class ClericGuild : public CharacterGuild
{
	Character* createCharacter(void) override {
		return new Cleric();
	}
};