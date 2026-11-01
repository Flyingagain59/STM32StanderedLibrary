#include "PID.h"
#include "stm32f10x.h"

void PID_Update(PID_t *p)
{
    p->Error1 = p->Error0;
    p->Error0 = p->target - p->actual;

    if (p->Ki != 0)
    {
        p->ErrorInt  += p->Error0;
    }else
    {
        p->ErrorInt = 0;
    }
    p->out = p->Kp * p->Error0 + p->Ki * p->ErrorInt + p->Kd * (p->Error0 - p->Error1);

    if (p->out > p->maxOut){p->out = p->maxOut;}
    if (p->out < p->minOut){p->out = p->minOut;}
    
}
