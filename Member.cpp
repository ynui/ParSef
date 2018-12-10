#define _CRT_SECURE_NO_WARNINGS

#include "Member.h"
#include "FanPage.h"
#include "Status.h"
#include <string.h>

member::member(char* name, char* birthday)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	strcpy(this->birthday, birthday);
	friendsList = nullptr;
	statusList = nullptr;
	fanPageList = nullptr;
}
member::~member()
{
	delete[] statusList;
	delete[] friendsList;
	delete[] fanPageList;
	delete[] name;
}

void member::addStatus(status* stat)
{
	//extand the list's size if it's full/creating new list 
	if (!statusList)
	{
		sizeOf_statusList = 10;
		statusList = new status*[sizeOf_statusList];
	}
	if (sizeOf_statusList == statusNum)
	{
		status** temp = statusList;
		sizeOf_statusList *= 2;
		statusList = new status*[statusNum];
		memcpy(statusList, temp, sizeof(status*)*statusNum);
	}
	this->statusList[statusNum++] = stat;
}
void member::addFanPage(fanPage* page)
{
	//extand the list's size if it's full/creating new list 
	if (!fanPageList)
	{
		sizeOf_fanPageList = 10;
		fanPageList = new fanPage*[sizeOf_fanPageList];
	}
	if (sizeOf_fanPageList == fanPageNum)
	{
		fanPage** temp = fanPageList;
		sizeOf_fanPageList *= 2;
		fanPageList = new fanPage*[fanPageNum];
		memcpy(fanPageList, temp, sizeof(fanPage*)*fanPageNum);
	}
	fanPageList[fanPageNum++] = page;
}
void member::makeFriendship(member *other)
{
	//extand the list's size if it's full/creating new list 
	if (!friendsList)
	{
		sizeOf_friendsList = 10;
		friendsList = new member*[sizeOf_friendsList];
	}
	if (sizeOf_friendsList == friendsNum)
	{
		member** temp = friendsList;
		sizeOf_friendsList *= 2;
		friendsList = new member*[friendsNum];
		memcpy(friendsList, temp, sizeof(member*)*friendsNum);
	}
	this->friendsList[friendsNum++] = other;
}

void member::showEntity()
{
	if (this)
		cout << "Member name: " << this->name << ", Birthday: " << this->birthday << endl;
}
void member::showAllStatus()
{
	if (this->statusNum == 0)
		cout << this->name << " does not have any status yet\n";
	else
		cout << this->name << "'s statuses:\n";
	for (int i = 0; i < this->statusNum; i++)
		this->statusList[i]->showData();
}
void member::showAllfriends()
{
	if (this->friendsNum == 0)
		cout << this->name << " does not have any friends yet\n";
	else
		cout << this->name << "'s friends:\n";
	for (int i = 0; i < this->friendsNum; i++)
		this->friendsList[i]->showEntity();
}
void member::showAllFanPages()
{
	if (this->getFanPageNum() == 0)
		cout << this->name << " does not support any Fan Pages yet\n";
	else
		cout << this->name << "'s Fan Pages:\n";
	for (int i = 0; i < this->fanPageNum; i++)
		cout << this->fanPageList[i]->getName() << "\n";
}

bool member::areFriends(member* m1, member* m2)
{
	int size = m1->friendsNum;
	//checks if a member is in another's friends list
	for (int i = 0; i < size; i++)
		if (strcmp(m2->name, m1->friendsList[i]->name)==0)
			return true;
	return false;
}

char* member::getName()
{
	return this->name;
}
int member::getFanPageNum()
{
	return this->fanPageNum;
}
int member::getFriendsNum()
{
	return this->friendsNum;
}
int member::getStatusNum()
{
	return this->statusNum;
}
member** member::getFriendsList()
{
	return this->friendsList;
}
fanPage** member::getFanPageList()
{
	return this->fanPageList;
}