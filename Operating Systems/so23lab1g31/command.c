#include <stdbool.h> 
#include <stdio.h>
#include <assert.h>
#include <glib.h>  //hay que usar esta libreria

#include "command.h"
#include "strextra.h"

/*  estructura de comando simple : ([char*],char*,char*)
    [char*] se puede implementar con GSList, y va a contener "nombre de comando" y argumentos,
    luego los siguiente punteros de tipo char son las redirecciones de entrada y salida

    implementacion de GSList: 
        struct GSList {
            void* data;
            GSList* next;
        }
*/

struct scommand_s {
    GSList *args; //<-- Comandos y Argumentos
    char *redir_in; //<-- Redirección de Entrada
    char *redir_out; //<-- Redirección de Salida
};


scommand scommand_new(void){
    scommand self = malloc (sizeof(struct scommand_s));
    
    self->args = NULL;
    self->redir_in = NULL;
    self->redir_out = NULL;

    assert(self != NULL && scommand_is_empty(self) && scommand_get_redir_in(self) == NULL && scommand_get_redir_out(self) == NULL); 
    return self;
}
/*
 * Nuevo `scommand', sin comandos o argumentos y los redirectores vacíos
 *   Returns: nuevo comando simple sin ninguna cadena y redirectores vacíos.
 * Ensures: result != NULL && scommand_is_empty (result) &&
 *  scommand_get_redir_in (result) == NULL &&
 *  scommand_get_redir_out (result) == NULL
 */

scommand scommand_destroy(scommand self) {
    assert (self != NULL);
    g_slist_free_full(self->args, free);
    self->args = NULL;
    if (self->redir_in != NULL)
    {
        free(self->redir_in);
        self->redir_in = NULL;
    }
    if (self->redir_out != NULL)
    {
        free(self->redir_out);
        self->redir_out = NULL;
    }   
    free(self);
    self = NULL;

    return self;
}
/*
 * Destruye `self'.
 *   self: comando simple a destruir.
 * Requires: self != NULL
 * Ensures: result == NULL
 */

/* Modificadores */

void scommand_push_back(scommand self, char * argument) {
    assert (self != NULL && argument != NULL);
    self->args = g_slist_append(self->args, argument);
    assert(!scommand_is_empty(self));
}
/*
 * Agrega por detrás una cadena a la secuencia de cadenas.
 *   self: comando simple al cual agregarle la cadena.
 *   argument: cadena a agregar. El TAD se apropia de la referencia.
 * Requires: self!=NULL && argument!=NULL
 * Ensures: !scommand_is_empty()
 */

void scommand_pop_front(scommand self) {
    assert (self!=NULL && !scommand_is_empty(self));
    free(g_slist_nth_data(self->args, 0));
    self->args = g_slist_delete_link (self->args, self->args);
}
/*
 * Quita la cadena de adelante de la secuencia de cadenas.
 *   self: comando simple al cual sacarle la cadena del frente.
 * Requires: self!=NULL && !scommand_is_empty(self)
 */

void scommand_set_redir_in(scommand self, char * filename){
    assert (self != NULL);
    if (self->redir_in == NULL){
        self->redir_in = filename;
    } else {
        free(self->redir_in);
        self->redir_in = filename;
    }
}

void scommand_set_redir_out(scommand self, char * filename){
    assert (self != NULL);
    if (self->redir_out == NULL){
        self->redir_out = filename;
    } else {
        free(self->redir_out);
        self->redir_out = filename;
    }
}
/*
 * Define la redirección de entrada (salida).
 *   self: comando simple al cual establecer la redirección de entrada (salida).
 *   filename: cadena con el nombre del archivo de la redirección
 *     o NULL si no se quiere redirección. El TAD se apropia de la referencia.
 * Requires: self!=NULL
 */

/* Proyectores */

bool scommand_is_empty(const scommand self){
    assert(self != NULL);
    return (g_slist_length(self->args) == 0);
}


/*
 * Indica si la secuencia de cadenas tiene longitud 0.
 *   self: comando simple a decidir si está vacío.
 *   Returns: ¿Está vacío de cadenas el comando simple?
 * Requires: self!=NULL
 */

unsigned int scommand_length(const scommand self) {
    unsigned int length = 0u;
    assert (self != NULL);
    length = g_slist_length(self->args); 
    assert((length == 0) == scommand_is_empty(self));
    return length;
}
/*
 * Da la longitud de la secuencia cadenas que contiene el comando simple.
 *   self: comando simple a medir.
 *   Returns: largo del comando simple.
 * Requires: self!=NULL
 * Ensures: (scommand_length(self)==0) == scommand_is_empty()
 *
 */

char * scommand_front(const scommand self) {
    assert (self != NULL && !scommand_is_empty(self));
    char * front_data = (char *)g_slist_nth_data (self->args, 0);
    assert (front_data != NULL);
    return front_data;
}
/*
 * Toma la cadena de adelante de la secuencia de cadenas.
 *   self: comando simple al cual tomarle la cadena del frente.
 *   Returns: cadena del frente. La cadena retornada sigue siendo propiedad
 *     del TAD, y debería considerarse inválida si luego se llaman a
 *     modificadores del TAD. Hacer una copia si se necesita una cadena propia.
 * Requires: self!=NULL && !scommand_is_empty(self)
 * Ensures: result!=NULL
 */

char * scommand_get_redir_in(const scommand self) {
    assert (self != NULL);
    return self->redir_in;
}
char * scommand_get_redir_out(const scommand self) {
    assert (self != NULL);
    return self->redir_out;
}
/*
 * Obtiene los nombres de archivos a donde redirigir la entrada (salida).
 *   self: comando simple a decidir si está vacío.
 *   Returns: nombre del archivo a donde redirigir la entrada (salida)
 *  o NULL si no está redirigida.
 * Requires: self!=NULL
 */

char * scommand_to_string(const scommand self) {
    assert(self != NULL);
    char *output = strdup("");
    char *killme;
    for (unsigned int i = 0u; i < g_slist_length(self->args); ++i){
        char *current_cmnd = g_slist_nth_data(self->args, i);
        killme = output;
        output = strmerge(output, current_cmnd);
        free(killme);
        killme = output;
        output = strmerge(output, " ");
        free(killme);
    }
    if(self->redir_out != NULL){
        killme = output;
        output = strmerge(output, "> ");
        free(killme);
        killme = output;
        output = strmerge(output, self->redir_out);
        free(killme);
    }
    if(self->redir_in != NULL){
        killme = output;
        output = strmerge(output, " < ");
        free(killme);
        killme = output;
        output = strmerge(output, self->redir_in);
        free(killme);
    }

    return (output);
}
/* Preety printer para hacer debugging/logging.
 * Genera una representación del comando simple en un string (aka "serializar")
 *   self: comando simple a convertir.
 *   Returns: un string con la representación del comando simple similar
 *     a lo que se escribe en un shell. El llamador es dueño del string
 *     resultante.
 * Requires: self!=NULL
 * Ensures: scommand_is_empty(self) ||
 *   scommand_get_redir_in(self)==NULL || scommand_get_redir_out(self)==NULL ||
 *   strlen(result)>0
 */


/*
 * pipeline: tubería de comandos.
 * Ejemplo: ls -l *.c > out < in  |  wc  |  grep -i glibc  &
 * Secuencia de comandos simples que se ejecutarán en un pipeline,
 *  más un booleano que indica si hay que esperar o continuar.
 *
 * Una vez que un comando entra en el pipeline, la memoria pasa a ser propiedad
 * del TAD. El llamador no debe intentar liberar la memoria de los comandos que
 * insertó, ni de los comandos devueltos por pipeline_front().
 * pipeline_to_string() pide memoria internamente y debe ser liberada
 * externamente.
 *
 * Externamente se presenta como una secuencia de comandos simples donde:
 *           ______________________________
 *  front -> | scmd1 | scmd2 | ... | scmdn | <-back
 *           ------------------------------
 */


/* Estructura: ([scommand], bool) */
struct pipeline_s {
    GSList *scmds;
    bool wait;  
};

pipeline pipeline_new(void) {
    pipeline self = malloc(sizeof(struct pipeline_s)); 
    self->scmds = NULL;
    self->wait = true;
    assert (self != NULL && pipeline_is_empty (self) && pipeline_get_wait (self));
    return self;
}
/*
 * Nuevo `pipeline', sin comandos simples y establecido para que espere.
 *   Returns: nuevo pipeline sin comandos simples y que espera.
 * Ensures: result != NULL
 *  && pipeline_is_empty(result)
 *  && pipeline_get_wait(result)
 */

pipeline pipeline_destroy(pipeline self) {
    assert (self != NULL);
    while (self -> scmds != NULL) {
        self -> scmds -> data = scommand_destroy (self -> scmds -> data);
        self -> scmds = g_slist_delete_link (self -> scmds, self -> scmds);
    };
    free (self);
    self = NULL;
    assert (self == NULL);
    return self;
}
/*
 * Destruye `self'.
 *   self: tubería a a destruir.
 * Requires: self != NULL
 * Ensures: result == NULL
 */

/* Modificadores */

void pipeline_push_back(pipeline self, scommand sc) {
    assert (self != NULL && sc != NULL);
    self->scmds = g_slist_append(self->scmds, sc);
    assert (!pipeline_is_empty(self));
}
/*
 * Agrega por detrás un comando simple a la secuencia.
 *   self: pipeline al cual agregarle el comando simple.
 *   sc: comando simple a agregar. El TAD se apropia del comando.
 * Requires: self!=NULL && sc!=NULL
 * Ensures: !pipeline_is_empty()
 */

void pipeline_pop_front(pipeline self) {
    assert (self != NULL && !pipeline_is_empty (self));
    self -> scmds -> data = scommand_destroy (self->scmds -> data);
    self-> scmds = g_slist_delete_link (self-> scmds, self-> scmds);
}
/*
 * Quita el comando simple de adelante de la secuencia.
 *   self: pipeline al cual sacarle el comando simple del frente.
 *      Destruye el comando extraido.
 * Requires: self!=NULL && !pipeline_is_empty(self)
 */

void pipeline_set_wait(pipeline self, const bool w) {
    assert (self != NULL);
    self -> wait = w;
}
/*
 * Define si el pipeline tiene que esperar o no.
 *   self: pipeline que quiere ser establecido en su atributo de espera.
 * Requires: self!=NULL
 */

/* Proyectores */

bool pipeline_is_empty(const pipeline self) {
    assert (self != NULL);
    return (g_slist_length(self->scmds) == 0);
}
/*
 * Indica si la secuencia de comandos simples tiene longitud 0.
 *   self: pipeline a decidir si está vacío.
 *   Returns: ¿Está vacío de comandos simples el pipeline?
 * Requires: self!=NULL
 */

unsigned int pipeline_length(const pipeline self) {
    assert (self != NULL);
    unsigned int length = g_slist_length (self -> scmds);
    return length;
}
/*
 * Da la longitud de la secuencia de comandos simples.
 *   self: pipeline a medir.
 *   Returns: largo del pipeline.
 * Requires: self!=NULL
 * Ensures: (pipeline_length(self)==0) == pipeline_is_empty()
 *
 */

scommand pipeline_front(const pipeline self)  {
    assert (self != NULL && !pipeline_is_empty (self));
    return (g_slist_nth_data (self -> scmds, 0));
}
/*
 * Devuelve el comando simple de adelante de la secuencia.
 *   self: pipeline al cual consultar cual es el comando simple del frente.
 *   Returns: comando simple del frente. El comando devuelto sigue siendo
 *      propiedad del TAD.
 *      El resultado no es un "const scommand" ya que el llamador puede
 *      hacer modificaciones en el comando, siempre y cuando no lo destruya.
 * Requires: self!=NULL && !pipeline_is_empty(self)
 * Ensures: result!=NULL
 */

bool pipeline_get_wait(const pipeline self) {
    assert (self != NULL);
    return self -> wait;
}
/*
 * Consulta si el pipeline tiene que esperar o no.
 *   self: pipeline a decidir si hay que esperar.
 *   Returns: ¿Hay que esperar en el pipeline self?
 * Requires: self!=NULL
 */

char * pipeline_to_string(const pipeline self) {
    assert (self != NULL);
    char *current_cmnd; 
    char *output = strdup ("");
    char *kill_char;
    for (unsigned int i = 0u; i < g_slist_length (self->scmds); ++i) {
        current_cmnd = scommand_to_string(g_slist_nth_data(self->scmds, i));
        kill_char = output;
        output = strmerge(output, current_cmnd);
        free (kill_char);
        if(i != g_slist_length(self->scmds) - 1u){    
            kill_char = output;
            output = strmerge (output, " | ");
            free(kill_char);
        }
        free(current_cmnd);
    };
    if (!self->wait)
    {
        kill_char = output;
        output = strmerge(output, "&");
        free(kill_char);
    }
    
    return output;
}
/* Pretty printer para hacer debugging/logging.
 * Genera una representación del pipeline en una cadena (aka "serializar").
 *   self: pipeline a convertir.
 *   Returns: una cadena con la representación del pipeline similar
 *     a lo que se escribe en un shell. Debe destruirla el llamador.
 * Requires: self!=NULL
 * Ensures: pipeline_is_empty(self) || pipeline_get_wait(self) || strlen(result)>0
 */
