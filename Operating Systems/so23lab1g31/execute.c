#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tests/syscall_mock.h"

#include "command.h"
#include "execute.h"
#include "builtin.h"

//Macros con los mensajes de error predefinidos
#define CLOSE_PIPE_ERR "Error closing pipe.\n"
#define INVALID_CMD "Invalid command.\n"
#define FORK_ERR "Fork error.\n"
#define CREATE_PIPE_ERR "Error creating pipe.\n"
#define OPEN_REDIR_FILE "Error opening redirect file.\n"

//variables de pipe
#define READ_END 0
#define WRITE_END 1



static char ** scommand_to_array(scommand command){
    assert(command != NULL);

    unsigned int length = scommand_length(command);
    char * str_i = NULL;
    char ** argv = calloc(length+1, sizeof(char*));
    
    for (unsigned int i = 0; i<length; i++){
        str_i = scommand_front(command);
        argv[i] = calloc(strlen(str_i), sizeof(char));
        argv[i] = strcpy(argv[i], str_i);
        scommand_pop_front(command);
    }
    
    return argv;
}

static void redir_in(scommand command){
    int red_in = open(scommand_get_redir_in(command), O_RDONLY | O_CREAT, S_IRWXU);

    if(red_in == -1){ perror(OPEN_REDIR_FILE); } 
    else { dup2(red_in,STDIN_FILENO); }
    if (close(red_in) != 0){ perror(CLOSE_PIPE_ERR); }
}

static void redir_out(scommand command){
    int red_out = open(scommand_get_redir_out(command), O_WRONLY | O_CREAT, S_IRWXU);

    if(red_out == -1){ perror(OPEN_REDIR_FILE); } 
    else { dup2(red_out, STDOUT_FILENO); }
    if (close(red_out) != 0) { perror(CLOSE_PIPE_ERR);}
}

void execute_pipeline(pipeline apipe){
    assert(apipe != NULL);

    pid_t pid = 0;
    char ** argv = NULL;
    unsigned int length = pipeline_length(apipe);
    
    if (pipeline_is_empty(apipe)) {return;}
    
    if (builtin_is_internal(pipeline_front(apipe))) {
        builtin_run(pipeline_front(apipe));
    
    } else if (length == 1){
        pid = fork();

        if (pid < 0) { perror(FORK_ERR); }
        
        else if (pid==0){
            scommand cmd = pipeline_front(apipe);
        
            if(scommand_get_redir_in(cmd) != NULL) { redir_in(cmd); }
            if(scommand_get_redir_out(cmd) != NULL){ redir_out(cmd); }
            
            argv = scommand_to_array(cmd);
            execvp(argv[0], argv);
            perror(INVALID_CMD);

            apipe = pipeline_destroy(apipe);
            exit(getpid());
        }
        else {
            if (!pipeline_is_empty(apipe)){
                pipeline_pop_front(apipe);
            }
            if (pipeline_get_wait(apipe)){
                wait(NULL);
            }
        }
    }
    else if (length == 2){

        int pipefd[2];
        if (pipe(pipefd) < 0 ) {perror (CREATE_PIPE_ERR);}

        for (unsigned int i=1; i<= length; i++){
            
            pid = fork();
            if (pid < 0) { perror(FORK_ERR); }

            else if (pid==0){
                scommand cmd = pipeline_front(apipe);
    
                if(scommand_get_redir_in(cmd) != NULL) { redir_in(cmd); }
                if(scommand_get_redir_out(cmd) != NULL) { redir_out(cmd); }

                if(i == 1){      //si es cmd1 escribe al que sigue
                   close(pipefd[READ_END]);
                   dup2(pipefd[WRITE_END], STDOUT_FILENO);
                   close(pipefd[WRITE_END]);
                }

                if(i == 2){      //si es cmd2 lee del anterior
                    close(pipefd[WRITE_END]);
                    dup2(pipefd[READ_END], STDIN_FILENO);
                    close(pipefd[READ_END]);
                }

                argv = scommand_to_array(cmd);
                execvp(argv[READ_END], argv);
                perror(INVALID_CMD);
                
                apipe = pipeline_destroy(apipe);
                exit(getpid());
            }
            else {
                if (!pipeline_is_empty(apipe)){ pipeline_pop_front(apipe); }
                if (i == 1) { close(pipefd[WRITE_END]); }
                if (i == 2) { close(pipefd[READ_END]); }
            }
        } 
        if (pipeline_get_wait(apipe)){
            wait(NULL);
            wait(NULL);
        }
    
    } else{ printf(INVALID_CMD); }
}
