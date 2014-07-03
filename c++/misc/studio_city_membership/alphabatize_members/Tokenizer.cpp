#include <iostream>
#include <string>
#include <iomanip>
#include "Tokenizer.h"
#include "LinkedList.h"

Tokenizer::Tokenizer() {
}

Tokenizer::Tokenizer(string tokenize) 
{
	chainOtOkens = new LinkedList<string>();
	toBeTokenized = tokenize;
	word = 0;
	
	int count1 = 0;
	int num = 1;
	while(count1 < toBeTokenized.size()) 
	{
		string token = "";
		int count2 = count1;
		while(tokenize[count2] != ' ' && count2 < toBeTokenized.size()) 
		{
			token = token + tokenize[count2];
			count1++;
			count2++;
		}
		count1++;
		chainOtOkens->InsertTail(token);		
	}
	word = 0;
}

Tokenizer::Tokenizer(string tokenize, char tokenStop) 
{
	chainOtOkens = new LinkedList<string>();
	toBeTokenized = tokenize;
	word = 0;
	
	int count1 = 0;
	int num = 1;
	//cout << "TOKENIZING WITH " << tokenStop << endl;
	//system("PAUSE");
	while(count1 < toBeTokenized.size()) 
	{
		string token = "";
		int count2 = count1;
		while(tokenize[count2] != tokenStop && count2 < toBeTokenized.size()) 
		{
			token = token + tokenize[count2];
			count1++;
			count2++;
		}
		//cout << "FIRST TOKEN IS: " << token << endl;
		//system("PAUSE");
		if(count2 < toBeTokenized.size()) 
		{
			token = token + toBeTokenized[count2];
			//cout << "FIRST TOKEN IS NOW: " << token << endl;
			//system("PAUSE");
		}
		count1++;
		while(count1 < toBeTokenized.size() && tokenize[count1] == ' ') 
		{
			count1++;
		}
		chainOtOkens->InsertTail(token);
	}
	word = 0;
}

Tokenizer::~Tokenizer() 
{
	delete chainOtOkens;
}

int Tokenizer::getWord() 
{
	return word;
}

string Tokenizer::nextToken() 
{
	string s = "";
	if(chainOtOkens == NULL || chainOtOkens->getHead() == NULL) 
	{
	}
	else 
	{
		s = chainOtOkens->getHead()->getData();
		chainOtOkens->DeleteHead();
	}
	return s;
}

bool Tokenizer::hasMoreTokens() 
{
	bool ret = false;
	if(chainOtOkens->getHead() == NULL) 
	{
	}
	else 
	{
		ret = true;
	}
	return ret;
}

string Tokenizer::getToken(int tokenNumber) 
{
	string ret = "";
	if(chainOtOkens->getHead() == NULL) 
	{
	}
	else if(tokenNumber > 0 && tokenNumber <= chainOtOkens->getSize())
	{	
		Node<string>* slider = chainOtOkens->getHead();
		int getToken = 1;
		while(getToken != tokenNumber) 
		{
			slider = slider->getNext();
			getToken++;
		}
		ret = slider->getData();		
	}
	return ret;
}




