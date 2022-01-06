/*
 * dbase.c
 *
 *  Created on: 02.01.2022
 *      Author: danie
 */


#include "dbase.h"
#include "main.h"

/*
void dbase_Make(TD_LINEOBJ *line,const char *filename, const char *string,
    const char *header, const char *postfix, uint16_t *linenr, const char *fmt, ...)
    {
    char pbuffer[TD_LINEOBJ_MAX_SSIZE];

    dBase_addTimeStr(line);

    int len = 0;

    // no vsprint paramlist and already formatet string is given
    -----------------------------------------------------------
    if ((fmt == 0) & (string != 0))
    {
    snprintf(pbuffer, TD_LINEOBJ_MAX_SSIZE, string);
    strcpy(line->string, pbuffer);
    }
    //  printing to lineobject with given vsprintf format string
    -----------------------------------------------------------
    if ((fmt != 0) & (string == 0))
    {
    memset(pbuffer, 1, TD_LINEOBJ_MAX_SSIZE);
    va_list argp;
    va_start(argp, fmt);
    vsnprintf(pbuffer, UART_PRINTBUFFER, fmt, argp);
    strcpy(line->string, pbuffer);
    va_end(argp);
    }
    // printing double value with default format
    -----------------------------------------------------------
    if ((fmt == 0) & (string == 0))
    {
    snprintf(line->string, UART_PRINTBUFFER, "%.4g", line->value);
    }
    //
    -----------------------------------------------------------
    if (filename == 0)
    {
    snprintf( pbuffer, 2, " ");
    strcpy( line->filename, pbuffer);
    }
    else
    {
    len = strlen(filename);
    utils_truncate_number_int(&len, 0, TD_LINEOBJ_MAX_SSIZE);
    snprintf( pbuffer, len+1 , filename);
    strcpy( line->filename, pbuffer);
    }
    //
    -----------------------------------------------------------
    if (header == 0)
    {
     snprintf( pbuffer, 2, " ");
     strcpy( line->header, pbuffer);
    }
    else
    {
    len = strlen(header);
    utils_truncate_number_int(&len, 0, TD_LINEOBJ_MAX_HEADERSIZE);
    snprintf( pbuffer, len+1, header);
     //strcpy( line->header, pbuffer);
     strcpy( line->header, pbuffer);
    }
    //
    -----------------------------------------------------------
    if (postfix == 0)
    {
     snprintf( pbuffer, 2, " ");
     strcpy( line->postfix, pbuffer);
    }
    else
    {
    len = strlen(postfix);
    utils_truncate_number_int(&len, 0, TD_LINEOBJ_MAX_POSTFIXSIZE);
    snprintf( pbuffer, len+1, postfix);
    strcpy( line->postfix, pbuffer);
    }
    -----------------------------------------------------------

    // dont overwrite in case of static usage
    if (linenr != 0)
    line->linenr = *linenr;


    // dont overwrite in case of static usage
    if (linenr != 0)
    line->linenr = *linenr;

    }*/
