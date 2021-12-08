#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  // TODO: initialize struct if needed
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->root = p->nil;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory

  free(t);
}

void _right_rotation(rbtree * tree, node_t * x){
    node_t * y = x->left;
    x->left = y->right;
    if(y->right != tree->nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}


void _left_rotation(rbtree * tree, node_t * x){
    node_t * y = x->right;
    x->right = y->left;
    if(y->left != tree->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


void _rb_insert_fixup(rbtree *t, node_t *curr){
    while(curr->parent->color == RBTREE_RED){
        if(curr->parent == curr->parent->parent->left){
            node_t * uncle = curr->parent->parent->right;
            // case 1
            if(uncle->color == RBTREE_RED){
                curr->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                curr = curr->parent->parent;
            }
            else {
                // case 2
                if(curr == curr->parent->right){
                    curr = curr->parent;
                    _left_rotation(t, curr);
                }
                // case 3
                curr->parent->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                _right_rotation(t, curr->parent->parent);
            }
        }
        else{  
            node_t * uncle = curr->parent->parent->left;
            // case 1
            if(uncle->color == RBTREE_RED){
                curr->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                curr = curr->parent->parent;
            }
            else {
                if(curr == curr->parent->left){
                    curr = curr->parent;
                    _right_rotation(t, curr);
                }
                curr->parent->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                _left_rotation(t, curr->parent->parent);
            }
        }
    }
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert
    
    // make new_node
    node_t * new_node = (node_t *)calloc(1, sizeof(node_t));
    node_t * y = t->nil;
    node_t * x = t->root;
    while(x != t->nil){
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    new_node->parent = y;
    if(y == t->nil){
        t->root = new_node;
    }
    else if(key < y->key){
        y->left = new_node;
    }
    else {
        y->right = new_node;
    }

    new_node->key = key;
    new_node->color = RBTREE_RED;
    new_node->left = new_node->right = t->nil;

    _rb_insert_fixup(t, new_node);
    t->root->color = RBTREE_BLACK;
    return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}