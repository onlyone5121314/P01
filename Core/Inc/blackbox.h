/*
 * blackbox.h
 * 简易飞行数据黑匣子接口
 */
#ifndef __BLACKBOX_H__
#define __BLACKBOX_H__

#include "main.h"

typedef struct {
    uint32_t tick;
    float pitch;
    float roll;
    float yaw;
    int16_t thr;
    int16_t motor1;
    int16_t motor2;
    int16_t motor3;
    int16_t motor4;
    uint8_t flight_state;
    uint8_t remote_state;
    float voltage;
    uint16_t distance;
} BlackboxEntry;

void Blackbox_Init(void);
void Blackbox_Log(BlackboxEntry *entry);
void Blackbox_DumpAll(void);

#endif // __BLACKBOX_H__
