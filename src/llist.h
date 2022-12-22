#include "list.h"

struct llist {
    struct lcell* head;
};

struct lcell {
    char letter; // first letter of the last name
    struct list* lst; // list of cells with last names starting with this letter
    struct lcell* next; 
};

/* Make a lcell from a letter */
struct lcell* make_lcell(char letter);

/* Compare two lcells based on the letter */
int compare_lcells(struct lcell* cl1, struct lcell* cl2);

/* Load data from a file and return a llist */
struct llist* load_file2(char* file_name);

/* Print the contents of a main_list */
void print_main_list(struct llist* main_lst);

void free_llist(struct llist* lliste);