#include <assert.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool valid = true;
    if (d != NULL){
        if(d->left != NULL){
            valid = valid && key_less(d->left->key, d->key);
        }
        if (d->right != NULL){
            valid = valid && !key_less(d->right->key, d->key);
        }
        valid = valid && invrep(d->left) && invrep(d->right);
    }
    return valid;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;

    assert(invrep(d) && dict_length(d) == 0);
    return dict;
}

dict_ t create_d(key_t word, value_t def){
    dict_t dict = NULL;
    dict =malloc(sizeof(struct _node_t));
    assert(dict != NULL);

    dict->key = word;
    dict->value = def;
    dict->left = NULL;
    dict->right = NULL;

    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(d) && word != NULL && def != NULL);

    //si no tengo diccionario aun
    if (dict == NULL){
        dict = create_d(word, def);
        assert(invrep(d) && key_eq(def, dict_search(dict, word)));
        return dict;
    }

    //si la palabra no existe, le busco lugar
    if (!dict_exists(dict,word)){
       if(key_less (word, dict->key)){
           dict->left = dict_add(dict->left, word);
        }else{
            dict->right = dict_add (dict->right,word);
        }
    }else{

    }

    //si la palabra existe, le cambio la definicion

    assert(invrep(d) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def=NULL;
    /* needs implementation */
    return NULL;
}

bool dict_exists(dict_t dict, key_t word) {
    /* needs implementation */
    return false;
}

unsigned int dict_length(dict_t dict) {
    /* needs implementation */
    return 0u;
}

dict_t dict_remove(dict_t dict, key_t word) {
    /* needs implementation */
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    /* needs implementation */
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    /* needs implementation */
}

dict_t dict_destroy(dict_t dict) {
    /* needs implementation */
    return dict;
}

