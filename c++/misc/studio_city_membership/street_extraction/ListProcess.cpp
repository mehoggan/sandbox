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
	ifstream myifile("Export_Output.txt");
	while(! myifile.eof())
	{ 
			getline(myifile, line);
			Tokenizer* tobeTokened = new Tokenizer(line, ',');
			string city = tobeTokened->getToken(5);
			if(city == "\"STUDIO CITY\"," || city == "\"NORTH HOLLYWOOD\"," || city == "\"VALLEY VILLAGE\"," 
				|| city == "\"UNIVERSAL CITY\"," || city == "\"TOLUCA LAKE\",")
			{
				string street = tobeTokened->getToken(12);
				if(street != "\" \",")
				{
					string dir = tobeTokened->getToken(11);
					street = dir + " " + street;
					if(street.at(1) != ' ')
					{
						street = street.replace(0, 1, "");
						street = street.replace(1, 2, "");
						street = street.replace(1, 2, " ");
					}
					else
					{
						street = street.replace(0, 6, "");
					}
					street = street.replace(street.size() - 2, street.size() - 1, "");
					if(!container1->Search(street))
					{
						container1->InsertOrdered(street);
					}
				}
			}
			delete tobeTokened;
	}
	container1->Display();
	
	myifile.close();
	delete container1;
	
	string quit;
	cout << "Pleaes hit <enter> to quit:> ";
	getline(cin, quit);
}