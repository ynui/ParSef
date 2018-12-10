#define _CRT_SECURE_NO_WARNINGS
#include "FanPage.h"


fanPage::fanPage(char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	fansList = nullptr;
	statusList = nullptr;
}
fanPage::~fanPage()
{
	delete[] name;
	delete[] fansList;
}

void fanPage::addStatus(status* stat)
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
void fanPage::addFan(member* mmbr)
{
	//extand the list's size if it's full/creating new list 
	if (!fansList)
	{
		sizeOf_fansList = 10;
		fansList = new member*[sizeOf_fansList];
	}
	if (sizeOf_fansList == fansNum)
	{
		member** temp = fansList;
		sizeOf_fansList *= 2;
		fansList = new member*[fansNum];
		memcpy(fansList, temp, sizeof(member*)*fansNum);
	}
	fansList[fansNum++] = mmbr;
}

void fanPage::showEntity()
{
		cout << "Fan Page name: " << name << endl;
}
void fanPage::showAllStatus()
{
	if (this->statusNum == 0)
		cout << this->name << " does not have any status yet\n";
	else
		for (int i = 0; i < this->statusNum; i++)
			this->statusList[i]->showData();
}
void fanPage::showAllFans()
{
	if (fansNum == 0)
		cout << this->name << " has no supporters yet!" << endl;
	for (int i = 0; i < this->fansNum; i++)
		this->fansList[i]->showEntity();
}

char* fanPage::getName()
{
	return this->name;
}
