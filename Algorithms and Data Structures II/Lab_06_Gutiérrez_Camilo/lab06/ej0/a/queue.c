#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    unsigned int size;
    struct s_node *last;
    struct s_node *first;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node *create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool invrep(queue q) {

    return q != NULL;
}

/*
    Las siguientes dos funciones son necesarias porque en la postcondición de queue_enqueue() se verifica si el primer 
    elemento de la cola modificada es igual al elemento entrante pero esto solo es cierto si anteriormente la cola era vacía.
    Por lo que una mejor guarda para la precondición sería revisar si el elemento entrante es el primero ó el último.
    No contemplo el caso en que un elemento sea el primero y el último de la fila a la vez.
*/
static bool queue_has_a_last(queue q){

    return q->size > 1;
}

static queue_elem queue_last(queue q) {
    assert(invrep(q) && queue_has_a_last(q)); //PRE

    return q->last->elem;
} 

queue queue_empty(void) {
    queue q=NULL;
    
    q = malloc(sizeof(struct s_queue));
    assert(q!=NULL);
    q->size=0u;
    q->last=NULL;
    q->first=NULL;

    assert(invrep(q) && queue_is_empty(q)); //POS
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q)); //PRE
    struct s_node *new_node = create_node(e);
    if (q->first==NULL) {
        q->first = new_node;
    } else {
        if (q->last == NULL){
            q->first->next = new_node;
            q->last = new_node;
        }
        q->last->next = new_node;
        q->last = new_node;
    }
    q->size = q->size + 1u;

    assert(invrep(q) && !queue_is_empty(q) && (queue_first(q) == e || queue_last(q) == e)); //POS
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q)); //PRE

    return q->first == NULL;
}

unsigned int queue_size(queue q) {
    assert(invrep(q)); //PRE
    
    return q->size;
}

queue_elem queue_first(queue q) {
    
    assert(invrep(q) && !queue_is_empty(q)); //PRE

    return q->first->elem;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q)); //PRE
    struct s_node * killme=q->first;

    q->first = q->first->next;
    killme = destroy_node(killme);
    
    assert(invrep(q)); //POS
    return q;
}

void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
