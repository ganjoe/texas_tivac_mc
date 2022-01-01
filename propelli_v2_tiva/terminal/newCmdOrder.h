/*
 * newCmdOrder.h
 *
 *  Created on: 07.01.2021
 *      Author: daniel
 */


#include "terminal.h"

#ifndef APP_NEWCMDORDER_H_
#define APP_NEWCMDORDER_H_


/*------------Registrieren der Callback-Funktionen--------------
 *
 */
void cmd_init_callbacks(TD_CMD *asdf);

/*------------Callback Funktionen--------------
 *
 */
void    help(int argc, const char **argv);



#endif /* APP_NEWCMDORDER_H_ */
