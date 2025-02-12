#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist)
{
    if (cmd_line == NULL || strlen(cmd_line) == 0) {

        return WARN_NO_CMDS;
    }

    int count = 0;
    char *token;
    char *save;

    token = strtok_r(cmd_line, PIPE_STRING, &save);

    while (token != NULL) {

        if (count >= CMD_MAX) {

            return ERR_TOO_MANY_COMMANDS;
        }
        while (*token == SPACE_CHAR) {
            token++;
        }

        char *position = strchr(token, SPACE_CHAR);

        if (position) {
            *position = '\0';
            position++;

            while (*position == SPACE_CHAR) {
                position++;
            }
            strncpy(clist->commands[count].args, position, ARG_MAX - 1);

        }

        strncpy(clist->commands[count].exe, token, EXE_MAX - 1);
        count++;
        token = strtok_r(NULL, PIPE_STRING, &save);
    }


    clist->num = count;

    return OK;
}
