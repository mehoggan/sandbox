#ifndef RB_TREE_H
#define RB_TREE_H

typedef enum Color {
  RED,
  BLACK,
  NONE,
} Color;

typedef struct rb_tree_node {
  void *key_;
  void *val_;
  struct rb_tree_node *left_;
  struct rb_tree_node *right_;
  Color color_;
} rb_tree_node;

typedef struct rb_tree {
  rb_tree_node *root_;
} rb_tree;

/**
 * @brief Creates a red black tree on the heap and returns a pointer to the
 * user to be free'd by the user. You may call rb_tree_destroy to free the
 * memory as well.
 */
extern rb_tree *rb_tree_create();

/**
 * @brief Free the memory allocated by rb_tree_create. This will recursivly
 * destroy each rb_tree_node inserted into a tree returned by and operated on
 * by any of the functions in this module.
 */
extern void rb_tree_destroy(rb_tree **rbt);

/**
 * @brief Creates a node to be inserted into a red black tree. This
 * rb_tree_node should be freed by client code manually or by deleting a node
 * from the tree.
 */
extern rb_tree_node *rb_tree_node_create(void *key, void *val);

#endif
