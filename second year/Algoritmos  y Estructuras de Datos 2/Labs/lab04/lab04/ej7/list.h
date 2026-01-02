#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef struct node_of_T *list;
typedef int list_elem;

/*defininig the struct*/
struct node_of_T{
    list_elem elem;
    struct node_of_T *next;
};

/*constructors*/

    list empty();
    /*creates an empty list*/

    list add_l (list_elem e, list l);
    /*adds an element in the beggining of the list */

/*destroy*/
    list destroy (list l);
    /*frees the memory if necesary*/

/*operations*/

    bool is_empty(list l);
    /*Returns true if the list is empty*/

    list_elem head (list l);
    /*returns the first element of the list
    * PRE: !is_empty(l)
    */

    list tail (list l);
    /*ELiminates the first element of the list
    * PRE: !is_empty(l)
    */
    list addr (list_elem e, list l);
    /*adds an element on the right side of the list*/

    unsigned int length (list l);
    /*returns the length of the list*/

    list concat (list l, list l0);
    /*adds all of the elements of l0 at the end of l*/

    list_elem index (list l, unsigned int n);
    /*returns the element on th nth position
    * PRE: length(l)>n
    */
   list take (list l, unsigned int n);
   /*leaves the first n elements of a list, eliminating the rest */

   list drop (list l, unsigned int n);
   /*drops the first n elements of l*/

   list copy_list ( list l);
   /*copies the list l on other list l2*/


#endif
