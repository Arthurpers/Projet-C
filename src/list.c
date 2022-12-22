#include "list.h"

/* Construction/Destruction
======================== */

struct list* new_list() {
	struct list* lst = (struct list*)malloc(sizeof(struct list));

	if (lst == NULL) { 
		return NULL; 
	}

	lst->head=NULL;
	return lst;
}

static void free_cells(struct list *lst) {
	struct cell *cur;
	struct cell *tmp;
    // Empty list 
	if (lst == NULL) { 
        return; 
    }
    // Free each cell one by one
	cur = lst->head;
	while (cur != NULL) {
		tmp = cur;
		cur = cur->next;
        // If dynamically allocated!
        // free(tmp->fname);
        // free(tmp->lname);
        // free(tmp->zip);
		free(tmp);
	}
	lst->head = NULL;
}

void free_list(struct list* lst) {
    free_cells(lst);
	free(lst);
}


/* Printing
======== */

void print_cell(struct cell* c) {
	printf("[%s, %s, %s]\n", c->fname, c->lname, c->zip);
}

void print_list(struct list *lst) {
	printf("{\n");
    struct cell* current_cell = lst->head;
    while (current_cell != NULL) {
        print_cell(current_cell);
        current_cell = current_cell->next;
    }
    printf("}\n");
}

/* Cell addition
============= */

struct cell* make_cell(char* fname, char* lname, char* zip) {
	struct cell* new_cell = (struct cell*) malloc(sizeof(struct cell));
    new_cell->fname = fname;
    new_cell->lname = lname;
    new_cell->zip = zip;
    new_cell->next = NULL;
    return new_cell;
}

void push(struct list *lst, struct cell* c) {
	c->next = lst->head;
    lst->head = c;
}

/* Pop the first cell of the list and return its value in out */
void pop(struct list* list, struct cell* out) {
    out->fname = list->head->fname;
    out->lname = list->head->lname;
    out->zip = list->head->zip;
    out->next = NULL;
    list->head = list->head->next;
}

/* Make a cell from a line of data */
struct cell* make_cell_from_line(char* line) {
 	line = strtok(line, ";");
    char *copy = (char*)malloc(strlen(line)+1);
    strcpy(copy, line);
    char* fname = strtok(copy, ",");
    char* lname = strtok(NULL, ",");
    char* zip = strtok(NULL, "");

    // Use the make_cell function to create the cell
    struct cell* new_cell = make_cell(fname, lname, zip);

    // free(copy); // free the copy of the line
    return new_cell;
}


/* Compare two cells by last name (then first name if equal) */
int compare_cells(struct cell* cell1, struct cell* cell2) {
    int result = strcmp(cell1->lname, cell2->lname);
    if (result == 0) {
        result = strcmp(cell1->fname, cell2->fname);
    }
    return result;
}

/* Insert a cell into the list in the correct order */
void insert(struct list* list, struct cell* new_cell) {
    // Check if the list is empty
    if (list->head == NULL) {
        list->head = new_cell;
        return;
    }

    // Check if the new cell should be inserted at the beginning of the list
    if (compare_cells(new_cell, list->head) < 0) {
        new_cell->next = list->head;
        list->head = new_cell;
        return;
    }

    // Find the correct position in the list
    struct cell* current_cell = list->head;
    while (current_cell->next != NULL && compare_cells(new_cell, current_cell->next) > 0) {
        current_cell = current_cell->next;
    }

    // Insert the new cell
    new_cell->next = current_cell->next;
    current_cell->next = new_cell;
}

struct list* load_file(char* file_name) {
    // Create a new list
    struct list* list = new_list();

    // Open the file
    FILE* file;
	file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return list;
    }

    // Read each line of the file and insert the data into the list
    char line[1024];
    while (fgets(line, 1024, file)) {
        // Remove the newline character from the end of the line
        int line_length = strlen(line);
        if (line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        }

        // Make a cell from the line and insert it into the list
        struct cell* new_cell = make_cell_from_line(line);
        insert(list, new_cell);
    }

    // Close the file
    fclose(file);

    return list;
}

