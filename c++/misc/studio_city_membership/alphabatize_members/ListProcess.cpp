#include<iostream>
#include<string>
#include<fstream>
#include "Tokenizer.h"
#include "LinkedList.h"

using namespace std;

int main()
{
	LinkedList<string>* container1 = new LinkedList<string>();
	string line;
	ifstream myifile("streetsmhoggan.txt");
	while(! myifile.eof())
	{ 
			getline(myifile, line);
			Tokenizer* tobeTokened = new Tokenizer(line, '\t');
			string street_pre = tobeTokened->getToken(5);
			if(street_pre != "\t")
			{
				street_pre = street_pre.replace(street_pre.size() - 1, street_pre.size() - 1, " ");
			}
			else
			{
				street_pre = "";
			}
			string street_suf = tobeTokened->getToken(6);
			string street = street_pre + street_suf;
			if(street != "" || street != " ")
			{
				if(!container1->Search(street))
				{
					cout << "Adding street: " << street << endl;
					container1->InsertOrdered(street);
				}
			}
			delete tobeTokened;
	}
	cout << "OUT PUTTING" << endl;
	container1->Display();
	
	myifile.close();
	delete container1;
	
	string quit;
	cout << "Pleaes hit <enter> to quit:> ";
	getline(cin, quit);
}