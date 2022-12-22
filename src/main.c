#include <time.h>

#include "llist.h"

int main(int argc, char *argv[]) {
    // struct list* l;
    // l = new_list();
    // print_list(l);

    // struct cell* c;
    // c = make_cell("Annie", "ERNAUX", "76170");
    
    // push(l, c);

    // print_list(l);

    // free_list(l);
    // return 0;

    
    if(argc == 1){ // no file specified
        printf("Error - no file specified.\n");
        return 1;
    }

    char* filename = argv[1];
    printf("----- Méthode 1 -----\n");
    clock_t t1;
    t1 = clock();
    struct list* l;
    l = load_file(filename);
    // print_list(l);
    free_list(l);
    t1 = clock() - t1;
    double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds
    printf("\n");

    printf("----- Méthode 2 -----\n");
    clock_t t2;
    t2 = clock();
    struct llist* l2;
    l2 = load_file2(filename);
    // print_main_list(l2);
    free_llist(l2);
    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds

    printf("Methode1() took %f seconds to execute \n", time_taken1);
    printf("Methode2() took %f seconds to execute \n", time_taken2);




}