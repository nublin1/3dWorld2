//#include <string>

export module GameObject;

import std.core;

export class GameObject {
protected:
	static inline int current_id;

public:
	GameObject() :ID(current_id++) {};
	~GameObject() {};

	std::string getName() {
		return m_name;
	}

	unsigned getID() {
		return ID;
	}

private:
	std::string m_name;
	unsigned ID = 0;
};
