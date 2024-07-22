#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>         // incluye getcwd: devuelve el directorio del proceso actual

#include "command.h"
#include "execute.h"
#include "parser.h"
#include "parsing.h"
#include "builtin.h"

static void show_prompt(void) {
    char buffer [1040];
    getcwd (buffer, sizeof (buffer));
    printf ("\x1b[32;1m%s@%s-mybash\x1b[0m:\x1b[34;1m~%s\x1b[0m> ", getenv ("USERNAME"), getenv ("USER"), buffer != NULL ? buffer : "current directory not avaible");        // getenv: accede a la variable de entorno
    fflush (stdout);
}

int main(int argc, char *argv[]) {
    pipeline pipe;
    Parser input;
    bool quit = false;

    input = parser_new(stdin);
    while (!quit) {
        show_prompt();
        pipe = parse_pipeline(input);
        
        /* Hay que salir luego de ejecutar? */
        quit = parser_at_eof(input);
        if (pipe != NULL)
        {
            execute_pipeline(pipe);
            pipeline_destroy(pipe);
        } 
        
    }
    parser_destroy(input); input = NULL;
    return EXIT_SUCCESS;
}
