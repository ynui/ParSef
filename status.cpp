#define _CRT_SECURE_NO_WARNINGS

#include "Status.h"

status::status() 
{
	this->type = 0;
	this->data = NULL;
	this->owner_member = NULL;
	this->owner_fanPage = NULL;
}
status::~status()
{
	delete[] data;
}

status* status::createStatus(member* name, int type)
{
	char stat[500];
	this->type = type;
	if (type == 1)
	{
		cin.ignore();
		cout << "Enter text to status:\n";
		cin.getline(stat, 500);
	}
	else if (type == 2)
	{
		strcpy(stat, "This is a PICTURE status");//default for picture type status
	}
	else
	{
		strcpy(stat, "This is a VIDEO status");//default for video type status
	}
	this->data = new char[strlen(stat) + 1];
	strcpy(this->data, stat);

	time(&this->publishTime);
	this->owner_member = name;
	return this;
}
status* status::createStatus(fanPage* name, int type)
{
	time_t publishTime;
	status* newStatus = new status();
	char stat[500];
	this->type = type;
	if (type == 1)
	{
		cin.ignore();
		cout << "Enter text to status:\n";
		cin.getline(stat, 500);
	}
	else if (type == 2)
	{
		strcpy(stat, "This is a PICTURE status");//default for picture type status
	}
	else
	{
		strcpy(stat, "This is a VIDEO status");//default for video type status
	}
	this->data = new char[strlen(stat) + 1];
	strcpy(this->data, stat);
	time(&this->publishTime);
	this->owner_fanPage = name;
	return this;
}

void status::showData()
{
	cout <<"Publish time: " << ctime(&this->publishTime) << "Data:\n" << this->data << endl;
}

member* status::getOwner()
{
	return this->owner_member;
}