#ifndef _TREE_PRIVATE_H
#define _TREE_PRIVATE_H

#include <stdlib.h>
#include "tree.h"
#include "entry.h"

struct treeNode {
  //char *val;
  struct entry_t *entry;
  struct treeNode *left;
  struct treeNode *right;
};

//Cria nó vazio
struct treeNode *create_node();

//Destroí o nó
struct treeNode *destroy_node(struct treeNode *node);

//Devolve a altura
int tree_maxHeigth(struct treeNode *node);

struct tree_t {
  struct treeNode *root;
  int size;
};

#endif
