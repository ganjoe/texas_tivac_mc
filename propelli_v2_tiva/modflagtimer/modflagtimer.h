/*
 * datatypes_tasks.h
 *
 *  Created on: 10.09.2020
 *      Author: daniel
 */

#ifndef MODFLAGTIMER_MODFLAGTIMER_H_
#define MODFLAGTIMER_MODFLAGTIMER_H_


typedef struct
    {
    int divisor;

    uint64_t rampcounter, callcount;
    uint32_t counter, ovf;
    uint64_t oldtick, systick, newtick,repeat ;
    uint32_t duration, tickdiff;
    float freq, duty_sp;
    /*
     * flag         funktion wird ausgeführt, danach rückgesetzt. wird durch mftask gepollt
     * flag_delay   funktion wird nach ablauf über callback-isr ausgeführt. gehört zu mf_tse
     * flag_reset   error-flag, wird ggf. durch mfinit-funktion rückgesetzt
     * init_done    enable für die funktion
     * const char name[8];
     */
    int flag, flag_delay, flag_reset, init_done;

    } MODFLAG;

    void modflag_init(MODFLAG *thismf, MODFLAG systick, float setpoint_hz);
    void modflag_upd_regular(MODFLAG *thismf);
    void modflag_enable(MODFLAG *thismf);
    void modflag_disable(MODFLAG *thismf);
    void modflag_set_delay_until_callback(MODFLAG *thismf);
    uint64_t modflag_tickdiff(MODFLAG *cnt);

void mf_timerinit(uint32_t hz, MODFLAG *thismf);

extern MODFLAG mf_systick;

#endif /* MODFLAGTIMER_MODFLAGTIMER_H_ */
