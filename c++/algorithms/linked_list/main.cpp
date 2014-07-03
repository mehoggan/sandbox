/*
* Assignment: Get middle node in linked list.
* Requirements:
* 1) You don’t have a pointer to the tail
* 2) This is a singly linked list
* 3) This is to be a generic list
* 4) This is to be production code
*/

#include <cstdlib>
#include <assert.h>
#include <iostream>

/*!
* Internal structure of a list
* a node contains a key and a pointer to
* another node in the list
*/
template <typename key_type>
struct node
{
public:
node(key_type key) :
  m_Key(key),
  m_Next(NULL)
{}
key_type m_Key;
node * m_Next;
};

/*!
* Linked list structure. A list that
* contains 0 or more nodes of type
* key_type
*/
template <typename key_type>
class list
{
public:
  list() :
    root(NULL)
  {}

/*!
 * dtor -- deletes all dynamically allocated nodes created
* by inserting into list
*/
~list();

/*!
 * Delete list -- deletes all nodes in list
 */
void delete_list(node<key_type> *current);
/*!
 * Provide a key and this method will create a node
 * and insert the node with the provided key into the list
 * the new key will be inserted at end of list. Complexity
 * of method O(n)
 */
void insert_node(key_type key);
/*!
 * Provide a key and this method will look for that node
 * if the node is present it will remove it from list. If the key
 * does not exist in the list NULL is returned. Complexity
 * is worst case O(n)
 */
void delete_node(key_type key);

/*!
 * This method will get the length of the list then
 * it will scan the list till it has reach that length and return
 * a const pointer to this node.
 */
const node<key_type> *middle_node();
/*!
 * This method gets the length of the list and returns it
 * a list with 0 items in it has length 0, 1 item length 1
 * etc.
 */
unsigned int length();

 /*!
  * Reverse a list
  */
 void reverse(node<key_type> *prev, node<key_type> *current);

 node<key_type> *root;
};

template <typename key_type>
list<key_type>::~list()
{
delete_list(root);
}

template <typename key_type>
void list<key_type>::delete_list(node<key_type> *current)
{
if (current == NULL) {
  return;
}
delete_list(current->m_Next);
delete current;
}

template <typename key_type>
const node<key_type> *list<key_type>::middle_node()
{
if (root == NULL) {
  return NULL;
}
unsigned int middle = length()/2;
unsigned int loc = 0;
node<key_type> *slider = root;
while (loc != middle) {
  slider = slider->m_Next;
  ++loc;
}
return slider;
}

template <typename key_type>
unsigned int list<key_type>::length()
{
if (root == NULL) {
  return 0;
}
node<key_type> *find = root;
unsigned int node_count = 0;
while (find->m_Next != NULL) {
  node_count++;
  find = find->m_Next;
}
return node_count;
}

template <typename key_type>
void list<key_type>::insert_node(key_type key)
{
node<key_type> *insert = new node<key_type>(key);
if (root == NULL) {
  root = insert;
} else {
  node<key_type> * finder = root;
  while (finder->m_Next != NULL) {
    finder = finder->m_Next;
  }
  finder->m_Next = insert;
}
}

template <typename key_type>
void list<key_type>::reverse(node<key_type> *prev, node<key_type> *current)
{
 if (current == NULL) {
   root = prev;
   return;
 }
 reverse(current, current->m_Next);
 current->m_Next = prev;
}

int main(int argc, char *argv[]) {
 list<int> insert;
 for (int i = 1; i <= 10; ++i) {
    insert.insert_node(i);
 }
 std::cout << insert.middle_node()->m_Key << std::endl;
 insert.reverse(NULL, insert.root);
 for (node<int> *p = insert.root; p != NULL; p = p->m_Next) {
   std::cout << p->m_Key << " ";
 }
 std::cout << std::endl << insert.middle_node()->m_Key << std::endl;
 assert(insert.middle_node()->m_Key == 6 && "Failure to find middle node correctly");
}

