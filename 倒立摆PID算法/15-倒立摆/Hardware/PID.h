#ifndef __PID_H
#define __PID_H

#include <stdint.h>

typedef struct {
    float target;
    float actual;
    float out;

    float Kp;
    float Ki;
    float Kd;

    float Error0;
    float Error1;
    float ErrorInt;

    float maxOut;
    float minOut;

    uint32_t lastTime;
} PID_t;

void PID_Update(PID_t *p);

#endif // __PID_H
