#include <iostream>
#include <string>
#include "TemplateContainers.h"

using namespace std;
using namespace containers;

int main(int argc, char* argv[]) {
	LinkedList<int>* chain = new LinkedList<int>();
	for(int x = 0; x < 20; x++) {
		container::chain->Insert(x);
	}
	
	chain->Display();
	
	chain->Delete(1);
	chain->Display();

	chain->Delete(19);
	chain->Display();

	chain->Delete(15);
	chain->Display();

	chain->Delete(2);
	chain->Display();

	chain->Delete(10);
	chain->Display();

	chain->Delete(16);
	chain->Display();

	chain->Delete(5);
	chain->Display();

	BST<int>* bst = new BST<int>();

	cout << "Inserting 10" << endl;
	bst->InsertLeaf(10);
	cout << "Inserting 5" << endl;
	bst->InsertLeaf(5);
	cout << "Inserting 15" << endl;
	bst->InsertLeaf(15);
	cout << "Inserting 1" << endl;
	bst->InsertLeaf(1);
	cout << "Inserting 9" << endl;
	bst->InsertLeaf(9);
	cout << "Inserting 11" << endl;
	bst->InsertLeaf(11);
	cout << "Inserting 20" << endl;
	bst->InsertLeaf(20);
	cout << "Inserting 6" << endl;
	bst->InsertLeaf(6);
	cout << "Inserting 14" << endl;
	bst->InsertLeaf(14);
	bst->Display();
	bst->Remove(9);
	bst->Display();
	bst->Remove(15);
	bst->Display();

	delete chain;
	delete bst;

	string quit = " ";
	cout << "Hit <enter> to quit";
	//cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, quit);
	return 0;
}