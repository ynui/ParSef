#include "textColor.h"
#include "facebook.h"

facebook::facebook()
{
	memberArrSize = 10, fanPageArrSize = 10, statusArrSize = 10;
	memberList = new member*[memberArrSize];
	fanPageList = new fanPage*[fanPageArrSize];
	allStatusList = new status*[statusArrSize];

}
facebook::~facebook()
{
		for (int i = 0; i < memberNum; i++)
			delete memberList[i];
		delete[] memberList;

		for (int i = 0; i < fanPageNum; i++)
			delete fanPageList[i];
		delete[] fanPageList;

		for (int i = 0; i < statusNum; i++)
			delete allStatusList[i];
		delete[] allStatusList;
}

void facebook::printManu()
{
	setTextColorBlue();
	cout << "|||||||||||||||||||||||||||||||||||||||\n1.Add member\n2.Add fan page\n3.Add status (to member/fan pgae)\n4.show all statuses(of a member/fan page)\n5.Make friendship\n6.Add fan to page\n7.Show all registered entities\n8.Show all friends/fans\n9.Exit\n******Extra******\n10.Show all Fan Pages a member supports\n11.Show last 10 statuses of a member's friends\n|||||||||||||||||||||||||||||||||||||||\n";
	setTextColorWhite();
}
void facebook::addMember()
{
	bool isValid = false;
	char tempName[50];
	char tempBday[50];
	//extand the list's size if it's full/creating new list 
	if (memberNum == memberArrSize)
	{
		member** temp = memberList;
		memberArrSize *= 2;
		memberList = new member*[memberArrSize];
		memcpy(memberList, temp, sizeof(member*)*memberArrSize);
	}
	cin.ignore();
	cout << "Enter name: ";
	cin.getline(tempName, 50);
	isValid = isNameAlreadyExist(tempName, true);
	while (!isValid)
	{
		cout << "This name already exist. choose a different name: ";
		cin.getline(tempName, 50);
		isValid = isNameAlreadyExist(tempName, true);
	}
	cout << "Enter birthday (DD.MM.YY): ";
	cin.getline(tempBday, 50);
	isValid = isDateOk(tempBday);
	while (!isValid)
	{
		cout << "Birthday format inputted is illegal, enter bitrhday again: ";
		cin.clear();
		cin.getline(tempBday, 50);
		isValid = isDateOk(tempBday);
	}
	member* newMember = new member(tempName, tempBday);
	this->memberList[memberNum++] = newMember;
	cout << "The new member " << tempName << " was added succsfully to the system!" << endl;
}
void facebook::addFanPage()
{
	bool isValid = false;
	char tempName[50];
	//extand the list's size if it's full/creating new list 
	if (fanPageNum == fanPageArrSize)
	{
		fanPage** temp = fanPageList;
		fanPageArrSize *= 2;
		fanPageList = new fanPage*[fanPageArrSize];
		memcpy(fanPageList, temp, sizeof(fanPage*)*fanPageArrSize);
	}
	cin.ignore();
	cout << "Enter Fan Page name: ";
	cin.getline(tempName, 50);
	isValid = isNameAlreadyExist(tempName, false);
	while (!isValid)
	{
		cout << "This name already exist. choose a different name: ";
		cin.getline(tempName, 50);
		isValid = isNameAlreadyExist(tempName, false);
	}
	fanPage* newFanPage = new fanPage(tempName);
	this->fanPageList[fanPageNum++] = newFanPage;
	cout << "The new Fan Page " << tempName << " was added succsfully to the system!" << endl;
}
void facebook::addStatus()
{
	//extand the list's size if it's full/creating new list 
	if (statusNum == statusArrSize)
	{
		status** temp = allStatusList;
		statusArrSize *= 2;
		allStatusList = new status*[statusArrSize];
		memcpy(allStatusList, temp, sizeof(status*)*statusArrSize);
	}
	status* newStatus = new status();
	int input, memberIndx, fanPageIndx;
	cout << "What do you want to add status to?\n1.Member\n2.Fan Page\nEnter 1 or 2: ";
	cin >> input;

	//get legal input
	while (input != 1 && input != 2)
	{
		cout << "Illegal input. try again: ";
		cin.clear();
		cin.ignore();
		cin >> input;
	}
	if (input == 1 && !memberNum)
	{
		cout << "There are no members in facebook yet!\n";
		return;
	}
	if (input == 2 && !fanPageNum)
	{
		cout << "There are no Fan Pages in facebook yet!\n";
		return;
	}
	cin.ignore();
	char search[50];
	cout << "Enter name: ";
	cin.getline(search, 50);
	if (input == 1)
	{
		memberIndx = getMemberIndx(search);
		int statType = getType();
		newStatus = newStatus->createStatus(memberList[memberIndx], statType);
		memberList[memberIndx]->addStatus(newStatus);

	}
	else if (input == 2)
	{
		fanPageIndx = getFanPageIndx(search);
		int statType = getType();
		newStatus->createStatus(fanPageList[fanPageIndx], statType);
		fanPageList[fanPageIndx]->addStatus(newStatus);
	}
	this->allStatusList[statusNum++] = newStatus;
	cout << "New status was added to " << memberList[memberIndx]->getName() << " succesfully!" << endl;
}
void facebook::addFanToPage()
{
	if (memberNum == 0)
	{
		cout << "There are no members in the system yet!" << endl;
		return;
	}
	if (fanPageNum == 0)
	{
		cout << "There are no Fan Pages in the system yet!" << endl;
		return;
	}
	bool alreadyExist;
	char memberName[50], pageName[50];
	cin.ignore();
	cout << "Enter member name : ";
	cin.getline(memberName, 50);
	int memberIndx = getMemberIndx(memberName);
	cout << "Enter the Fan Page name for " << memberName << " to support: ";
	cin.getline(pageName, 50);
	int fanPageIndx = getFanPageIndx(pageName);
	if (alreadyExist = checkFanPageDuplicate(memberList[memberIndx], pageName))//check if fan is already supporting this fan page
	{
		cout << memberName << " is already supporting " << pageName << "!\n";
		return;
	}
	else
	{
		memberList[memberIndx]->addFanPage(fanPageList[fanPageIndx]);
		fanPageList[fanPageIndx]->addFan(memberList[memberIndx]);
	}
	cout << memberName << " is now supporting " << pageName << "!" << endl;

}
void facebook::makeFriendship()
{
	bool alreadyExist;
	cin.ignore();
	int member1indx, member2indx;
	char member1[50], member2[50];
	if (memberNum < 2)
	{
		if (memberNum == 1)
			cout << "There is only 1 member in facebook, cannot make friendship\n";
		else
			cout << "There are no members in facebook, cannot make friendship\n";
		return;
	}
	cout << "Enter name of a member: ";
	cin.getline(member1, 50);
	cout << "Enter name of another member to make friendship: ";
	cin.getline(member2, 50);
	while (!strcmp(member1, member2))
	{
		cout << "Cannot make friendship with the same member.\nTry a different member: ";
		cin.getline(member2, 50);
	}
	member1indx = getMemberIndx(member1);
	member2indx = getMemberIndx(member2);
	if (alreadyExist = checkFriendshipDuplicate(memberList[member1indx], memberList[member2indx]->getName()))
	{
		cout << member1 << " and " << member2 << " are already friends!\n";
		return;
	}
	else
	{
		memberList[member1indx]->makeFriendship(memberList[member2indx]);
		memberList[member2indx]->makeFriendship(memberList[member1indx]);
	}
	cout << member1 << " and " << member2 << " are now friends!" << endl;

}

void facebook::showAllEntities()
{
	if (this->memberNum == 0)
		cout << "Facebook has no members yet!\n";
	else
		cout << "Members:\n";
	for (int i = 0; i < this->memberNum; i++)
		memberList[i]->showEntity();
	if (this->fanPageNum == 0)
		cout << "Facebook has no Fan Pages yet!\n";
	else
		cout << "Fan Pages:\n";
	for (int i = 0; i < this->fanPageNum; i++)
		fanPageList[i]->showEntity();
}
void facebook::showAllStatuses()
{
	int input;
	cout << "Show status of:\n1.Member\n2.Fan Page\nEnter 1 or 2: ";
	cin >> input;
	//get legal input
	while (input != 1 && input != 2)
	{
		cout << "Illegal input. try again: ";
		cin.clear();
		cin.ignore();
		cin >> input;
	}

	char search[50];

	if (input == 1)
	{
		if (memberNum == 0)
		{
			cout << "There are no members in facebook yet!\n";
			return;
		}
		cin.ignore();
		cout << "Enter name: ";
		cin.getline(search, 50);
		int indx = getMemberIndx(search);
		memberList[indx]->showAllStatus();
	}
	else
	{
		if (fanPageNum == 0)
		{
			cout << "There are no Fan Pages in facebook yet!\n";
			return;
		}
		cin.ignore();
		cout << "Enter name: ";
		cin.getline(search, 50);
		int indx = getFanPageIndx(search);
		fanPageList[indx]->showAllStatus();
	}

}
void facebook::showAllConnections()
{
	int input;
	cout << "Show friends of:\n1.Member\n2.Fan Page\nEnter 1 or 2: ";
	cin >> input;
	while (input != 1 && input != 2)
	{
		cout << "Illegal input. try again: ";
		cin.clear();
		cin.ignore();
		cin >> input;
	}
	char search[50];
	if (input == 1)
	{
		if (memberNum == 0)
		{
			cout << "There are on members in the system yet!" << endl;
			return;
		}
		cin.ignore();
		cout << "Enter name: ";
		cin.getline(search, 50);
		int indx = getMemberIndx(search);
		memberList[indx]->showAllfriends();
	}
	else
	{
		if (fanPageNum == 0)
		{
			cout << "There are no members in the system yet!" << endl;
			return;
		}
		cin.ignore();
		cout << "Enter name: ";
		cin.getline(search, 50);
		int indx = getFanPageIndx(search);
		fanPageList[indx]->showAllFans();
	}

}
void facebook::showAllFanPagesMemberSupports()
{
	if (memberNum == 0)
	{
		cout << "There are no members in the system yet!" << endl;
		return;
	}
	char search[50];
	cin.ignore();
	cout << "Enter name: ";
	cin.getline(search, 50);
	int indx = getMemberIndx(search);
	memberList[indx]->showAllFanPages();
}
void facebook::showLast10()
{
	if (memberNum == 0)
	{
		cout << "There are no members in the system yet!" << endl;
		return;
	}
	int indx, counter = 0;
	char search[50];
	cin.ignore();
	cout << "Enter name: ";
	cin.getline(search, 50);
	indx = getMemberIndx(search);
	int size = statusNum;
	cout << "Last 10 statuses of " << memberList[indx]->getName() << "'s friends:\n";
	for (int i = size - 1; i >= 0 && counter < 10; i--)
	{
		if (memberList[indx]->areFriends(memberList[indx], allStatusList[i]->getOwner()))
		{
			cout << "Status by: " << allStatusList[i]->getOwner()->getName() << endl;
			allStatusList[i]->showData();
			counter++;
		}
	}
	if (counter == 0)
		cout << memberList[indx]->getName() << "'s friends did not add any status yet\n";
}

bool facebook::checkFanPageDuplicate(member* memberName, char* pageName)
{
	//checks if a member is trying to support a page it's already supporting
	fanPage** tempList = memberName->getFanPageList();
	int num = memberName->getFanPageNum();
	for (int i = 0; i < num; i++)
		if (!strcmp(pageName, tempList[i]->getName()))
			return true;
	return false;
}
bool facebook::checkFriendshipDuplicate(member* memberName, char* otherName)
{
	//checks if a member is already friends with a member
	member** tempList = memberName->getFriendsList();
	int num = memberName->getFriendsNum();
	for (int i = 0; i < num; i++)
		if (!strcmp(otherName, tempList[i]->getName()))
			return true;
	return false;
}
bool facebook::isNameAlreadyExist(char* name, bool isMember)
{
	//
	if (isMember)//check for member
	{
		for (int i = 0; i < memberNum; i++)
			if (strcmp(memberList[i]->getName(), name) == 0)
				return false;
	}
	else//check for fan page
	{
		for (int i = 0; i < fanPageNum; i++)
			if (strcmp(fanPageList[i]->getName(), name) == 0)
				return false;
	}
	return true;
}
bool facebook::isDateOk(char name[])
{
	//checks if a string is valid to the only form allowed: DD/MM/YY -> 0<DD<31,0<MM<12, 0<YY
	//the form of the string is known, usint const array values
	int len = strlen(name);
	if (len != 8)
		return false;
	//allows only XX/XX/XX or XX.XX.XX
	if (name[2] != '.' || name[5] != '.') {
		if (name[2] != '/' || name[5] != '/')
			return false;
	}

	int num;
	for (int i = 0; i < 9; i += 3)
	{
		num = stringToInt(name, i);
		switch (i)
		{
		case 0:
			if (num < 0 || num>31)
				return false;
			break;
		case 3:
			if (num < 0 || num>12)
				return false;
			break;
		case 6:
			if (num < 0)
				return false;
			break;
		}
	}
	return true;
}

int facebook::getMemberIndx(char* temp)
{
	//search for a member until ine is found
	while (1)
	{
		for (int i = 0; i < memberNum; i++)
		{
			if (!strcmp(temp, memberList[i]->getName()))
				return i;
		}
		cout << "Member not found, enter name again:\n";
		cin.getline(temp, 50);
	}

}
int facebook::getFanPageIndx(char* temp)
{
	//search for a fan page until one is found
	while (1)
	{
		for (int i = 0; i < fanPageNum; i++)
		{
			if (!strcmp(temp, fanPageList[i]->getName()))
				return i;
		}
		cout << "Fan Page not found, enter name again:\n";
		cin.getline(temp, 50);
	}
}
int facebook::getType()
{
	//gets the wanted status type
	int input;
	cout << "What type of status would you like to add?\n1.Text\n2.Picture\n3.Video\nChoose 1,2 or 3: ";
	cin >> input;
	while (input < 1 || input > 3)
	{
		cout << "Illegal input. try again: ";
		cin.clear();
		cin.ignore();
		cin >> input;
	}
	return input;
}


int facebook::stringToInt(char* date, int start)
{
	//convers 2 numbers to from string to int
	//checks first if it's numbers
	if (date[start] - '0'>9 || date[start] - '0' < 0)
		return -1;
	if (date[start + 1] - '0'>9 || date[start+1] - '0' < 0)
		return -1;
	int num = 0;
	num += date[start] - '0';
	num *= 10;
	num += date[start + 1] - '0';
	return num;
}