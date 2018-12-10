#define _CRT_SECURE_NO_WARNINGS


#include "facebook.h"


void main()
{
	int input = -1;
	facebook FB;


	while (input != 9) {
		FB.printManu();
		cin >> input;
		while (input < 1 || input >11)
		{
			cout << "Illegal input, try again: \n";
			cin.clear();
			cin.ignore();
			cin >> input;
		}
		switch (input)
		{
		case 1:
			FB.addMember();
			break;
		case 2:
			FB.addFanPage();
			break;
		case 3:
			FB.addStatus();
			break;
		case 4:
			FB.showAllStatuses();
			break;
		case 5:
			FB.makeFriendship();
			break;
		case 6:
			FB.addFanToPage();
			break;
		case 7:
			FB.showAllEntities();
			break;
		case 8:
			FB.showAllConnections();
			break;
		case 9:
			cout << "Goodbay!\n";
			break;
		case 10:
			FB.showAllFanPagesMemberSupports();
			break;
		case 11:
			FB.showLast10();
			break;
		}
	}
}