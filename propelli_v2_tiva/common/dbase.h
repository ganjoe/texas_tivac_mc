/*
 * dbase.h
 *
 *  Created on: 02.01.2022
 *      Author: danie
 */

#ifndef COMMON_DBASE_H_
#define COMMON_DBASE_H_

#include "main.h"

#define TD_LINEOBJ_MAX_SSIZE 16
#define TD_LINEOBJ_MAX_HEADERSIZE 8
#define TD_LINEOBJ_MAX_POSTFIXSIZE 5
#define TD_LINEOBJ_MAX_TIMESTRINGSIZE 18
#define TD_LINEOBJ_MAX_FILENAMESIZE 8
//array size for snprintf
#define UART_PRINTBUFFER    64

typedef struct
{
    char    timestring[TD_LINEOBJ_MAX_TIMESTRINGSIZE];
    char    filename[TD_LINEOBJ_MAX_FILENAMESIZE];  //rom l999 cmd
    char    string[TD_LINEOBJ_MAX_SSIZE];   //setdate 10 10 10
    char    header[TD_LINEOBJ_MAX_HEADERSIZE];  //tmcu, thot, tcld, fhot, fcld, lvlh, lvlc
    char    postfix[TD_LINEOBJ_MAX_POSTFIXSIZE];    // "%4.3f"
    uint16_t    linenr;
    double  value;

}
    TD_LINEOBJ;

void dbase_parse_cmd(TD_LINEOBJ *line);

void dbase_StoreSD(TD_LINEOBJ *line);

void dbase_Make(TD_LINEOBJ *line,
            const char* filename,
            const char* string,
            const char* header,
            const char* postfix,
            uint16_t* linenr,
            const char  *fmt,
            ... );





#endif /* COMMON_DBASE_H_ */
