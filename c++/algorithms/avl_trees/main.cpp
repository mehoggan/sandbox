#include <cstdlib>
#include <iostream>

class tree
{
public:
  tree() :
    _root(NULL)
  {}

  ~tree()
  {
    rec_delete(_root);
  }

  void insert(int key);
  void print();

  class node
  {
  public:
    node (int key) :
      _key(key),
      _balance(0),
      _parent(NULL),
      _left(NULL),
      _right(NULL)

    {}

    enum AttachAs { Error, LeftHookUp, RightHookUp };
    enum Rotate { LeftRotation, RightRotation };

    node *rotate(Rotate direction ,AttachAs side);
    AttachAs attach_as();
    void adjust_balance();
    void set_left_child();
    void set_right_child();
    void rebalance_family(node *parent, node *current, node *child);

  private:
    friend class tree;
    int _key;
    int _balance;
    node *_parent;
    node *_left;
    node *_right;
  };

private:
  node *_root;
  void rec_print(node *curr);
  node *rec_insert(int key, node *curr);
  void rec_delete(node *curr);
};

void tree::rec_delete(node *curr)
{
  if (curr != NULL) {
    rec_delete(curr->_left);
    rec_delete(curr->_right);
    delete curr;
  }
}

void tree::print()
{
  if (_root == NULL) {
    return;
  }
  rec_print(_root);
}

void tree::rec_print(tree::node *curr)
{
  if (curr != NULL) {
    rec_print(curr->_left);
    std::cout << "(" << ((curr->_parent != NULL) ? curr->_parent->_key : -1) << ") "
      << curr->_key << " (" << curr->_balance << ") " << std::endl;
    rec_print(curr->_right);
  }
}

void tree::insert(int key)
{
  if (_root == NULL) {
    _root = new tree::node(key);
  } else {
    _root = rec_insert(key, _root);
  }
}

tree::node *tree::rec_insert(int key, tree::node *curr)
{
  if (curr == NULL) {
    curr = new node(key);
  } else {
    if (key < curr->_key) {
      curr->_balance++;
      curr->_left = rec_insert(key, curr->_left);
      curr->_left->_parent = curr;
    } else if (key > curr->_key) {
      curr->_balance--;
      curr->_right = rec_insert(key, curr->_right);
      curr->_right->_parent = curr;
    }

    /* AVL Tree Balance */
    if (curr->_balance == -2) { // Right tree unbalanced
      if (curr->_right && curr->_right->_balance == -1) { // Right right
        curr = curr->rotate(tree::node::LeftRotation, curr->attach_as());
      }
      if (curr->_right && curr->_right->_balance == 1) { // Right left
        curr = curr->_right->rotate(tree::node::RightRotation, curr->_right->attach_as());
        curr = curr->rotate(tree::node::LeftRotation, curr->attach_as());
      }
    }
    if (curr->_balance == 2) { // Left tree unbalanced
      if (curr->_left && curr->_left->_balance == 1) { // Left left
        curr = curr->rotate(tree::node::RightRotation, curr->attach_as());
      }
      if (curr->_left && curr->_left->_balance == -1) { // Left right
        curr = curr->_left->rotate(tree::node::LeftRotation, curr->_left->attach_as());
        curr = curr->rotate(tree::node::RightRotation, curr->attach_as());
      }
    }
  }
  return curr;
}

void tree::node::rebalance_family(node *parent, node *current, node *child)
{
  if (parent && parent->_balance < 0) {
    parent->_balance++;
  } else if (parent && parent->_balance > 0) {
    parent->_balance--;
  }

  if (current && current->_balance < 0) {
    current->_balance++;
  } else if (current && current->_balance > 0) {
    current->_balance--;
  }

  if (child && child->_balance < 0) {
    child->_balance++;
  } else if (child && child->_balance > 0) {
    child->_balance--;
  }
}

tree::node *tree::node::rotate(tree::node::Rotate direction, tree::node::AttachAs side)
{
  tree::node *return_node = NULL;

  /*
   * The nodes we know upfront
   */
  tree::node *hook_up_to = _parent;
  tree::node *rotate = this;

  /*
   * We need to find out which case we are in
   * before we can assign the orphan - the cases
   * being a left or right rotation (see below
   * for right child)
   */
  tree::node *orphan = NULL;

  if (direction == tree::node::LeftRotation) {
    /*
     * On any left rotate we need the right child
     * and its left child which will become an orphan
     * while moving nodes around
     */
    tree::node *right_child = rotate->_right;
    orphan = right_child->_left;


    /*
     * Start by hooking up the right child
     * to this nodes parent. We store a pointer
     * to this in rotate so as not to lose it
     */
    if (side == tree::node::LeftHookUp) {
      hook_up_to->_left = right_child;
    }
    if (side == tree::node::RightHookUp) {
      hook_up_to->_right = _right;
    }
    _right->_parent = hook_up_to;


    /* Next we hook up the orphaned child to take the
     * place of the previous previous right child
     * that just took the place of this node in the tree
     */
    rotate->_right = orphan;
    if (orphan != NULL) {
      orphan->_parent = rotate;
    }

    /*
     * Last move in a left rotation is to make this node
     * the left child of its previous right child
     */
    right_child->_left = rotate;
    rotate->_parent = right_child;

    rebalance_family(hook_up_to, this, right_child);
    return_node = right_child;
  }

  /*
   * Right rotation case
   */
  if (direction == tree::node::RightRotation) {
    /*
     * On any right rotate we need the left child
     * and its right child which will become an orphan
     * while moving nodes around
     */
    tree::node *left_child = rotate->_left;
    orphan = left_child->_right;


    /*
     * Start by hooking up the left child
     * to this nodes parent. We store a pointer
     * to this in rotate so as not to lose it
     */
    if (side == tree::node::LeftHookUp) {
      hook_up_to->_left = left_child;
    }
    if (side == tree::node::RightHookUp) {
      hook_up_to->_right = left_child;
    }
    left_child->_parent = hook_up_to;

    /* Next we hook up the orphaned child to take the
     * place of the previous previous left child
     * that just took the place of this node in the tree
     */
    rotate->_left = orphan;
    if (orphan != NULL) {
      orphan->_parent = rotate;
    }

    /*
     * Last move in a right rotation is to make this node
     * the right child of its previous left child
     */
    left_child->_right = rotate;
    rotate->_parent = left_child;

    rebalance_family(hook_up_to, this, left_child);
    return_node = left_child;
  }
  return return_node;
}

tree::node::AttachAs tree::node::attach_as()
{
  if (_parent && _parent->_right == this) {
    return tree::node::RightHookUp;
  } else if (_parent && _parent->_left == this) {
    return tree::node::LeftHookUp;
  }
  return tree::node::Error;
}

int main(int argc, char *argv[])
{
  tree *t = new tree();
  // Root
  t->insert(32);

  // Left
  //t->insert(24);
  //t->insert(16);
  t->insert(8);

  // Right
  t->insert(64);
  t->insert(128);
  t->insert(256);

  t->print();
  delete t;
}
