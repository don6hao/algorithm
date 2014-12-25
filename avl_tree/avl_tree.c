/*
 * AVL TREE
 */
#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

static void left_rotation(tree_pointer *parent);
static void right_rotation(tree_pointer *parent);
void list_insert(list_head_pointer list_head, tree_pointer *tree_node);
list_pointer list_remove(list_head_pointer list_head);

list_pointer list_remove(list_head_pointer list_head)
{
    if (NULL == list_head || NULL == list_head->head){
        return NULL;
    }
    list_pointer tmp = list_head->head;
    if (tmp->next == NULL){
        list_head->head = NULL;
        return tmp;
    }
    list_pointer prev = tmp;

    while(1){
        if (NULL == tmp->next){
            prev->next = NULL;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return tmp;
}


void list_insert(list_head_pointer list_head, tree_pointer *tree_node)
{
    list_pointer node = (list_pointer)calloc(1, sizeof(struct list_node));
    if (NULL == node){
        printf("calloc error!\n");
        return;
    }
    node->data = (void **)(tree_node);
    node->next = NULL;

    list_pointer head = list_head->head;
    if (NULL == head){
        list_head->head = node;
    }else{
        list_pointer tmp = head;
        while(NULL != tmp){
            if(NULL == tmp->next){
                tmp->next = node;
                break;
            }
            tmp = tmp->next;
        }
    }

    return;
}

void avl_print(tree_pointer parent)
{
    if (NULL == parent)
        return;
    avl_print(parent->left_child);
    avl_print(parent->right_child);
    printf("%d\n", parent->data.key);

    return;
}

int main()
{
    /*create a avl tree*/
    /*element ele[4] = {{10}, {9}, {8}, {7}};*/
    element ele[] = {{30}, {20}, {4}, {2}, {9}, {3}, {15}, {5}, {10}};
    int size = sizeof(ele)/sizeof(int);
    tree_pointer parent = NULL;
    while(size > 0){
        avl_insert(&parent, ele[--size]);
    }

    printf("post order:\n");
    avl_print(parent);
    printf("++++++++++++++++++++\n");
    /*search a key in avl tree */

    /* insert a tree_node in avl tree */

    /* delete a tree_node in avl_treee */


    return 0x00;
}

static void right_rotation(tree_pointer *parent)
{
    tree_pointer child = (*parent)->right_child;
    tree_pointer grand_child = NULL;

    if (-1 == child->bf){
        printf("2222222222222222\n");
        (*parent)->right_child = child->left_child;
        child->left_child = (*parent);
        (*parent)->bf = 0x00;
        (*parent) = child;
    }else if (1 == child->bf){
        printf("111111111111111111\n");
        grand_child = child->left_child;
        (*parent)->right_child = grand_child->left_child;
        child->left_child = grand_child->right_child;
        grand_child->left_child = (*parent);
        grand_child->right_child = child;
        switch(grand_child->bf){
            case -1: /* RLR */
                (*parent)->bf = 1;
                child->bf = 0x00;
                break;
            case 1: /* RLL */
                (*parent)->bf = 0x00;
                child->bf = -1;
                break;
            case 0: /* RL */
                (*parent)->bf = 0x00;
                child->bf = 0x00;
                break;
        }
        grand_child->bf = 0x00;
        (*parent) = grand_child;
    }

    return;
}

static void left_rotation(tree_pointer *parent)
{
    tree_pointer child = (*parent)->left_child;
    tree_pointer grand_child = NULL;

    if (0x01 == child->bf){
        /* LL rotation */
        (*parent)->left_child = child->right_child;
        child->right_child = (*parent);
        (*parent) = child;
        (*parent)->bf = 0;
    }else if (-1 == child->bf){
        /* LR rotation */
        grand_child = child->right_child;
        (*parent)->left_child = grand_child->right_child;
        child->right_child =  grand_child->left_child;
        grand_child->left_child = child;
        grand_child->right_child = (*parent);
        switch(grand_child->bf){
            case -1:  /* LRR */
                child->bf = 0x01;
                (*parent)->bf = 0x00;
                break;
            case 0x01: /* LRL */
                child->bf = 0x00;
                (*parent)->bf = -1;
                break;
            case 0x00: /* LR */
                child->bf = 0x00;
                (*parent)->bf = 0x00;
                break;

        }
        grand_child->bf = 0x00;
        (*parent) = grand_child;
    }
    return;
}

void do_rotation(tree_pointer *tp)
{
    switch((*tp)->bf){
        case 0x00:
            ((*tp)->flag == RIGHT_WEIGHT)?((*tp)->bf = -1):((*tp)->bf = 1);
            break;
        case 0x01:
            ((*tp)->flag == RIGHT_WEIGHT)?((*tp)->bf = 0x00):(left_rotation(tp));
            break;
        case -1:
            ((*tp)->flag == RIGHT_WEIGHT)?(right_rotation(tp)):((*tp)->bf = 0x00);
            break;
        default:
            printf("balance factor was abnormal!\n");
            break;
    }

    return;
}

int avl_insert(tree_pointer *parent, element x)
{
    struct list_head head = {NULL};

    tree_pointer leaf_node = (tree_pointer)calloc(1, sizeof(struct tree_node));
    if (NULL == leaf_node){
        printf("calloc error!\n");
        return FALSE;
    }
    leaf_node->bf = 0x00;
    leaf_node->data = x;
    leaf_node->right_child = NULL;
    leaf_node->left_child = NULL;
    leaf_node->flag = -1;

    tree_pointer *tmp_pointer = parent;
    while(NULL != *tmp_pointer){
        /* insert tree_pointer into tnlist */
        list_insert(&head, tmp_pointer);
        if (x.key < (*tmp_pointer)->data.key){
            (*tmp_pointer)->flag = LEFT_WEIGHT;
            tmp_pointer = &((*tmp_pointer)->left_child);
        }else{
            (*tmp_pointer)->flag = RIGHT_WEIGHT;
            tmp_pointer = &((*tmp_pointer)->right_child);
        }
    }
    *tmp_pointer = leaf_node;

    while(NULL != head.head){
        list_pointer list_node = list_remove(&head);
        do_rotation((tree_pointer *)(list_node->data));
    }

    return TRUE;
}


