#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
#define TRUE 0x01
#define FALSE 0x00

#define LEFT_WEIGHT 0x02
#define RIGHT_WEIGHT 0x03

typedef struct tree_node *tree_pointer;

typedef struct{
    int key;
}element;

struct tree_node{
    tree_pointer left_child;
    element data;
    short int bf;
    short int flag;
    tree_pointer right_child;
};

typedef struct list_node *list_pointer;
struct list_node{
    list_pointer next;
    void **data;
};

typedef struct list_head *list_head_pointer;
struct list_head{
    list_pointer head;
};

int avl_insert(tree_pointer *parent, element x);
#endif
