#include <iostream>

using namespace std;

class List {
public:
    List( ) : head( NULL ){ ;}
    ~List( ) { ;}
	void operator()( const int nValue );
	int& operator[]( const int nValue ) const;
	void operator<<( const int size ) const;
    int length;
private:
    class Node {
    public:
		Node( int insert ) : value( insert ), next( NULL ){ ;}
		~Node( ){ ;}
        Node *next;
        int value;
    private:
		friend class List;
	};
    Node *head;
};

void List::operator()( const int nValue ) {
	if( this->head == NULL ) {
		Node *insert = new Node( nValue );
		this->head = insert;
	} else {
		Node *slider = this->head;
		Node *insert = new Node( nValue );
		while( slider->next != NULL ) {
			slider = slider->next;
		}
		slider->next = insert;
	}
}

int& List::operator[]( const int nValue ) const {
	int ret = -1;
	int &value = ret;
	//*
	if( this->head == NULL ) {
		return value;
	} else {
		Node *slider = this->head;
		while( slider != NULL && slider->value != nValue) {
			slider = slider->next;
		}
		if( slider == NULL ) {
			return value;
		} else {
			value = slider->value;
			return value;
		}
	}
}

void List::operator<<( int size ) const {
	int count = 0;
	if( this->head != NULL ) {
		Node *slider = this->head;
		cout << "["; while( slider != NULL && count <= size ) {
			cout << slider->value << ((slider->next==NULL) ? "" : ", ");
			slider = slider->next;
		} cout << "]" <<endl;
	}
}

int main( int argc, char **argv ) {
	List L;
	L(10);
	L(9);
	L(8);
	L(7);
	L(6);
	L(5);
	L(4);
	L(3);
	L(2);
	L(1);
	L<<10;
	cout << L[10] << endl;
	return( 0 );
}