#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"

/**** 
 **** FOR REMOTE SHELL USE YOUR SOLUTION FROM SHELL PART 3 HERE
 **** THE MAIN FUNCTION CALLS THIS ONE AS ITS ENTRY POINT TO
 **** EXECUTE THE SHELL LOCALLY
 ****
 */

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */
int exec_local_cmd_loop() {

    char *cmd_buff = malloc(SH_CMD_MAX);

    if (!cmd_buff) {
        return ERR_MEMORY;
    }

    command_list_t clist;

    while (1) {

        printf("%s", SH_PROMPT);

        if (!fgets(cmd_buff, SH_CMD_MAX, stdin)) {

            printf("\n");
            break;
        }

        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';
        
        if (build_cmd_list(cmd_buff, &clist) == WARN_NO_CMDS) {
            printf(CMD_WARN_NO_CMD);
            continue;
        }
        
        if (clist.num == 1) {

            Built_In_Cmds type = match_command(clist.commands[0].argv[0]);

            if (type == BI_CMD_EXIT) {

                free(cmd_buff);
                return OK;
            } 
            
            else if (type == BI_CMD_CD) {
                if (clist.commands[0].argc > 1) {
                    chdir(clist.commands[0].argv[1]);
                }
            } 
            
            else {

                exec_cmd(&clist.commands[0]);
            }
        } 
        
        else {
            execute_pipeline(&clist);
        }
    }


    free(cmd_buff);
    return OK;
}

int alloc_cmd_buff(cmd_buff_t *cmd_buff) {

    cmd_buff->_cmd_buffer = malloc(SH_CMD_MAX);

    if (cmd_buff->_cmd_buffer) {
        return OK;
    }
    
    else {
        return ERR_MEMORY;
    }

}

int free_cmd_buff(cmd_buff_t *cmd_buff) {

    free(cmd_buff->_cmd_buffer);
    return OK;
}

int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd_buff) {

    cmd_buff->argc = 0;
    cmd_buff->_cmd_buffer = malloc(SH_CMD_MAX);
    
    if (!cmd_buff->_cmd_buffer) {
        return ERR_MEMORY;
    }

    strcpy(cmd_buff->_cmd_buffer, cmd_line);
    char *input = cmd_buff->_cmd_buffer;
    char *token = NULL;
    bool quotes = false;

    while (*input != '\0' && cmd_buff->argc < CMD_MAX) {

        while (*input == SPACE_CHAR) {

            input++;
        }

        if (*input == '"') {

            quotes = true;
            input++;
            token = input;
        } 
        
        else {

            token = input;
        }

        while (*input != '\0' && (quotes || *input != SPACE_CHAR)) {

            if (*input == '"' && quotes) {

                quotes = false;
                *input = '\0';
                input++;
                break;
            }

            input++;
        }

        if (*input != '\0') {

            *input = '\0';
            input++;
        }

        if (token && *token != '\0') {

            cmd_buff->argv[cmd_buff->argc++] = token;
        }
    }

    cmd_buff->argv[cmd_buff->argc] = NULL;
    
    if (cmd_buff->argc > 0) {

        return OK;
    }

    else {

        return WARN_NO_CMDS;
    }

    return OK;

}

int exec_cmd(cmd_buff_t *cmd) {

    pid_t pid = fork();

    if (pid < 0) {
        return ERR_EXEC_CMD;
    } 
    
    else if (pid == 0) {

        if (execvp(cmd->argv[0], cmd->argv) == -1) {

            exit(ERR_EXEC_CMD);
        }
    } 
    
    else {
        
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } 

        else {

            return ERR_EXEC_CMD;
        }
    }

    return OK;

}

Built_In_Cmds match_command(const char *input) {

    if (strcmp(input, EXIT_CMD) == 0) {
        return BI_CMD_EXIT;
    } 
    
    else if (strcmp(input, "cd") == 0) {
        return BI_CMD_CD;
    }

    return BI_NOT_BI;
}

int build_cmd_list(char *cmd_line, command_list_t *clist) {

    clist->num = 0;
    char *token = strtok(cmd_line, PIPE_STRING);
    
    while (token != NULL && clist->num < CMD_MAX) {

        build_cmd_buff(token, &clist->commands[clist->num]);
        clist->num++;
        token = strtok(NULL, PIPE_STRING);
    }
    
    if (clist->num == 0) {
        return WARN_NO_CMDS;
    }
    
    return OK;
}

int execute_pipeline(command_list_t *clist) {

    int pipes[CMD_MAX - 1][2];
    pid_t pids[CMD_MAX];

    for (int i = 0; i < clist->num - 1; i++) {

        if (pipe(pipes[i]) == -1) {
            return ERR_EXEC_CMD;
        }
    }

    for (int i = 0; i < clist->num; i++) {

        pids[i] = fork();

        if (pids[i] < 0) {
            return ERR_EXEC_CMD;
        }

        if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }

            if (i < clist->num - 1) {
                
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            for (int j = 0; j < clist->num - 1; j++) {

                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            execvp(clist->commands[i].argv[0], clist->commands[i].argv);
            exit(ERR_EXEC_CMD);
        }
    }
    
    for (int i = 0; i < clist->num - 1; i++) {

        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    for (int i = 0; i < clist->num; i++) {
        waitpid(pids[i], NULL, 0);
    }
    
    return OK;

}
