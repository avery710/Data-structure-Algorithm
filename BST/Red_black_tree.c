#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int key;
    int color; // 1-red, 0-black
    struct node* parent; // parent
    struct node* left; // left child
    struct node* right; // right child
}node;

node* newNode(int key){
    node* N = malloc(sizeof(node));

    N -> key = key;
    N -> color = 1; // mark as red first
    N -> parent = NULL;
    N -> left = NULL;
    N -> right = NULL;

    return N;
}

// global variable
node* ROOT = NULL;

node* insert_BST(node* cur, node* temp){
    // if the tree is empty, return the new node
    if (cur == NULL){
        return temp;
    }

    // otherwise recur down the tree
    if (temp -> key < cur -> key){
        cur -> left = insert_BST(cur -> left, temp);
        cur -> left -> parent = cur; // record the parent node
    }
    else if (temp -> key > cur -> key){
        cur -> right = insert_BST(cur -> right, temp);
        cur -> right -> parent = cur;
    }

    return cur;
}

void left_rotate(node* temp){
    node* right = temp -> right;

    // Step 1 : 處理right的左子樹，丟給temp
    temp -> right = right -> left;

    // 雙向設定，從child指向parent
    if (temp -> right){
        temp -> right -> parent = temp;
    }

    // Step 2 : 設定right的父母(根據temp的父母)
    right -> parent = temp -> parent;

    // 雙向設定，從parent指向child(分三種情況)
    if (!temp -> parent){
        ROOT = right;
    }
    else if (temp == temp -> parent -> left){
        temp -> parent -> left = right;
    }
    else {
        temp -> parent -> right = right;
    }

    // Step 3 : 把right的左子樹更新為temp
    right -> left = temp;

    // Step 4 : 最後把temp的parent更新為right
    temp -> parent = right;
}

void right_rotate(node* temp){
    node* left = temp -> left;

    // step 1
    temp -> left = left -> right;
    if (temp -> left){
        temp -> left -> parent = temp;
    }

    // step  2
    left -> parent = temp -> parent;
    if (!temp -> parent){
        ROOT = left;
    }
    else if (temp == temp -> parent -> left){
        temp -> parent -> left = left;
    }
    else {
        temp -> parent -> right = left;
    }

    // step 3
    left -> right = temp;
    // step 4
    temp -> parent = left;
}

// fix up
void fix_up(node* cur){
    node* parent = NULL;
    node* grandparent = NULL;

    // cur node is not root & red-red conflict -> continue fixing up
    while ((cur != ROOT) && (cur -> color == 1) && (cur -> parent -> color == 1)){
        parent = cur -> parent;
        grandparent = cur -> parent -> parent;

        // Case A : left side
        if (parent = grandparent -> left){
            node* uncle = grandparent -> right;

            // Case A-1 : uncle is red -> recolor
            if (uncle != NULL && uncle -> color == 1){
                grandparent -> color = 1;
                parent -> color = 0;
                uncle -> color = 0;
                cur = grandparent;
            }
            // else uncle is black
            else {
                // Case A-2 : uncle is black, cur is right child of parent -> LR rotation
                if (parent -> right == cur){
                    left_rotate(parent);
                    cur = parent;
                    parent = cur -> parent;
                }

                // Case A-3 : uncle is black, cur is left child of parent -> LL rotation
                right_rotate(grandparent);
                int t = parent -> color;
                parent -> color = grandparent -> color;
                grandparent -> color = t;
                cur = parent;
            }
        }
        // Case B : right side
        else {
            node* uncle = grandparent -> left;

            // Case B-1 : uncle is red -> recolor
            if (uncle != NULL && uncle -> color == 1){
                grandparent -> color = 1;
                parent -> color = 0;
                uncle -> color = 0;
                cur = grandparent;
            }
            // else uncle is black
            else {
                // case B-2 : uncle is black, cur is left child of parent -> RL rotation
                if (parent -> left == cur){
                    right_rotate(parent);
                    cur = parent;
                    parent = cur -> parent;
                }

                // case B-3 : uncle is black, cur is right child of parent -> RR rotation
                left_rotate(grandparent);
                int t = parent -> color;
                parent -> color = grandparent -> color;
                grandparent -> color = t;
                cur = parent;
            }
        }
    }

    root -> color = 0;
}

// left most child
node* successor(node* n){
    node* temp = n;

    while (temp -> left != NULL){
        temp = temp -> left;
    }

    return temp;
}

node* BST_replace(node* n){
    // when the node has 2 children
    if (n -> left != NULL && n -> right != NULL){
        return successor(n -> right);
    }

    // leaf
    if (n -> left == NULL && n -> right == NULL){
        return NULL;
    }

    // only one child
    if (n -> left != NULL){
        return n -> left;
    }
    else {
        return n -> right;
    }
}

void fix_double_black(node* n){

}

void delete_node(node* delete){
    node* replace = BST_replace(delete);

    bool bothBLACK = (delete -> color == 0) && ((replace == NULL) || (replace -> color == 0));
    node* parent = delete -> parent;

    // the node to be deleted is leaf (has no child)
    if (replace == NULL){
        if (replace == ROOT){
            ROOT = NULL;
        }
        else {
            if (bothBLACK){
                // both nodes are black, and DELETE is leaf
                fix_double_black(delete);
            }

            // delete the leaf node
            if (delete == parent -> left){
                parent -> left == NULL;
            }
            else {
                parent -> right == NULL;
            }
        }
        return;
    }

    // if DELETE has one child
    if (replace != NULL){
        if (delete == ROOT){
            delete -> key = replace -> key;
            delete -> left = delete -> right = NULL;
        }
        // Detach v(DELETE) from tree and move u(REPLACE) up
        else {
            if (delete == parent -> left){
                parent -> left = replace;
            }
            else {
                parent -> right = replace;
            }

            replace -> parent = parent;

            if (bothBLACK){
                fix_double_black(replace);
            }
            /*else {
                replace -> color = 1;
            }*/

        }
        return;
    }

    // if the node has 2 children, switch two nodes
    int temp;
    delete -> key = replace -> key;
    replace -> key = temp;
    delete_node(delete);
}

int main(){
    ROOT = newNode(0);

}