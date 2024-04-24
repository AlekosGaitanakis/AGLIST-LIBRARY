#ifndef _AGLIST_H_
#define _AGLIST_H_

#define BEGIN int main(void){
#define END return 0;}
#define INIT(aglist) init_single_linked_list(aglist)
#define INSERT_START(aglist, val) insert_at_start(aglist, val)
#define INSERT_END(aglist, val) insert_at_end(aglist, val)
#define DELETE_ELEMENT(aglist, val) delete_element(aglist, val)
#define PRINT_LIST(aglist) print_list(aglist)
#define SORT_LIST(aglist) sort_list(aglist)
#define FREE_LIST(aglist) free_all(aglist)
#define INSERT_AT_SORTED(aglist, val) insert_at_sorted_list(aglist, val)

    struct list{
        int val;
        struct list* next;
    };

    struct tree{
        int val;
        struct tree* left;
        struct tree* right;
    };

    typedef struct tree AGTREE;
    typedef struct list AGLIST;

    /**
     * O(1) initialize the list 
    */
    void init_single_linked_list(AGLIST** aglist);
    
    /**
     * O(1) insert val at the start of the list, but O(logn) because of the tree insertion
    */
    void insert_at_start(AGLIST** aglist, int val);

    /**
     * O(n) insert val at the end of the list
    */
    void insert_at_end(AGLIST** aglist, int val);

    /**
     * O(n) delete element with specific val
    */
    int delete_element(AGLIST** aglist, int val);

    /**
     * O(n) sort the list
    */
    int sort_list(AGLIST** aglist);

    /**
     * O(n) insert at sorted list
    */
    int insert_at_sorted_list(AGLIST** aglist, int val);

    /**
     * 0(n) print List
    */
    void print_list(AGLIST* aglist);

    /**
     * O(n) free only list
    */
    void free_list(AGLIST** aglist);

    /**
     * O(n) free list and tree
    */
    void free_all(AGLIST** aglist);             
#endif