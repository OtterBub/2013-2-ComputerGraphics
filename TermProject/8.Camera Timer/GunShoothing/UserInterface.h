#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Util.h"
#include "CallBackFunction.h";

// UserInterface Class Define
#define UI UserInterface::Instance()

// UserInterface Class
class UserInterface {
private:

	int m_capacity;
	int m_score;

	UserInterface(const UserInterface&);
	UserInterface operator=(const UserInterface&);

	UserInterface()
	{
		m_capacity = 0;
		m_score = 0;
	}

	~UserInterface() {
	}

public:
	
	static UserInterface& Instance() {
		static UserInterface instance;
		return instance;
	}
	
	void draw();
	void update();
};

#endif //USERINTERFACE_H