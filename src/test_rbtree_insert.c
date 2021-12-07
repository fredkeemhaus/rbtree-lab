#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void left_rotate(rbtree* t, node_t* x) {
    node_t* y = x->right;
 
    x->right = y->left;
 
    if (x->right != t->nil)
        x->right->parent = x;
 
    y->parent = x->parent;
 
    if (x->parent == t->nil)
        t->root = y;

    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree* t, node_t* y) {
    node_t* x = y->right;

    y->right = x->left;
 
    if (x->right != t->nil)
        x->right->parent = x;
        
    y->parent = x->parent;

    if (x->parent == t->nil)
        t->root = y;
 
    else if (x == x->parent->left)
        x->parent->left = y;

    else    x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}
 

void rbtree_fixup(rbtree* t, node_t* z) {
  // 1. 부모의 색이 RED일 때 실행
  while(z->parent->color == RBTREE_RED){
    // 부모가 조부모의 왼쪽 노드일때부터 시작한다.
    if (z->parent == z->parent->parent->left){ 
      node_t* uncle = z->parent->parent->right;  // 삼촌
      
      // 2. Recolor
      if (uncle->color == RBTREE_RED){
        z->parent->parent->color = RBTREE_RED;
        z->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;

        z = z->parent->parent;  // z의 조부모가 규칙에 어긋나면 fixup 다시 실행(while문)
      }

      // 3. Restructure
      else{
        // triangle
        if (z == z->parent->right){
          z = z->parent;
          left_rotate(t, z);
        }

        // line
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }

    // 부모가 조부모의 오른쪽 노드일 때
    else{
      node_t* uncle = z->parent->parent->left;

      // Recolor
      if (uncle == RBTREE_RED){
        z->parent->parent->color = RBTREE_RED;
        z->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;

        z = z->parent->parent;
      }

      // Reconstruct
      else{
        if (z == z->parent->right){
          z = z->parent;
          right_rotate(t, z);
        }

        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }

    }
  }
  
  // 4. 만약 새 노드가 ROOT라면.
  t->root->color = RBTREE_BLACK;
}


/*
  insert(key) : key 값을 가진 노드를 트리에 삽입한다.
  1. 이진탐색트리와 동일하게 새 노드를 트리에 삽입한다.
  2. 새 노드의 색을 RED로 칠한다.
  3. RBT의 규칙에 어긋날 시, 규칙을 지키기 위해 트리를 fixup한다.
*/
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t* newNode = malloc(sizeof(node_t));
  newNode->key = key;

  // 새 노드의 부모 노드를 찾는다.
  node_t* parent = t->nil;
  node_t* curr = t->root;

  while (curr != t->nil){
    parent = curr;
    if (key < curr->key)
      curr = curr->left;
    else
      curr = curr->right;
  }
  newNode->parent = parent;

  // 새 노드의 자리를 찾아 삽입한다(원래 있던 자릴 대체하진 않는다).
  if (parent == t->nil)
    t->root = newNode;
  else if (key < parent->key)
    parent->left = newNode;
  else
    parent->right = newNode;
  
  newNode->left = t->nil;
  newNode->right = t->nil;
  
  // 새 노드의 색을 RED로 칠하고 트리를 fixup한다.
  newNode->color = RBTREE_RED;
  rbtree_fixup(t, newNode);  // 인자가 이게 맞나?

  return t->root;
}

void _rbtree_print(rbtree * tree, node_t * curr, int tab_count) {
    if(curr == tree->nil){
        return;
    }
    if(tab_count == 1){
        printf("root: %d(%s)\n", curr->key, curr->color == RBTREE_BLACK ? "black" : "red");
    }
    if(curr->left != tree->nil){
        for(int i = 0; i < tab_count * 4; i++){
            printf(" ");
        }
        printf("left: %d(%s)\n", curr->left->key, curr->left->color == RBTREE_BLACK ? "black" : "red");
        _rbtree_print(tree, curr->left, tab_count+1);
    }
    if(curr->right != tree->nil){
        for(int i = 0; i < tab_count * 4; i++){
            printf(" ");
        }
        printf("right: %d(%s)\n", curr->right->key, curr->right->color == RBTREE_BLACK ? "black" : "red");
        _rbtree_print(tree, curr->right, tab_count+1);
    }
}


void rbtree_print(rbtree * tree) {
    if(tree->root == tree->nil){
        printf("empty tree.\n");
        return;
    }
    _rbtree_print(tree, tree->root, 1);
    printf("\n");
}


void rbtree_insert_test(){
    printf("rbtree insertion test!\n");
    rbtree* rbt = new_rbtree();
    printf("test1\n");
    rbtree_insert(rbt, 11);
    rbtree_insert(rbt, 2);
    rbtree_insert(rbt, 14);
    rbtree_insert(rbt, 1);
    rbtree_insert(rbt, 7);
    rbtree_insert(rbt, 15);
    rbtree_insert(rbt, 5);
    rbtree_insert(rbt, 8);
    rbtree_insert(rbt, 4);
    rbtree_print(rbt);
    delete_rbtree(rbt);

    rbtree* rbt2 = new_rbtree();
    printf("test2\n");
    rbtree_insert(rbt2, 1);
    rbtree_insert(rbt2, 2);
    rbtree_insert(rbt2, 3);
    rbtree_insert(rbt2, 4);
    rbtree_insert(rbt2, 5);
    rbtree_insert(rbt2, 6);  
    rbtree_insert(rbt2, 7);
    rbtree_insert(rbt2, 8);
    rbtree_print(rbt2);
    delete_rbtree(rbt2);

    rbtree* rbt3 = new_rbtree();
    printf("test3\n");
    rbtree_insert(rbt3, 8);
    rbtree_insert(rbt3, 7);
    rbtree_insert(rbt3, 6);
    rbtree_insert(rbt3, 5);
    rbtree_insert(rbt3, 4);
    rbtree_insert(rbt3, 3);  
    rbtree_insert(rbt3, 2);
    rbtree_insert(rbt3, 1);
    rbtree_print(rbt3);
    delete_rbtree(rbt3);
}


int main(int argc, char *argv[]) {
    rbtree_insert_test();
    /*
    // rbtree insertion test!
    // test1
    root: 7(black)
        left: 2(red)
            left: 1(black)
            right: 5(black)
                left: 4(red)
        right: 11(red)
            left: 8(black)
            right: 14(black)
                right: 15(red)
								*
    // test2
    root: 4(black)
        left: 2(red)
            left: 1(black)
            right: 3(black)
        right: 6(red)
            left: 5(black)
            right: 7(black)
                right: 8(red)

    // test3
    root: 5(black)
        left: 3(red)
            left: 2(black)
                left: 1(red)
            right: 4(black)
        right: 7(red)
            left: 6(black)
            right: 8(black)
  */  
}

