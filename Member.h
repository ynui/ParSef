#ifndef _member_h
#define _member_h


//#include "Status.h"

class fanPage;
class status;

class member
{
	char* name;
	char birthday[9];//   dd.mm.yy
	member**  friendsList;
	status**  statusList;
	fanPage** fanPageList;
	int friendsNum = 0, statusNum = 0, fanPageNum = 0, sizeOf_statusList, sizeOf_friendsList, sizeOf_fanPageList;
public:
	member(char* name,char* birthday);
	~member();
	
	void addStatus(status* stat);
	void addFanPage(fanPage* page);
	void makeFriendship(member* other);

	void showEntity();
	void showAllStatus();
	void showAllfriends();
	void showAllFanPages();
	
	bool areFriends(member* m1, member* m2);

	char* getName();
	int getFanPageNum();
	int getFriendsNum();
	int getStatusNum();
	member** getFriendsList();
	fanPage** getFanPageList();

};

#endif // !_member_h