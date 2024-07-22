#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "parsing.h"
#include "parser.h"
#include "command.h"

static scommand parse_scommand(Parser p) {
    /* Devuelve NULL cuando hay un error de parseo */
    scommand cmd = NULL;
    char *arg = NULL;
    arg_kind_t type;
    bool pipe_found, ampsd_found; //ampsd = ampersand
    parser_skip_blanks(p);
    arg = parser_next_argument(p, &type); 
    if (arg != NULL) {
        cmd = scommand_new ();
        while (!parser_at_eof (p) && arg != NULL) {
            switch (type) {
                case ARG_NORMAL:
                    scommand_push_back (cmd, arg);
                    break;
                case ARG_INPUT:
                    scommand_set_redir_in(cmd, arg);
                    break;
                case ARG_OUTPUT:
                    scommand_set_redir_out(cmd, arg);
                    break;
            };
            parser_skip_blanks(p);
            arg = parser_next_argument(p, &type);       // avanza al siguiente argumento
        };
    } else {
        parser_op_background (p, &ampsd_found);
        parser_op_pipe (p, &pipe_found);
        if (ampsd_found || pipe_found) {
            fprintf (stderr, "Parser error, %s founded \n", (pipe_found) ? "|" : "&");
        };
    };
    return cmd;
}

pipeline parse_pipeline(Parser p) {
    assert(p != NULL && !parser_at_eof(p));
    
    scommand cmd = parse_scommand(p);
    pipeline result = pipeline_new ();

    bool error = (cmd == NULL); /* Comando inválido al empezar */
    bool another_pipe = true, has_garbage = false, wait = false;
    

    while (!error && another_pipe && !wait) {
        pipeline_push_back(result, cmd);
        parser_op_pipe (p, &another_pipe);      // CREO que no hace falta un parser blank (parse_command te deja en un argumento '|' o '&')
        parser_op_background (p, &wait);
        cmd = parse_scommand(p);         // desp de | espera otro comando
        error = (cmd == NULL);
    }

    /* Opcionalmente un OP_BACKGROUND al final */

    pipeline_set_wait (result, !wait);

    parser_garbage (p, &has_garbage);   
    parser_last_garbage (p);
    /* Consumir todo lo que hay inclusive el \n */
    
    /* Tolerancia a espacios posteriores */
    /* Si hubo error, hacemos cleanup */
    bool not_new_line = has_garbage && !wait; // si no es salto de linea ni '&'

    if ((not_new_line || pipeline_is_empty (result)) && error) {
        result = pipeline_destroy(result);  // para evitar problemas con destroy (pipe_destroy retorna pipeline)
    };

    return result;
}

