#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}



static bool invrep(abb tree) {
    bool valid = true;
    if (tree!=NULL){
        if (tree->left != NULL){
            valid = valid && elem_less(tree->left->elem, tree->elem);
        }
        if (tree->right != NULL){
            valid = valid && (tree->right->elem > tree->elem);
        }
        valid = valid && invrep(tree->left) && invrep(tree->right);
    }
    return valid;
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb create_leaf(abb_elem e){
    abb tree = NULL;
    tree = malloc(sizeof(struct _s_abb));
    assert (tree != NULL);
    tree->elem = e;
    tree->right = NULL;
    tree->left = NULL;

    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

    //caso: mi arbol esta vacio;
    if (tree == NULL){
        tree = create_leaf(e);
        return tree;
    }
    if(abb_exists(tree,e)){
       return tree;
    }else{
        if (e > tree->elem || elem_eq(e,tree->elem)){
            //voy pa derecha
            tree->right = abb_add(tree->right, e);
        }else{
            //voy pa izq
             tree->left = abb_add(tree->left, e);
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));

    if(tree == NULL){
        is_empty = true;
    }

    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));

    if (tree != NULL){
        if (tree->elem == e){
            exists = true;
            return exists;
        }else if(e >= tree->elem){
            exists = abb_exists(tree->right, e);
        }else{
            exists = abb_exists(tree->left, e);
        }
    }
    assert(abb_length(tree)!=0 || !exists);
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));


    if (tree == NULL){
        length = 0;
    }else{
        length = 1+ abb_length(tree->left) + abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
     if (tree == NULL) {
        return NULL;
    }

    if (e < tree->elem) {
        // El elemento a eliminar está en el subárbol izquierdo.
        tree->left = abb_remove(tree->left, e);
    } else if (e > tree->elem) {
        // El elemento a eliminar está en el subárbol derecho.
        tree->right = abb_remove(tree->right, e);
    } else {
        // Encontramos el nodo a eliminar.
        if (tree->left == NULL) {
            // El nodo tiene solo hijo derecho o no tiene hijos.
            abb temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            // El nodo tiene solo hijo izquierdo.
            abb temp = tree->left;
            free(tree);
            return temp;
        }

        // El nodo tiene dos hijos, buscamos el menor nodo del subárbol derecho.
        abb temp = tree->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        // Reemplazamos el elemento del nodo a eliminar con el elemento del menor nodo.
        tree->elem = temp->elem;
        // Eliminamos el menor nodo del subárbol derecho.
        tree->right = abb_remove(tree->right, temp->elem);
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    if (tree == NULL){
        return 0;
    }else if (tree->right == NULL){
        max_e = tree->elem;
    }else{
        max_e = abb_max(tree->right);
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    if (tree == NULL){
        return 0;
    }else if (tree->left == NULL){
        min_e = tree->elem;
    }else{
        min_e = abb_min(tree->left);
    }

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord==ABB_IN_ORDER  || 
                            ord==ABB_PRE_ORDER ||
                            ord==ABB_POST_ORDER));

    if (tree != NULL) {
        if (ord == ABB_IN_ORDER){
            abb_dump(tree->left, ord);
            printf("%d ", tree->elem);
            abb_dump(tree->right, ord);
        }
        if (ord == ABB_POST_ORDER){
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
            printf("%d ", tree->elem);
        }
        if (ord == ABB_PRE_ORDER){
            printf("%d ", tree->elem);
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
        }
    }

}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL){
        if (tree->left != NULL){
            tree->left = abb_destroy(tree->left);
        }
        if (tree->right != NULL){
            tree->right = abb_destroy(tree->right);
        }
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

