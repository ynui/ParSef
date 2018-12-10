#ifndef status_h
#define status_h


#include <time.h> 
#include <string.h>
#include <iostream>
using namespace std;

#include"Member.h"
#include"FanPage.h"

class fanPage;

class status {
	int type;
	time_t publishTime;
	char* data;
	member* owner_member;
	fanPage* owner_fanPage;
public:
	status();
	~status();

	status* createStatus(member* name, int type);
	status* createStatus(fanPage* name, int type);
	
	void showData();
	
	member* getOwner();
};

#endif // !status_h
