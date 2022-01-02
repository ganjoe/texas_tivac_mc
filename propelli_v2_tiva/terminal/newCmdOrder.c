/*
 * newCmdOrder.c
 *
 *  Created on: 07.01.2021
 *      Author: daniel
 */

#include "newCmdOrder.h"


void cmd_init_callbacks(TD_CMD *asdf)
    {
    asdf->callback_len = 40;
    asdf->argument_nbr = 4;

    term_lol_setCallback(asdf, "help", "Hilfetext jeden Befehls anzeigen", "kein Argument", help);

    }




