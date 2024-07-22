/*static abb elim(abb tree, abb father, abb_elem e){
    assert(invrep(tree)); //PRE
    abb eraser = NULL;

    if (elem_less(e, tree->elem))
    {
        father = tree;
        tree = tree->left;
        tree->left = elim(tree, father, e);
    }
    else if (elem_less(tree->elem, e))
    {
        father = tree;
        tree = tree->right;
        tree->right = elim(tree, father, e);
    }
    else
    {
        if (tree->right == NULL)
        {
            eraser = tree;
            tree = tree->left;
            free(eraser);
            father->left = tree;
        }
        else
        {
            eraser = tree->right;
            while (eraser->left != NULL) //Me muevo hasta llegar al elemento más chico del subárbol derecho.
            {
                father = eraser;
                eraser = eraser->left;
            }
            tree->elem = eraser->elem;
            if (father->left == eraser)
            {
                free(eraser);
                father->left = NULL;
            }
            else
            {
                tree->right = eraser->right;
                free(eraser);
                eraser = NULL;
            } 
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e)); //POS
    return tree;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree)); //PRE
    abb tree_aux=NULL;
    abb father=NULL;
    
    if (tree != NULL)
    {
        if (elem_less(e, tree->elem))
        {
            father = tree;
            tree_aux = tree->left;
            tree->left = elim(tree_aux, father, e);
        }
        else if (elem_less(tree->elem, e))
        {
            father = tree;
            tree_aux = tree->right;
            tree->right = elim(tree_aux, father, e);
        }
        else
        {
            tree = elim(tree, tree, e);
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e)); //POS
    return tree;
}
*/