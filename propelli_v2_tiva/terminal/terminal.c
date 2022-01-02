/*
 * terminal.c
 *
 *  Created on: 07.01.2021
 *      Author: daniel
 */
#include "terminal.h"

void term_lol_setCallback(TD_CMD *newcmd, const char *command, const char *help,const char *arg_names, void (*cbf)(int argc, const char **argv))
    {
    int callback_num = newcmd->callback_write;
    int i;
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

void cmd_parse_string(TD_CMD *newcmd, char *string)
    {

    char strbuffer[newcmd->callback_len];

    char* strbufferptr = &strbuffer;

    int ArgCount = 0;
    int i;

    char *ptrArgBuffer[newcmd->argument_nbr]; //max arguemtns

    //cmd ist der erste stringabschnitt von links
    strbufferptr = strtok(string, strdup(" "));

    //argumente separieren, und in ptr-array speichern
    while (strbufferptr && ArgCount < 4)
    {
    ptrArgBuffer[ArgCount++] = strbufferptr;

    strbufferptr = strtok(0, strdup(" "));
    }

    /*
     if (argc == 0)
     {
     term_qPrintf(myTxQueueHandle, "No command received\n");
     return;
     }
     if (strcmp(argv[0], "help") == 0)
     {
     term_qPrintf(myTxQueueHandle, "registered commands:\n");
     for (int i = 0; i < callback_write; i++)
     {
     term_qPrintf(myTxQueueHandle, callbacks[i].command);
     term_qPrintf(myTxQueueHandle, "\rhelp: ");
     term_qPrintf(myTxQueueHandle, callbacks[i].help);
     term_qPrintf(myTxQueueHandle, "\r");
     }
     }
     */
    for (i = 0; i < newcmd->callback_write; i++)
    {
    if (newcmd->callbacks[i].cbf != 0
        && strcmp(ptrArgBuffer[0], newcmd->callbacks[i].command) == 0)
        {
        newcmd->callbacks[i].cbf(ArgCount, (const char**) ptrArgBuffer);
        return;
        }
    }    //
    }



TD_CMD newcmd;


