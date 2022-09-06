// Insert & delete & search (like BST)

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    int height;
}node;

node* newNode(int key){
    node* N = malloc(sizeof(node));
    N -> key = key;
    N -> left = NULL;
    N -> right = NULL;
    N -> height = 0;

    return N;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

// use recursion to get the height of tree
int height(node* N){
    if (N == NULL){
        return 0;
    }
    else {
        return 1 + max(height(N -> left), height(N -> right));
    }
}

// Right rotate
node* rightRotation(node* y){
    node* x= y -> left;
    node* xRight = x -> right;

    // rotation
    x -> right = y;
    y -> left = xRight;

    // update height
    y -> height = height(y);
    x -> height = height(x);

    return x;
}

// Left rotate
node* leftRotation(node* y){
    node* x = y -> right;
    node* xLeft = x -> left;

    // rotate
    x -> left = y;
    y -> right = xLeft;

    // update height
    y -> height = height(y);
    x -> height = height(x);

    return x;
}

// height of left tree - height of right tree
int getBalance(node* N){
    if (N == NULL){
        return 0;
    }
    return height(N -> left) - height(N -> right);
}

// 1. use recursion to insert the key
// 2. adjust layer by layer (during recursion)
node* insert(node* N, int key){
    // 1. BST insertion
    if (N == NULL){
        return newNode(key);
    }

    if (key > N -> key){
        N -> right = insert(N -> right, key); 
        // if the subtree needs rotate, it will return a new pointer of root
    }
    else if (key < N ->key){
        N -> left = insert(N -> left, key);
    }
    else { // equal keys are not availavle in BST
        return N;
    }

    // 2. Update the height of this node (after the rotation of its subtree)
    N -> height = height(N);

    // 3. check whether it is a balanced tree (needed rotation or not)
    int balance = getBalance(N);

    // left left 
    if (balance > 1 && key < N -> left -> key){
        return rightRotation(N);
    }
    // left right
    if (balance > 1 && key > N -> left -> key){
        N -> left = leftRotation(N -> left);
        return rightRotation(N);
    }
    // right right 
    if (balance < -1 && key > N -> right -> key){
        return leftRotation(N);
    }
    // right left 
    if (balance < -1 && key < N -> right -> key){
        N -> right = rightRotation(N -> right);
        return leftRotation(N);
    }

    // if rotation is not needed, return current node
    return N;

}

node* left_most(node* N){
    node* cur = N;

    while (cur -> left != NULL){
        cur = cur -> left;
    }

    return cur;
}

node* deleteNode(node* root, int key){
    // 1. perform standard BST delete
    if (root == NULL){
        return root;
    }

    // keep searching
    if (key < root -> key){
        root -> left = deleteNode(root -> left, key);
    }
    else if (key > root -> key){
        root -> right = deleteNode(root -> right, key);
    }
    else {
        // if key is same as root's key, 
        // then This is the node to be deleted!

        // node with one child or no child
        if ((root -> right == NULL) || (root -> left == NULL)){
            node* temp = (root -> left) ? root -> left : root -> right;

            // if no child
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            // one child
            else {
                *root = *temp;
            }

            free(temp);
        }
        // node with 2 children: get inorder successor(smallest in right subtree)
        else {
            node* temp = left_most(root -> right);

            root -> key = temp -> key;

            // delete inorder successor
            root -> right = deleteNode(root -> right, temp -> key);
        }
    }

    // If the key node is leaf (no child)
    // After deleting the key value, root becomes NULL, Return!!
    if (root == NULL){
        return root;
    }

    // 2. update height of the current node
    root -> height = height(root);

    // 3. check whether current node is balanced
    int balance = getBalance(root);

    // L1 & L0 case, perform LL rotation
    if (balance > 1 && getBalance(root -> left) >= 0){
        return rightRotation(root);
    }
    // L-1 case, perform LR rotation
    if (balance > 1 && getBalance(root -> left) < 0){
        root -> left = leftRotation(root -> left);
        return rightRotation(root);
    }

    // R1 & R0 case, perform RR rotation
    if (balance < -1 && getBalance(root -> right) <= 0){
        return leftRotation(root);
    }
    // R1 case, perform RL rotation
    if (balance < -1 && getBalance(root -> right) > 0){
        root -> right = rightRotation(root -> right);
        return leftRotation(root);
    }

    return root;
}

int main(){
    node* root = NULL;

    root = insert(root, 10);

    // print the tree

    return 0;
}