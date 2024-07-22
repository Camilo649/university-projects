#include <stdlib.h>
#include <assert.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool is_key(key_t word){
    bool res = true;
    unsigned int length = string_length(word);
    unsigned int i=0u;
    const char* w = string_ref(word);

    while (res && i < length)
    {
        if (w[i] == ' ') //Si la cadena tiene un espacio, significa que contiene más de una palabra
        {                //y por lo tanto, probablemente sea una definición y no una sola palabra.
            res = false;
        }
        ++i;
    }

    return res;
}

static bool is_value(value_t def){
    bool res = false;
    string espacio = string_create(" ");

    res = !value_eq(def, espacio);
    string_destroy(espacio);

    return res;
}

static bool is_empty_dict(dict_t d){

    return d == NULL;
}

static bool invrep(dict_t d) { //Notar que el invariante de representación también contempla que tanto las palabras
    bool inv=true;             //como las definiciones sean válidas.

    if (!is_empty_dict(d))
    {
        inv = is_key(d->key) && is_value(d->value);
        if (inv && !is_empty_dict(d->left))
        {
            inv = inv && key_less(d->left->key, d->key) && !key_eq(d->left->key, d->key) && invrep(d->left);
        }
        if (inv && !is_empty_dict(d->right))
        {
            inv = inv && key_less(d->key, d->right->key) && !key_eq(d->key, d->right->key) && invrep(d->right);
        }
    }

    return inv;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    
    assert(invrep(dict) && dict_length(dict) == 0); //POS
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict) && is_key(word) && is_value(def)); //PRE

    if (is_empty_dict(dict))
    {
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    }
    else
    {
        if (key_less(word, dict->key))
        {
            dict->left = dict_add(dict->left, word, def);
        }
        else if (key_less(dict->key, word))
        {
            dict->right = dict_add(dict->right, word, def);
        }
        else
        {
            dict->key = string_destroy(dict->key);
            dict->key = word;
            dict->value = string_destroy(dict->value);
            dict->value = def;
        }
    }

    assert(invrep(dict) && value_eq(def, dict_search(dict, word))); //POS
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def=NULL;
    assert(invrep(dict) && is_key(word)); //PRE

    if (!is_empty_dict(dict))
    {
        if (key_less(word, dict->key))
        {
            def = dict_search(dict->left, word);
        }
        else if (key_less(dict->key, word))
        {
            def = dict_search(dict->right, word);
        }
        else
        {
            def = dict->value;
        }
    }

    assert((def != NULL) == dict_exists(dict, word)); //POS
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict) && is_key(word)); //PRE
    bool res=false;

    if (!is_empty_dict(dict))
    {
        if (key_less(word, dict->key))
        {
            res = dict_exists(dict->left, word);
        }
        else if (key_less(dict->key, word))
        {
            res = dict_exists(dict->right, word);
        }
        else
        {
            res = true;
        }
    }

    assert(invrep(dict)); //POS
    return res;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict)); //PRE
    unsigned int length=0u;

     if (dict != NULL)
    {
        ++length;
        length = length + dict_length(dict->left);
        length = length + dict_length(dict->right);
    }
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict) && is_key(word)); //PRE

    dict_t dict_aux=NULL;
    dict_t previous=NULL;
    
    if (dict != NULL)
    {
        if (key_less(word, dict->key))
        {
            dict->left = dict_remove(dict->left, word);
        }
        else if (key_less(dict->key, word))
        {
            dict->right = dict_remove(dict->right, word);
        }
        else
        {
            if (dict->right == NULL) //Si el subdiccionario derecho es vacío, la palabra a borrar ahora es su 
            {                        //subdiccionario izquierdo y elimino la palabra original.
                dict_aux = dict;
                dict = dict->left;
                dict_aux->key = string_destroy(dict_aux->key);
                dict_aux->value = string_destroy(dict_aux->value);
                free(dict_aux);
                dict_aux = NULL;
            }
            else
            {
                dict_aux = dict->right;
                while (dict_aux->left != NULL) //Si el subdiccionario derecho no es vacío, me muevo hasta llegar 
                {                              //al elemento más chico del subdiccionario derecho.
                    previous = dict_aux;
                    dict_aux = dict_aux->left;
                }
                dict->key = dict_aux->key; //Reemplazo el valor 'dict' por el valor de 'dict_aux' el cual se
                if (previous != NULL)      //convierte en mi palabra a borrar.
                {
                    if (dict_aux->right != NULL) //Si 'dict_aux' no es vacío, cambio mi palabra a borrar por
                    {                            //su subdiccionario derecho y elimino la palabra original.
                        dict_aux->key = dict_aux->right->key;
                        previous = dict_aux;
                        dict_aux = dict_aux->right;
                        previous->right = dict_aux->right; 
                        dict_aux->key = string_destroy(dict_aux->key);
                        dict_aux->value = string_destroy(dict_aux->value);
                        free(dict_aux);
                        dict_aux = NULL;
                    }
                    else //Si 'dict_aux' es vacío, simplemente elimino la palabra a la que apunta.
                    {
                        dict_aux->key = string_destroy(dict_aux->key);
                        dict_aux->value = string_destroy(dict_aux->value);
                        free(dict_aux);
                        dict_aux = NULL;
                        previous->left = NULL;
                    }
                }
                else //Si 'previous' nunca fue asignado, entonces la palabra a borrar ahora es su subdiccionario derecho
                {    //y elimino la palabra original.
                    dict->right = dict_aux->right;
                    dict_aux->key = string_destroy(dict_aux->key);
                    dict_aux->value = string_destroy(dict_aux->value);
                    free(dict_aux);
                    dict_aux = NULL;
                } 
            }
        }
    }

    assert(invrep(dict) && !dict_exists(dict, word)); //POS
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict)); //PRE
    dict = dict_destroy(dict);

    assert(invrep(dict) && dict_length(dict) == 0); //POS
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL); //POS
    //Dumpea alfábeticamente.
    if (dict != NULL)
    {
        dict_dump(dict->left, file);
        string_dump(dict->key, file);
        fprintf(file, ":");
        string_dump(dict->value, file);
        fprintf(file, "\n\n");
        dict_dump(dict->right, file);
    } 
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict)); //PRE

    if (!is_empty_dict(dict))
    {
        dict->left = dict_destroy(dict->left);
        dict->right = dict_destroy(dict->right);
        string_destroy(dict->key);
        string_destroy(dict->value);
        free(dict);
        dict = NULL;
    }

    assert(dict == NULL); //POS
    return dict;
}
