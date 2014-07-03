#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Tokenizer.h"
#include "LinkedList.h"
#include "StringChecker.h"
#include "StringChanger.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	LinkedList<string>* address = new LinkedList<string>();
	LinkedList<string>* address2 = new LinkedList<string>();
	char str[2000];
	fstream file_In("X:\\Matthew\\CSUN\\Final Project\\EditMemberList\\Membership.csv", ios::in);
	fstream file_Out("X:\\Matthew\\CSUN\\Final Project\\EditMemberList\\Output2.csv", ios::out);
	int lineCount = 1;
	bool inList = false;
	int count = 1;
	while(!file_In.eof()) 
	{
		count++;
		string token = "";
		file_In.getline(str, 2000);
		Tokenizer* t = new Tokenizer(str, ',');
		string location = t->getToken(13);
		if(lineCount == 1)
		{
			while(t->hasMoreTokens()) 
			{
				file_Out << t->nextToken();
			}
			file_Out << endl;
			lineCount++;
		}
		else 
		{
			if(address->Search(t->getToken(13)))
			{
				inList = true;	
			}
			
			else
			{
				address->InsertTail(t->getToken(13));
				string formatedAddress = "";
				StringChanger* strChange = new StringChanger();
				//CHANGE EVERYTHING TO CAPS
				string temp = strChange->specialToCapsKeepFirstSevenNumbers(t->getToken(13));
				delete strChange;
				StringChecker* strChecker = new StringChecker();
				Tokenizer* adrsChecker = new Tokenizer(temp);
				//TOKENIZE ADDRESS AND CHECK EACH INDIVIDUAL TOKEN
				while(adrsChecker->hasMoreTokens())
				{
					string special = ",";
					if(adrsChecker->getToken(1) == "1" || adrsChecker->getToken(1) == "1/2" || adrsChecker->getToken(1) == "12")
					{
					}
					else if(strChecker->isNumeric(adrsChecker->getToken(1)))
					{
					}
					else if(adrsChecker->getToken(1) == "S," || adrsChecker->getToken(1) == "J," || adrsChecker->getToken(1) == "B,"
						|| adrsChecker->getToken(1) == "C," || adrsChecker->getToken(1) == "E," || adrsChecker->getToken(1) == "Z,"
						|| adrsChecker->getToken(1) == "F," || adrsChecker->getToken(1) == "Y," || adrsChecker->getToken(1) == "A,"
						|| adrsChecker->getToken(1) == "L," || adrsChecker->getToken(1) == "L,")
					{	
					}
					else if(adrsChecker->getToken(1) == "APT")
					{
					}
					else if(adrsChecker->getToken(1) == "P")
					{
					}
					else if(adrsChecker->getToken(1) == "O")
					{
					}
					else if(adrsChecker->getToken(1) == "BOX")
					{
					}
					else if(adrsChecker->getToken(1) == "GUEST,")
					{
					}
					else if(adrsChecker->getToken(1) == "MAILBOX")
					{
					}
					else if(adrsChecker->getToken(1) == "STREET," || adrsChecker->getToken(1) == "STREET ,") 
					{
						formatedAddress = formatedAddress + " ST";
					}
					else if(adrsChecker->getToken(1) == "DRIVE," || adrsChecker->getToken(1) == "DRIVE ,") 
					{
						formatedAddress = formatedAddress + " DR";
					}
					else if(adrsChecker->getToken(1) == "PLACE," || adrsChecker->getToken(1) == "PLACE ,")
					{
						formatedAddress = formatedAddress + " PL";
					}
					else if(adrsChecker->getToken(1) == "CANYON," || adrsChecker->getToken(1) == "CANYON ,")
					{
						formatedAddress = formatedAddress + " CYN";
					}
					else if(adrsChecker->getToken(1) == "AVENUE," || adrsChecker->getToken(1) == "AVENUE ,")
					{
						formatedAddress = formatedAddress + " AVE";
					}
					else if(adrsChecker->getToken(1) == "WAY," || adrsChecker->getToken(1) == "WAY ,")
					{
						formatedAddress = formatedAddress + " WY";
					}
					else if(adrsChecker->getToken(1) == "TRAIL," || adrsChecker->getToken(1) == "TRAIL ,")
					{
						formatedAddress = formatedAddress + " TR";
					}
					else if(adrsChecker->getToken(1) == ",")
					{
						formatedAddress = formatedAddress + ",";
						while(adrsChecker->hasMoreTokens())
						{
							string noMore = adrsChecker->nextToken();
						}
					}
					else
					{	
						formatedAddress = formatedAddress + " " + adrsChecker->getToken(1);
					}
					string advanceNextToken = adrsChecker->nextToken();
				}
				delete strChecker;
				delete adrsChecker;
				if(!address2->Search(formatedAddress))
				{
					address2->InsertTail(formatedAddress);
					int tokenCount = 1;
					while(t->hasMoreTokens()) 
					{
						if(tokenCount == 13)
						{
							file_Out << formatedAddress;
							string discard = t->nextToken();
						}
						else
						{
							file_Out << t->nextToken();
						}
						tokenCount++;
					}
				}				
			}
			if(!inList)
			{
				file_Out << endl;
			}
			inList = false;
			delete t;
			t = NULL;
		}
	}
	file_In.close();
	address->Display();
	file_Out.close();
	cout <<endl;
	delete address;
	delete address2;

	string quit = "";
	cout << "Please hit <enter> to quit:>";
	getline(cin, quit);
	return 0;
}





		