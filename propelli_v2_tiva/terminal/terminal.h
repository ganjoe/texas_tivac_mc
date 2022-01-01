/*
 * terminal.h
 *
 *  Created on: 07.01.2021
 *      Author: daniel
 */

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

#include "main.h"

typedef struct
    {
    const char *command;
    const char *help;
    const char *arg_names;
    void (*cbf)(int argc, const char **argv);
    }
    TD_TERMINAL_CALLBACKS;

typedef struct
{
    TD_TERMINAL_CALLBACKS callbacks[40];
    int callback_write;
    int callback_len;
    int argument_nbr;
}
    TD_CMD;
/*------------api----------------------------
*/
void term_lol_setCallback(
            TD_CMD* newcmd,     \
            const char *command,    \
            const char *help,   \
            const char *arg_names,  \
            void (*cbf)(int argc, const char **argv));


void    cmd_parse_string(TD_CMD* newcmd,char* string);
void    cmd_init_callbacks(TD_CMD *newcmd);




#endif /* TERMINAL_TERMINAL_H_ */
