#include "llist.h"

struct llist* new_llist() {

    struct llist* llst = (struct llist*) malloc(sizeof(struct llist));

    if (llst == NULL){
        return NULL;
    }

    llst->head = NULL;
    return llst;
}

void free_lcell(struct lcell* cl){

    if (cl == NULL){
        return;
    }
    free_list(cl->lst);
    free(cl);
}

void free_llist(struct llist* lst) {

    struct lcell* cur;
    struct lcell* tmp;
    if (lst == NULL) {
        return;
    }
    cur = lst->head;
    while (cur != NULL) {
        tmp = cur;
        cur = cur->next;
        free_lcell(tmp);
    }
    lst->head = NULL;
    free(lst);
}

/* Make a lcell from a letter */
struct lcell* make_lcell(char letter) {
    struct lcell* cl = malloc(sizeof(struct lcell));
    cl->letter = letter;
    cl->lst = malloc(sizeof(struct list));
    cl->lst->head = NULL;
    cl->next = NULL;
    return cl;
}

/* Compare two lcells based on the letter */
int compare_lcells(struct lcell* cl1, struct lcell* cl2) {
    return cl1->letter - cl2->letter;
}

/* Insert a cell into the appropriate lcell */
void insert_cell(struct llist* llist, struct cell* new_cell) {
    char letter = new_cell->lname[0]; // get the first letter of the last name

    // Find the lcell with the appropriate letter
    struct lcell* cl = llist->head;
    while (cl != NULL && cl->letter != letter) {
        cl = cl->next;
    }

    // If no lcell with this letter was found, create a new one
    if (cl == NULL) {
        cl = make_lcell(letter);
        cl->next = llist->head;
        llist->head = cl;
    }

    // Insert the cell into the list
    insert(cl->lst, new_cell);
}

/* Load data from a file and return a llist */
struct llist* load_file2(char* file_name) {
    struct llist* llist = malloc(sizeof(struct llist)); // create the main list
    llist->head = NULL; // initialize the head to NULL

    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", file_name);
        return llist;
    }

    char* line = NULL;
    size_t line_size = 0;
    while (getline(&line, &line_size, fp) != -1) {
        struct cell* new_cell = make_cell_from_line(line);
        insert_cell(llist, new_cell);
    }

    free(line);
    fclose(fp);

    return llist;
}

/* Print the contents of a main_list */
void print_main_list(struct llist* main_lst) {
    printf("{\n");
    struct lcell* current = main_lst->head;
    while (current != NULL) {
        printf(" %c: {\n", current->letter);
        struct cell* current_cell = current->lst->head;
        while (current_cell != NULL) {
            printf("  [%s, %s, %s]", current_cell->fname, current_cell->lname, current_cell->zip);
            current_cell = current_cell->next;
        }
        printf("\n } \n");
        current = current->next;
    }
    printf("\n}\n");
}

