#include "rb_tree.h"

#include <stdlib.h>

rb_tree *rb_tree_create()
{
  rb_tree *rbt = malloc(sizeof(rb_tree));
  rbt->root_ = 0;
  return rbt;
}

void rec_delete_tree(rb_tree_node **rbtn)
{
  if (!rbtn || !(*rbtn)) {
    return;
  } else {
    rec_delete_tree(&(*rbtn)->left_);
    rec_delete_tree(&(*rbtn)->right_);
    free(*rbtn);
    (*rbtn) = 0;
  }
}

void rb_tree_destroy(rb_tree **rbt)
{
  if (!rbt || !(*rbt)) {
    return;
  }
  rec_delete_tree(&((*rbt)->root_));
  free(*rbt);
  (*rbt) = 0;
}

rb_tree_node *rb_tree_node_create(void *key, void *val)
{
  rb_tree_node *rbtn = malloc(sizeof(rb_tree_node));
  rbtn->key_ = key;
  rbtn->val_ = val;
  rbtn->left_ = 0;
  rbtn->right_ = 0;
  rbtn->color_ = NONE;
  return rbtn;
}

