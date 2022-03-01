/*
 * newCmdOrder.c
 *
 *  Created on: 02.01.2022
 *      Author: danie
 */

#include  "newCmdOrder.h"
#include "digital_IO/input_output.h"
#include "tasks/mc_primer.h"


void reset(int argc, const char **argv)
    {
    float f = -1;

    if (argc == 2)
    {
    sscanf(argv[1], "%f", &f);
    UARTprintf("\rcmd:\t%s",argv[0]);
    UARTprintf("\rargs:\t%d",argc);
    }
    }

void bledred(int argc, const char **argv)
    {
    int state = -1;
    if (argc ==2)
        {
        sscanf(argv[1], "%d", &state);
        if(state)
            {
            pinset(&led_red, 1);
            UARTprintf("\rRED_LED ON");
            }
        else
            {
            pinset(&led_red, 0);
            UARTprintf("\rRED_LED OFF");
            }
        }
    if (argc == 1)
        {
        if (pintoggle(&led_red))
            {
            UARTprintf("\rRED_LED ON");
            }
        else
            {
            UARTprintf("\rRED_LED OFF");
            }

        }
    }
void bledgreen(int argc, const char **argv)
    {
    int state = -1;
    if (argc ==2)
        {
        sscanf(argv[1], "%d", &state);
        if(state)
            {
            pinset(&led_green, 1);
            UARTprintf("\rGRN_LED ON");
            }
        else
            {
            pinset(&led_green, 0);
            UARTprintf("\rGRN_LED OFF");
            }
        }
    if (argc == 1)
    {
        if(pintoggle(&led_green))
        {
            UARTprintf("\rGRN_LED ON");
        }
        else
        {
            UARTprintf("\rGRN_LED OFF");
        }
    }
    }
void bledblue(int argc, const char **argv)
    {
    int state = -1;
    if (argc == 2)
        {
        sscanf(argv[1], "%d", &state);
        if(state)
            {
           pinset(&led_blue, 1);
           UARTprintf("\rBLUE_LED ON");
            }
        else
            {
            pinset(&led_blue, 0);
            UARTprintf("\rBLUE_LED OFF");
            }
        }
    if (argc == 1)
        {
        if(pintoggle(&led_blue))
            {
            UARTprintf("\rBLUE_LED ON");
            }
        else
            {
            UARTprintf("\rBLUE_LED OFF");
            }
        }
    }
void ledpwm(int argc, const char **argv)
    {
    float r = -1;
    float g = -1;
    float b = -1;
    uint32_t f = 0;

    if (argc == 5)
    {
    sscanf(argv[1], "%f", &r);
    sscanf(argv[2], "%f", &g);
    sscanf(argv[3], "%f", &b);
    sscanf(argv[4], "%d", &f);

    UARTprintf("\rcmd:\t%s",argv[0]);
    utils_truncate_number(&r, 0, 1.0);
    utils_truncate_number(&g, 0, 1.0);
    utils_truncate_number(&b, 0, 1.0);


    //pwmLedSetFreq(&pwmled);
    pwmled.freq(f, &pwmled);
    pwmled.green(g, &pwmled);
    pwmled.red(r, &pwmled);
    pwmled.blue(b, &pwmled);
    //pwmLedSetDuty(&pwmled);

    }
    if (argc == 1 || 5)
    {
    UARTprintf("\rPeriodGetPWM_GEN_2:%d",PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2));
    UARTprintf("\rPeriodGetPWM_GEN_3:%d",PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3));

    UARTprintf("\rPWMPulseWidth_PWM_GEN_3:%d",PWMPulseWidthGet(PWM1_BASE, PWM_OUT_5));
    UARTprintf("\rPWMPulseWidth_PWM_GEN_4:%d",PWMPulseWidthGet(PWM1_BASE, PWM_OUT_6));
    UARTprintf("\rPWMPulseWidth_PWM_GEN_5:%d",PWMPulseWidthGet(PWM1_BASE, PWM_OUT_7));
    }

    }
void mcpoti(int argc, const char **argv)
    {
    float f = -1;

    if (argc == 2)
        {
        sscanf(argv[1], "%f", &f);
        UARTprintf("\rcmd:\t%s",argv[0]);
        utils_truncate_number(&f, -1.0, 1.0);
        mc_data.poti_input = f;
        }
    }
void svmmf(int argc, const char **argv)
    {
    float g = -1;
    float o = -1;
    float f = 0;
    if (argc == 4)
        {
        svm_mf.Gain = g;
        svm_mf.Freq = f;
        svm_mf.Offset = o;
        }
    }

void help(int argc, const char **argv)
    {
    //dlogPause(&termlog);
    int var;
    for (var = 0; var < newcmd.callback_write; ++var)
        {
        UARTprintf("\rCMD %s ARG %s DESC %s \r",
                    newcmd.callbacks[var].command,
                    newcmd.callbacks[var].arg_names,
                    newcmd.callbacks[var].help);
        }
    }
void cmd_init_callbacks(TD_CMD *asdf)
    {
    asdf->callback_len = 40;
    asdf->argument_nbr = 5;

    term_lol_setCallback(asdf, "help", "alle befehle auflisten", "no arg", help);
    term_lol_setCallback(asdf, "reset", "mcu reset", "1,0", reset);
    term_lol_setCallback(asdf, "bledred", "switch board led", "1,0", bledred);
    term_lol_setCallback(asdf, "bledgreen", "switch board led", "1,0", bledgreen);
    term_lol_setCallback(asdf, "bledblue", "switch board led", "1,0", bledblue);
    term_lol_setCallback(asdf, "mcpoti", "analog-in override", "float -1,1", mcpoti);
    term_lol_setCallback(asdf, "ledpwm", "duty und freq fürrgb-led auf launchpad r,g,b,freq", "float 0..1 und 1..20E", ledpwm);
    term_lol_setCallback(asdf, "svmmf", "svm-mf gain, offset, freq", "gain, offset, freq", svmmf);
    }
void cmd_parse_string(TD_CMD *newcmd,char *string)
{
    int i;
    // char strbuffer[newcmd->callback_len];

    char *strbufferptr; //token für strtok
    char delimiter[] = " ";

    int ArgCount = 0;

    // pointerarry für argumente
    char *ptrArgBuffer[5]; //max arguemtns

    strbufferptr = strtok(string, delimiter);

    //argumente separieren, und in ptr-array speichern
    while (strbufferptr && ArgCount < 5)
        {
        ptrArgBuffer[ArgCount++] = strbufferptr;
        //
        strbufferptr = strtok(0, delimiter);
        }

    for (i = 0; i < newcmd->callback_write; i++)
        {
        if (strcmp(ptrArgBuffer[0], newcmd->callbacks[i].command) == 0)
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

