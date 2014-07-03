#include <string>
#include "StringChanger.h"

StringChanger::StringChanger()
{
}

StringChanger::~StringChanger()
{
}

string StringChanger::specialToCapsKeepFirstSevenNumbers(string& address) 
{
	string address1 = "";
	for(int x = 0; x < address.size(); x++) 
	{
		if(x <= 7)
		{
			if(address[x] == '0') 
			{
				address1 = address1 + "0";
			}
			else if(address[x] == '1') 
			{
				address1 = address1 + "1";
			}		
			else if(address[x] == '2') 
			{
				address1 = address1 + "2";
			}
			else if(address[x] == '3') 
			{
				address1 = address1 + "3";
			}
			else if(address[x] == '4') 
			{
				address1 = address1 + "4";
			}
			else if(address[x] == '5') 
			{
				address1 = address1 + "5";
			}
			else if(address[x] == '6') 
			{
				address1 = address1 + "6";
			}
			else if(address[x] == '7') 
			{
				address1 = address1 + "7";
			}
			else if(address[x] == '8') 
			{
				address1 = address1 + "8";
			}
			else if(address[x] == '9') 
			{
				address1 = address1 + "9";
			}
			else if(address[x] == 'a') 
			{
				address1 = address1 + "A";
			}
			else if(address[x] == 'b') 
			{
				address1 = address1 + "B";
			}
			else if(address[x] == 'c') 
			{
				address1 = address1 + "C";
			}
			else if(address[x] == 'd') 
			{
				address1 = address1 + "D";
			}
			else if(address[x] == 'e') 
			{
				address1 = address1 + "E";
			}
			else if(address[x] == 'f') 
			{
				address1 = address1 + "F";
			}
			else if(address[x] == 'g') 
			{
				address1 = address1 + "G";
			}
			else if(address[x] == 'h') 
			{
				address1 = address1 + "H";
			}
			else if(address[x] == 'i') 
			{
				address1 = address1 + "I";
			}
			else if(address[x] == 'j') 
			{
				address1 = address1 + "J";
			}
			else if(address[x] == 'k') 
			{
				address1 = address1 + "K";
			}
			else if(address[x] == 'l') 
			{
				address1 = address1 + "L";
			}
			else if(address[x] == 'm') 
			{
				address1 = address1 + "M";
			}
			else if(address[x] == 'n') 
			{
				address1 = address1 + "N";
			}
			else if(address[x] == 'o') 
			{
				address1 = address1 + "O";
			}
			else if(address[x] == 'p') 
			{
				address1 = address1 + "P";
			}
			else if(address[x] == 'q') 
			{
				address1 = address1 + "Q";
			}
			else if(address[x] == 'r') 
			{
				address1 = address1 + "R";
			}
			else if(address[x] == 'S') 
			{
				address1 = address1 + "S";
			}
			else if(address[x] == 't') 
			{
				address1 = address1 + "T";
			}
			else if(address[x] == 'u') 
			{
				address1 = address1 + "U";
			}
			else if(address[x] == 'v') 
			{
				address1 = address1 + "V";
			}
			else if(address[x] == 'w') 
			{
				address1 = address1 + "W";
			}
			else if(address[x] == 'x') 
			{
				address1 = address1 + "X";
			}
			else if(address[x] == 'y') 
			{
				address1 = address1 + "Y";
			}
			else if(address[x] == 'z') 
			{
				address1 = address1 + "Z";
			}
			else if(address[x] == 'A') 
			{
				address1 = address1 + "A";
			}
			else if(address[x] == 'B') 
			{
				address1 = address1 + "B";
			}
			else if(address[x] == 'C') 
			{
				address1 = address1 + "C";
			}
			else if(address[x] == 'D') 
			{
				address1 = address1 + "D";
			}
			else if(address[x] == 'E') 
			{
				address1 = address1 + "E";
			}
			else if(address[x] == 'F') 
			{
				address1 = address1 + "F";
			}
			else if(address[x] == 'G') 
			{
				address1 = address1 + "G";
			}
			else if(address[x] == 'H') 
			{
				address1 = address1 + "H";
			}
			else if(address[x] == 'I') 
			{
				address1 = address1 + "I";
			}
			else if(address[x] == 'J') 
			{
				address1 = address1 + "J";
			}
			else if(address[x] == 'K') 
			{
				address1 = address1 + "K";
			}
			else if(address[x] == 'L') 
			{
				address1 = address1 + "L";
			}
			else if(address[x] == 'M') 
			{
				address1 = address1 + "M";
			}
			else if(address[x] == 'N') 
			{
				address1 = address1 + "N";
			}
			else if(address[x] == 'O') 
			{
				address1 = address1 + "O";
			}
			else if(address[x] == 'P') 
			{
				address1 = address1 + "P";
			}
			else if(address[x] == 'Q') 
			{
				address1 = address1 + "Q";
			}
			else if(address[x] == 'R') 
			{
				address1 = address1 + "R";
			}
			else if(address[x] == 'S') 
			{
				address1 = address1 + "S";
			}
			else if(address[x] == 'T') 
			{
				address1 = address1 + "T";
			}
			else if(address[x] == 'U') 
			{
				address1 = address1 + "U";
			}
			else if(address[x] == 'V') 
			{
				address1 = address1 + "V";
			}
			else if(address[x] == 'W') 
			{
				address1 = address1 + "W";
			}
			else if(address[x] == 'X') 
			{
				address1 = address1 + "X";
			}
			else if(address[x] == 'Y') 
			{
				address1 = address1 + "Y";
			}
			else if(address[x] == 'Z') 
			{
				address1 = address1 + "Z";
			}
			else if(address[x] == ',') 
			{
				address1 = address1 + ",";
			}
			else if(address[x] == ' ')
			{
				address1 = address1 + " ";
			}
		}
		else if(address[x] == 'a') 
		{
			address1 = address1 + "A";
		}
		else if(address[x] == 'b') 
		{
			address1 = address1 + "B";
		}
		else if(address[x] == 'c') 
		{
			address1 = address1 + "C";
		}
		else if(address[x] == 'd') 
		{
			address1 = address1 + "D";
		}
		else if(address[x] == 'e') 
		{
			address1 = address1 + "E";
		}
		else if(address[x] == 'f') 
		{
			address1 = address1 + "F";
		}
		else if(address[x] == 'g') 
		{
			address1 = address1 + "G";
		}
		else if(address[x] == 'h') 
		{
			address1 = address1 + "H";
		}
		else if(address[x] == 'i') 
		{
			address1 = address1 + "I";
		}
		else if(address[x] == 'j') 
		{
			address1 = address1 + "J";
		}
		else if(address[x] == 'k') 
		{
			address1 = address1 + "K";
		}
		else if(address[x] == 'l') 
		{
			address1 = address1 + "L";
		}
		else if(address[x] == 'm') 
		{
			address1 = address1 + "M";
		}
		else if(address[x] == 'n') 
		{
			address1 = address1 + "N";
		}
		else if(address[x] == 'o') 
		{
			address1 = address1 + "O";
		}
		else if(address[x] == 'p') 
		{
			address1 = address1 + "P";
		}
		else if(address[x] == 'q') 
		{
			address1 = address1 + "Q";
		}
		else if(address[x] == 'r') 
		{
			address1 = address1 + "R";
		}
		else if(address[x] == 's') 
		{
			address1 = address1 + "S";
		}
		else if(address[x] == 't') 
		{
			address1 = address1 + "T";
		}
		else if(address[x] == 'u') 
		{
			address1 = address1 + "U";
		}
		else if(address[x] == 'v') 
		{
			address1 = address1 + "V";
		}
		else if(address[x] == 'w') 
		{
			address1 = address1 + "W";
		}
		else if(address[x] == 'x') 
		{
			address1 = address1 + "X";
		}
		else if(address[x] == 'y') 
		{
			address1 = address1 + "Y";
		}
		else if(address[x] == 'z') 
		{
			address1 = address1 + "Z";
		}
		else if(address[x] == 'A') 
		{
			address1 = address1 + "A";
		}
		else if(address[x] == 'B') 
		{
			address1 = address1 + "B";
		}
		else if(address[x] == 'C') 
		{
			address1 = address1 + "C";
		}
		else if(address[x] == 'D') 
		{
			address1 = address1 + "D";
		}
		else if(address[x] == 'E') 
		{
			address1 = address1 + "E";
		}
		else if(address[x] == 'F') 
		{
			address1 = address1 + "F";
		}
		else if(address[x] == 'G') 
		{
			address1 = address1 + "G";
		}
		else if(address[x] == 'H') 
		{
			address1 = address1 + "H";
		}
		else if(address[x] == 'I') 
		{
			address1 = address1 + "I";
		}
		else if(address[x] == 'J') 
		{
			address1 = address1 + "J";
		}
		else if(address[x] == 'K') 
		{
			address1 = address1 + "K";
		}
		else if(address[x] == 'L') 
		{
			address1 = address1 + "L";
		}
		else if(address[x] == 'M') 
		{
			address1 = address1 + "M";
		}
		else if(address[x] == 'N') 
		{
			address1 = address1 + "N";
		}
		else if(address[x] == 'O') 
		{
			address1 = address1 + "O";
		}
		else if(address[x] == 'P') 
		{
			address1 = address1 + "P";
		}
		else if(address[x] == 'Q') 
		{
			address1 = address1 + "Q";
		}
		else if(address[x] == 'R') 
		{
			address1 = address1 + "R";
		}
		else if(address[x] == 'S') 
		{
			address1 = address1 + "S";
		}
		else if(address[x] == 'T') 
		{
			address1 = address1 + "T";
		}
		else if(address[x] == 'U') 
		{
			address1 = address1 + "U";
		}
		else if(address[x] == 'V') 
		{
			address1 = address1 + "V";
		}
		else if(address[x] == 'W') 
		{
			address1 = address1 + "W";
		}
		else if(address[x] == 'X') 
		{
			address1 = address1 + "X";
		}
		else if(address[x] == 'Y') 
		{
			address1 = address1 + "Y";
		}
		else if(address[x] == 'Z') 
		{
			address1 = address1 + "Z";
		}
		else if(address[x] == ',') 
		{
			address1 = address1 + ",";
		}
		else if(address[x] == ' ')
		{
			address1 = address1 + " ";
		}
	}
	return address1;
}