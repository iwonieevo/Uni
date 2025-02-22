#pragma once
#include <iostream>
#include <string>
using std::cout, std::cin, std::string, std::getline;

class Player
{
private:
	string _nick;
	int _level;
	float _x;
	float _y;
	
public:
	Player() {
		cout << "\nDEFAULT CONSTRUCTOR";
		_nick = "Bot";
		_level = 0;
		_x = 0;
		_y = 0;
	}

	Player(string nick, int level, float x, float y)
		: _nick(nick)
		, _level(level)
		, _x(x)
		, _y(y)
	{
		cout << "\nPAREMETRIZED CONSTRUCTOR";
	}

	~Player() {
		cout << "\nDESTRUCTOR " << _nick;
	}

	void save_method(void) {
		cout << "\nInput nick: ";
		getline(cin, _nick);
		cout << "\nInput level: ";
		cin >> _level;
		cout << "\nInput position x: ";
		cin >> _x;
		cout << "\nInput position y: ";
		cin >> _y;
	}
	void print_method(void) const{
		cout << "\nNick: " << _nick << "\nLevel: " << _level << "\nPosition x: " << _x << "\nPosition y: " << _y;
	}

	void set_nick(string nick) {
		_nick = nick;
	}

	void set_level(int level) {
		_level = level;
	}

	void set_x(float x) {
		_x = x;
	}

	void set_y(float y) {
		_y = y;
	}

	string get_nick(void) const {
		return _nick;
	}

	int get_level(void) const {
		return _level;
	}

	float get_x(void) const {
		return _x;
	}

	float get_y(void) const {
		return _y;
	}
};

