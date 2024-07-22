#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "builtin.h"
#include "command.h"
#include "tests/syscall_mock.h"


static bool is_cd(scommand cmd){
    return(strcmp(scommand_front(cmd), "cd") == 0);
}

static bool is_help(scommand cmd){
    return(strcmp(scommand_front(cmd), "help") == 0);
}

static bool is_exit(scommand cmd){
    return(strcmp(scommand_front(cmd), "exit") == 0);
}

bool builtin_is_internal(scommand cmd){
    assert(cmd != NULL);
    return(is_cd(cmd) || is_exit(cmd) || is_help(cmd));
}

bool builtin_alone(pipeline p){
    assert(p !=  NULL);
    return((pipeline_length(p) == 1) && builtin_is_internal(pipeline_front(p)));
}

void builtin_run(scommand cmd){
    assert(builtin_is_internal(cmd));

    if (is_help(cmd))
    {
        printf("My bash, version FAMAF 2023, by SOBLCP group.\n"
                "These shell commands are defined internally.\n"
                "\n"
                "Type 'help' to see this list :\n"
                "\n" 
                "help : My bash information and dysplay internal commands.\n"
                "cd /path/ : chdir() changes the current working directory of the calling process to the directory specified in path.\n"
                "exit : exit() terminates the calling process immediately.\n\n"
                );
    }
    else if (is_cd(cmd))
    {
        if (scommand_length (cmd) == 1) {
            chdir (getenv ("HOME"));
        } else {
            scommand_pop_front(cmd);
            if (chdir(scommand_front(cmd)) == (-1)) //hago chdir y me fijo si da error
            {
                char *str = scommand_to_string(cmd);
                perror(str);
                free(str);
            }
        }
    }
    else if(is_exit(cmd)){
        close(STDIN_FILENO);
        exit (EXIT_SUCCESS);
    }

}