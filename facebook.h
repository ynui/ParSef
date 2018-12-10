#ifndef _facebook_h
#define _facebook_h


#include"Member.h"
#include"FanPage.h"
#include"Status.h"

class fanPage;
class member;

class facebook
{
	member** memberList;
	fanPage** fanPageList;
	status** allStatusList;
	int memberNum = 0, fanPageNum = 0, statusNum = 0, memberArrSize, fanPageArrSize, statusArrSize;
public:
	facebook();
	~facebook();

	void printManu();
	void addMember();
	void addFanPage();
	void addStatus();
	void addFanToPage();
	void makeFriendship();

	void showAllEntities();
	void showAllStatuses();
	void showAllConnections();
	void showAllFanPagesMemberSupports();
	void showLast10();

	bool checkFanPageDuplicate(member* memberName, char* pageName);
	bool checkFriendshipDuplicate(member* memberName, char* otherName);
	bool isNameAlreadyExist(char* name,bool isMember);
	bool isDateOk(char name[]);

	int getMemberIndx(char* temp);
	int getFanPageIndx(char* temp);
	int getType();

	int stringToInt(char* date, int start);
};

#endif // !_facebook_h