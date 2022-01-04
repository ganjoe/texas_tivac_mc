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
     * flag         funktion wird ausgef�hrt, danach r�ckgesetzt. wird durch mftask gepollt
     * flag_delay   funktion wird nach ablauf �ber callback-isr ausgef�hrt. geh�rt zu mf_tse
     * flag_reset   error-flag, wird ggf. durch mfinit-funktion r�ckgesetzt
     * init_done    enable f�r die funktion
     * const char name[8];
     */
    int flag, flag_delay, flag_reset, init_done;

    } MODFLAGTIMER;

    void modflag_init(MODFLAGTIMER *thismf, float systick, float setpoint_hz);
    void modflag_upd_regular(MODFLAGTIMER *thismf);
    void modflag_enable(MODFLAGTIMER *thismf);
    void modflag_disable(MODFLAGTIMER *thismf);
    void modflag_set_delay_until_callback(MODFLAGTIMER *thismf);
    uint64_t modflag_tickdiff(MODFLAGTIMER *cnt);

void mf_timerinit(int microseconds);

extern MODFLAGTIMER mf_global_systick;

#endif /* MODFLAGTIMER_MODFLAGTIMER_H_ */
