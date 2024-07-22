#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
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

static abb create_leaf(abb_elem e){
    abb container=NULL;

    container = malloc(sizeof(struct _s_abb));
    container->elem = e;
    container->left = NULL;
    container->right = NULL;

    return container;
}

static bool invrep(abb tree) {
    bool res=true;

    if (tree != NULL)
    {
        if (tree->left != NULL)
        {
            res = res && elem_less(tree->left->elem, tree->elem) && !elem_eq(tree->left->elem, tree->elem) && invrep(tree->left);
        }
        if (tree->right != NULL)
        {
            res = res && elem_less(tree->elem, tree->right->elem) && !elem_eq(tree->elem, tree->right->elem) && invrep(tree->right);
        }
    }

    return res;
}

abb abb_empty(void) {
    abb tree;
    
    tree = NULL;

    assert(invrep(tree) && abb_is_empty(tree)); //POS
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree)); //PRE
    
    if (tree == NULL)
    {
        tree = create_leaf(e);
    }
    else
    {
        if (elem_less(e, tree->elem))
        {
            tree->left = abb_add(tree->left, e);
        }
        else if (elem_less(tree->elem, e))
        {
            tree->right = abb_add(tree->right, e);
        }
    }

    assert(invrep(tree) && abb_exists(tree, e)); //POS
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree)); //PRE
  
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree)); //PRE
    
    if (tree != NULL)
    {
        if (elem_eq(e, tree->elem))
        {
            exists = true;
        }
        else if (elem_less(e, tree->elem))
        {
            exists = abb_exists(tree->left, e);
        }
        else
        {
            exists = abb_exists(tree->right, e);
        }
    }

    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0u;
    assert(invrep(tree)); //PRE
   
    if (tree != NULL)
    {
        ++length;
        length = length + abb_length(tree->left);
        length = length + abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0)); //POS
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree)); //PRE
    abb tree_aux=NULL;
    abb father=NULL;
    
    if (tree != NULL)
    {
        if (elem_less(e, tree->elem))
        {
            tree->left = abb_remove(tree->left, e);
        }
        else if (elem_less(tree->elem, e))
        {
            tree->right = abb_remove(tree->right, e);
        }
        else
        {
            if (tree->right == NULL) //Si el subárbol derecho es vacío, el nodo a borrar ahora es su subárbol izquierdo
            {                        //y elimino el nodo original.
                tree_aux = tree;
                tree = tree->left;
                free(tree_aux);
                tree_aux = NULL;
            }
            else
            {
                tree_aux = tree->right;
                while (tree_aux->left != NULL) //Si el subárbol derecho no es vacío, me muevo hasta llegar al elemento 
                {                              //más chico del subárbol derecho.
                    father = tree_aux;
                    tree_aux = tree_aux->left;
                }
                tree->elem = tree_aux->elem; //Reemplazo el valor 'tree' por el valor de 'tree_aux' el cual se
                if (father != NULL)          //convierte en mi nodo a borrar.
                {
                    if (tree_aux->right != NULL) //Si 'tree_aux' no es una hoja, cambio mi nodo a borrar por
                    {                            //su subárbol derecho y elimino el nodo original.
                        tree_aux->elem = tree_aux->right->elem;
                        father = tree_aux;
                        tree_aux = tree_aux->right;
                        father->right = tree_aux->right; 
                        free(tree_aux);
                        tree_aux = NULL;
                    }
                    else //Si 'tree_aux' es una hoja, simplemente la elimino.
                    {
                        free(tree_aux);
                        tree_aux = NULL;
                        father->left = NULL;
                    }
                }
                else //Si 'father' nunca fue asignado, entonces el nodo a borrar ahora es su subárbol derecho
                {    //y elimino el nodo original.
                    tree->right = tree_aux->right;
                    free(tree_aux);
                    tree_aux = NULL;
                } 
            }
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e)); //POS
    return tree;
}

abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree)); //PRE
    
    root = tree->elem;

    assert(abb_exists(tree, root)); //POS
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree)); //PRE
   
    if (tree->right != NULL)
    {
        max_e = abb_max(tree->right);
    }
    else
    {
        max_e = tree->elem;
    }

    assert(invrep(tree) && abb_exists(tree, max_e)); //POS
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree)); //PRE
   
    if (tree->left != NULL)
    {
        min_e = abb_min(tree->left);
    }
    else
    {
        min_e = tree->elem;
    }

    assert(invrep(tree) && abb_exists(tree, min_e)); //POS
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree)); //PRE
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree)); //PRE
    
    if (tree != NULL)
    {
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free (tree);
        tree = NULL;
    }

    assert(tree == NULL); //POS
    return tree;
}
