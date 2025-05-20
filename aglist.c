#include "aglist.h"

AGTREE* tree = NULL;

/**
 * Creates newNode
*/
AGTREE* new_tree_node(AGTREE* tree, int val){
    AGTREE* newNode = malloc(sizeof(AGTREE));
    if(newNode == NULL){
        printf("Failed to allocate Memory\n");
        exit(0);
    }
    newNode->val = val;
    newNode->height = 0;
    newNode->left = NULL;
    newNode->right = NULL;


    return newNode;
}

/**
 * Return the height of the tree
*/
int height_of_tree(AGTREE* tree) {
    if(tree == NULL) {
        return 0;
    }
    return tree->height;
}

/**
 * Return the max of 2 numbers
*/
int max(int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}

/**
 * Return the balance of the tree
*/
int get_balance(AGTREE* tree) {
    if(tree == NULL) {
        return 0;
    }
    return height_of_tree(tree->left) - height_of_tree(tree->right);
}

/**
 * Performs a right rotation on the given subtree
 * to rebalance the AVL tree when there is a left-heavy imbalance
*/
AGTREE* right_rotate(AGTREE* tree) {
    AGTREE* x = tree->left;
    AGTREE* T2 = tree->right;

    x->right = tree;
    tree->left = T2;

    tree->height = max(height_of_tree(tree->left), height_of_tree(tree->right)) + 1;
    x->height = max(height_of_tree(x->left), height_of_tree(x->right)) + 1;

    return x;
}

/**
 * Performs a left rotation on the given subtree
 * to rebalance the AVL tree when there is a right-heavy imbalance.
 */
AGTREE* left_rotate(AGTREE* tree) {
    AGTREE* y = tree->right;
    AGTREE* T2 = y->left;

    y->left = tree;
    tree->right = T2;

    tree->height = max(height_of_tree(tree->left), height_of_tree(tree->right)) + 1;
    y->height = max(height_of_tree(y->left), height_of_tree(y->right)) + 1;

    return y;
}

/**
 * Print the tree
*/
void print_tree(AGTREE* tree){
    if(tree == NULL){
        return ;
    }

    print_tree(tree->left);
    printf("%d ", tree->val);
    print_tree(tree->right);
}

/**
 * Inserts at tree (avl)
*/
AGTREE* insert_at_tree(AGTREE* tree, int val){
    if(tree == NULL){
        AGTREE* newNode = NULL;
        newNode = new_tree_node(newNode, val);
        return newNode;
    }

    if(val > tree->val){
        tree->left = insert_at_tree(tree->left, val);
    }
    else{
        tree->right = insert_at_tree(tree->right, val);
    }
    return tree;

    int balance = get_balance(tree);

    if(balance > 1 && val < tree->left->val) {
        return right_rotate(tree);
    }

    if(balance < -1 && val > tree->right->val) {
        return left_rotate(tree);
    }

    if(balance > 1 && val > tree->left->val) {
        tree->left = left_rotate(tree->left);
        return right_rotate(tree);
    }

    if(balance < -1 && val < tree->right->val) {
        tree->right = right_rotate(tree->right);
        return left_rotate(tree);
    }

    return tree;

}

/**
 * Free the tree
*/
void free_tree(AGTREE* tree){
    if(tree == NULL){
        return ;
    }

    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

/**
 * Init the single linked list
*/
void init_single_linked_list(AGLIST** aglist){
    *aglist = NULL;
}

/**
 * Creates new Node for the list
*/
AGLIST* create_new_node(AGLIST* aglist, int val){
    AGLIST* newNode= malloc(sizeof(AGLIST));
    if(newNode == NULL){
        printf("Failed to allocate Memory\n");
        exit(0);
    }
    newNode->val = val;

    return newNode;
}

/**
 * Insert at the start of the list and at the tree
*/
void insert_at_start(AGLIST** aglist, int val){
    AGLIST* newNode = NULL;

    newNode = create_new_node(newNode, val);
    tree = insert_at_tree(tree, val);
    if(*aglist == NULL){
        newNode->next = NULL;
        *aglist = newNode;
    }
    else{
        newNode->next = *aglist;
        *aglist = newNode;
    }
}

/**
 * Insert at the end of the list and at the tree
*/
void insert_at_end(AGLIST** aglist, int val){
    AGLIST* newNode = NULL;
    newNode = create_new_node(newNode, val);
    tree = insert_at_tree(tree, val);

    if(*aglist == NULL){
        newNode->next = NULL;
        *aglist = newNode;
    }
    else{
        AGLIST* temp = *aglist;
        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

/**
 * Finds the next minimum tree node to replace the one that will be deleted
*/
AGTREE* find_next_node(AGTREE* tree){
    AGTREE* currTree = tree;

    while(currTree && currTree->left != NULL){
        currTree = currTree->left;
    }
    return currTree;
}

/**
 * Delete element in tree
*/
AGTREE* delete_tree_element(AGTREE* tree, int val){
    AGTREE* tempNode;
    if(tree == NULL){
        return NULL;
    }

    if(val > tree->val){
        tree->left = delete_tree_element(tree->left, val);
    }
    else if(val < tree->val){
        tree->right = delete_tree_element(tree->right, val);
    }
    else{
        if(tree->right == NULL){
            AGTREE* tempNode = tree->left;
            free(tree);
            return tempNode;
        }
        else if(tree->left == NULL){
            AGTREE* tempNode = tree->right;
            free(tree);
            return tempNode;
        }
        tempNode = find_next_node(tree->right);

        tree->val = tempNode->val;

        tree->right = delete_tree_element(tree->right, tempNode->val);


    }
    return tree;
}

/**
 * Deletes element in the list
*/
int delete_element(AGLIST** aglist, int val){
    AGLIST* temp = *aglist;
    AGLIST* prev = NULL;
    if(*aglist == NULL){
        return -1;
    }
    tree = delete_tree_element(tree, val);
    if((*aglist)->val == val && (*aglist)->next == NULL){
        free(*aglist);
        *aglist = NULL;
        return 0;
    }
    else if((*aglist)->val == val && (*aglist)->next != NULL){
        AGLIST* tempNode = *aglist;
        *aglist = (*aglist)->next;
        free(tempNode);
        return 0;
    }

    while(temp != NULL){
        if(temp->val == val){
            AGLIST* tempNode = temp;
            if(temp->next == NULL){
                prev->next = NULL;
            }
            else{
                prev->next = temp->next; 
            }
            free(tempNode);
            return 0;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return -1;
}

/**
 * Inserts at the start of the linked list from tree
*/
void insert_start_from_tree(AGLIST** aglist, int val){
    AGLIST* newNode = NULL;

    newNode = create_new_node(newNode, val);
    if(*aglist == NULL){
        newNode->next = NULL;
        *aglist = newNode;
    }
    else{
        newNode->next = *aglist;
        *aglist = newNode;
    }
}

/**
 * Inserts in list from tree
*/
void insert_in_list_from_tree(AGTREE* tree, AGLIST** aglist){
    if(tree == NULL){
        return ;
    }

    insert_in_list_from_tree(tree->left, aglist);
    insert_start_from_tree(aglist, tree->val);
    insert_in_list_from_tree(tree->right, aglist);
}

/**
 * Sorts the list
*/
int sort_list(AGLIST** aglist){
    if(*aglist == NULL){
        return -1;
    }
    free_list(aglist);
    insert_in_list_from_tree(tree, aglist);
    return 0;
}

/**
 * Prints the list
*/
void print_list(AGLIST* aglist){
    AGLIST* temp = aglist;
    int isFirstCounter = 0;

    while(temp != NULL){
        if(isFirstCounter == 0){
            printf("______________\n");
            printf("    Head\n");
            printf(" _______\n");
            printf("|  %d    |\n", temp->val);
            printf("|_______|\n\n");
        }
        else{
            printf(" _______\n");
            printf("|  %d    |-----^\n", temp->val);
            printf("|_______|\n\n");
        }
        isFirstCounter++;
        temp = temp->next;
    }
    printf("    Tail\n");
    printf("______________\n");
}

/**
 * Inserts at sorted list and at the tree
*/
int insert_at_sorted_list(AGLIST** aglist, int val){
    AGLIST* newNode = NULL;
    AGLIST* temp = *aglist;
    AGLIST* prev = NULL;
    newNode = create_new_node(newNode, val);
    tree = insert_at_tree(tree, val);

    if(*aglist == NULL){
        newNode->next = NULL;
        *aglist = newNode;
        return 0;
    }
    else{
        while(temp != NULL){
            if(val <= temp->val){
                if(prev != NULL){
                    if(prev->next == NULL){
                        newNode->next = NULL;
                    }
                    else{
                        newNode->next = prev->next;
                    }
                    prev->next = newNode;
                    return 0;
                }
                else{
                    newNode->next = *aglist;
                    *aglist = newNode;
                    return 0;
                }

            }
            prev = temp;
            temp = temp->next;
        }
    }

    if(prev->val <= val){
        newNode->next = NULL;
        prev->next = newNode;
        return 0;
    }
    return -1;
}

/**
 * Free the list
*/
void free_list(AGLIST** aglist){
    while(*aglist != NULL){
        AGLIST* tempNode = *aglist;
        *aglist = (*aglist)->next;
        free(tempNode);
    }
    *aglist = NULL;
}

/**
 * Free the list and the tree
*/
void free_all(AGLIST** aglist){
    while(*aglist != NULL){
        AGLIST* tempNode = *aglist;
        *aglist = (*aglist)->next;
        free(tempNode);
    }
    free_tree(tree);
}
