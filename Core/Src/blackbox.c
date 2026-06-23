/*
 * blackbox.c
 * 简易黑匣子实现：环形内存缓存 + 串口导出
 */

#include "blackbox.h"
#include "Com_debug.h"

#define BLACKBOX_BUFFER_SIZE 256

static BlackboxEntry s_buffer[BLACKBOX_BUFFER_SIZE];
static uint16_t s_head = 0;
static uint16_t s_count = 0;

void Blackbox_Init(void)
{
    s_head = 0;
    s_count = 0;
}

void Blackbox_Log(BlackboxEntry *entry)
{
    if (entry == NULL)
        return;
    s_buffer[s_head] = *entry;
    s_head++;
    if (s_head >= BLACKBOX_BUFFER_SIZE)
        s_head = 0;
    if (s_count < BLACKBOX_BUFFER_SIZE)
        s_count++;
}

void Blackbox_DumpAll(void)
{
    // 从最老开始打印
    uint16_t idx = (s_count < BLACKBOX_BUFFER_SIZE) ? 0 : s_head;
    uint16_t printed = 0;
    while (printed < s_count)
    {
        BlackboxEntry *e = &s_buffer[idx];
        debug_printf("T:%lu P:%.2f R:%.2f Y:%.2f THR:%d M1:%d M2:%d M3:%d M4:%d FS:%d RS:%d V:%.2f D:%d\r\n",
                     (unsigned long)e->tick, e->pitch, e->roll, e->yaw,
                     e->thr, e->motor1, e->motor2, e->motor3, e->motor4,
                     e->flight_state, e->remote_state, e->voltage, e->distance);

        idx++;
        if (idx >= BLACKBOX_BUFFER_SIZE)
            idx = 0;
        printed++;
    }
}
