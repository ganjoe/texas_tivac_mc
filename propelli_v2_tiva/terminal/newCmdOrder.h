/*
 * newCmdOrder.h
 *
 *  Created on: 02.01.2022
 *      Author: danie
 */

#ifndef TERMINAL_NEWCMDORDER_H_
#define TERMINAL_NEWCMDORDER_H_

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

/*------------propelli commands--------------*/
void    bledred(int argc, const char **argv);
void    bledgreen(int argc, const char **argv);
void    bledblue(int argc, const char **argv);
void    ledpwm(int argc, const char **argv);
void    svmmf(int argc, const char **argv);

void    reset(int argc, const char **argv);
void    settime(int argc, const char **argv);
void    setdate(int argc, const char **argv);
void    setlog(int argc, const char **argv);
void    sdlog(int argc, const char **argv);
void    help(int argc, const char **argv);
void    confsave(int argc, const char **argv);
void    confshow(int argc, const char **argv);
void    confload(int argc, const char **argv);

/*------------motor control commands--------------
 * - Contactron-Style Test Interface
 * - Init - Commands
 */

void    mcpoti(int argc, const char **argv);

extern TD_CMD newcmd;




#endif /* TERMINAL_NEWCMDORDER_H_ */
