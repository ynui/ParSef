#ifndef _fanPage_h
#define _fanPage_h


#include <string.h>
#include <iostream>
#include "Member.h"
#include "Status.h"
using namespace std;

class fanPage
{
	char* name;
	status** statusList;
	member** fansList;
	int statusNum=0,fansNum=0, sizeOf_statusList, sizeOf_fansList;
public:
	fanPage(char* name);
	~fanPage();

	void addStatus(status* stat);
	void addFan(member* mmbr);
	
	void showEntity();
	void showAllStatus();
	void showAllFans();

	char* getName();
};

#endif // !_fanPage_h
