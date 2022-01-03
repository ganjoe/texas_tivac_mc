/*
 * newCmdOrder.c
 *
 *  Created on: 02.01.2022
 *      Author: danie
 */

#include  "newCmdOrder.h"

void reset(int argc, const char **argv)
    {
    float f = -1;

    if (argc == 2)
    {
    sscanf(argv[1], "%f", &f);
    }
    }

void cmd_init_callbacks(TD_CMD *asdf)
    {
    asdf->callback_len = 40;
    asdf->argument_nbr = 4;

    term_lol_setCallback(asdf, "reset", "mcu reset", "1,0 uint", reset);

    }
void cmd_parse_lobj(TD_CMD *newcmd, TD_LINEOBJ *line)
    {
    cmd_parse_string(newcmd, line->string);
    }
void cmd_parse_string(TD_CMD *newcmd, char *string)
    {
    int i;
   // char strbuffer[newcmd->callback_len];

    char * strbufferptr; //token für strtok
    char delimiter[] = " ";
    int ArgCount = 0;

    //char *ptrArgBuffer[newcmd->argument_nbr]; //max arguemtns
    char *ptrArgBuffer[4]; //max arguemtns

    //cmd ist der erste stringabschnitt von links
    strbufferptr = strtok(string, delimiter);

    //argumente separieren, und in ptr-array speichern
    while (strbufferptr && ArgCount < 4)
    {
    ptrArgBuffer[ArgCount++] = strbufferptr;
    //
    strbufferptr = strtok(0, delimiter);
    }

    for (i = 0; i < newcmd->callback_write; i++)
    {
    if (newcmd->callbacks[i].cbf != 0 && strcmp(ptrArgBuffer[0], newcmd->callbacks[i].command) == 0)
        {
        newcmd->callbacks[i].cbf(ArgCount, (const char**) ptrArgBuffer);
        return;
        }
    }    //
    }
void term_lol_setCallback(TD_CMD *newcmd, const char *command, const char *help,const char *arg_names, void (*cbf)(int argc, const char **argv))
    {
    int i;
    int callback_num = newcmd->callback_write;
    for (i = 0; i < newcmd->callback_write; i++)
    {
    // First check the address in case the same callback is registered more than once.
    if (newcmd->callbacks[i].command == command)
        {
        callback_num = i;
        break;
        }
    // Check by string comparison.
    if (strcmp(newcmd->callbacks[i].command, command) == 0)
        {
        callback_num = i;
        break;
        }
    // Check if the callback is empty (unregistered)
    if (newcmd->callbacks[i].cbf == 0)
        {
        callback_num = i;
        break;
        }
    }
    newcmd->callbacks[callback_num].command = command;
    newcmd->callbacks[callback_num].help = help;
    newcmd->callbacks[callback_num].arg_names = arg_names;
    newcmd->callbacks[callback_num].cbf = cbf;

    if (callback_num == newcmd->callback_write)
    {
    newcmd->callback_write++;
    if (newcmd->callback_write >= newcmd->callback_len)
        {
        newcmd->callback_write = 0;
        }
    }
    }

TD_CMD newcmd;

