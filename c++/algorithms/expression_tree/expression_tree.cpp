#include <iostream>
#include <string>

using namespace std;

struct Node
{
    string value;
    Node *left;
    Node *right;
};

struct BST 
{
    BST( string expression );
    Node *root;
};

BST::BST( string expression ) 
{
    if( expression[0] != '(' && !isdigit( expression[0] ) ) return;
    cout << expression << " will be evaluated " << endl;
}

int main( int argc, char *argv[ ] )
{
    BST bst( "(1+2)*3" );
}
