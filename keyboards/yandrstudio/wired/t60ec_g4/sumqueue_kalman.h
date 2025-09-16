// Copyright 2025 HEXTONE (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "util.h"
#include <string.h>

// A simple ringbuffer holding Size elements of type T
typedef struct
{
    uint16_t data[32];
    uint8_t Size;
    uint8_t head;
    uint8_t tail;
    float prevData;
    float p;
    float q;
    float r;
    float kGain;
    bool mutex;
} RingBuffer;

void initqueue(RingBuffer *st, uint8_t size)
{
    memset(st->data, 0, sizeof(st->data));
    st->Size = size;
    st->head = 0;
    st->tail = 0;
    st->prevData = 0;
    st->p = 1;
    st->q = 0.1;
    st->r = 0.05;
    st->kGain = 0;
    st->mutex = false;
}

void clearqueue(RingBuffer *st)
{
    if (st->mutex)
        return;
    st->head = 0;
    st->tail = 0;
    st->prevData = 0;
    st->p = 1;
    st->q = 0.1;
    st->r = 0.05;
    st->kGain = 0;
}

bool emptyqueue(RingBuffer *st) { return st->head == st->tail; }
uint8_t nextPosition(RingBuffer *st, uint8_t position)
{
    return (position + 1) % st->Size;
}
bool fullqueue(RingBuffer *st)
{
    uint8_t next = nextPosition(st, st->head);
    if (next == st->tail)
    {
        return true;
    }
    return false;
}
bool enqueue(RingBuffer *st, uint16_t item)
{
    if (st->mutex)
        return true;
    uint8_t next = nextPosition(st, st->head);
    if (next == st->tail)
    {
        // Full
        return false;
    }

    else
    {
        st->p = st->p + st->q;
        st->kGain = st->p / (st->p + st->r);
        item = st->prevData + (st->kGain * (item - st->prevData));
        st->p = (1.0 - st->kGain) * st->p;
        st->prevData = item;

        st->data[st->head] = item;
        st->head = next;
    }
    return true;
}

bool f_enqueue(RingBuffer *st, uint16_t item)
{
    if (st->mutex)
        return true;
    uint8_t next = (st->head + 1) % st->Size;
    if (next == st->tail)
    {
        // Full dequeue
        st->tail = (st->tail + 1) % st->Size;
    }

    {
        // 添加突变检测
        uint16_t diff = item > st->prevData ? item - st->prevData : st->prevData - item;
        if (diff > 50) {  // 如果变化太大，认为是突变
            st->q = 0.2;  // 临时增大过程噪声
            st->r = 0.02;  // 临时减小测量噪声
        } else {
            st->q = 0.1;  // 正常值
            st->r = 0.05;   // 正常值
        }

        st->p = st->p + st->q;
        st->kGain = st->p / (st->p + st->r);
        item = st->prevData + (st->kGain * (item - st->prevData));
        st->p = (1.0 - st->kGain) * st->p;
        st->prevData = item;

        st->data[st->head] = item;
        st->head = next;
    }
    return true;
}

bool dequeue(RingBuffer *st)
{
    if (st->mutex)
        return true;
    uint8_t tail = st->tail;
    if (tail == st->head)
    {
        // No more data
        return false;
    }
    tail = nextPosition(st, tail);
    st->tail = tail;
    return true;
}
uint8_t sizequeue(RingBuffer *st)
{
    int diff = st->head - st->tail;
    if (diff >= 0)
    {
        return diff;
    }
    return st->Size + diff;
}

uint16_t sumqueue(RingBuffer *st)
{
    st->mutex = true;
    uint8_t size = sizequeue(st);
    if (size == 0)
    {
        st->mutex = false;
        return 0;
    }
    uint32_t sum = 0;
    uint8_t i = 0, j = st->tail;
    uint16_t min_ad = 9999;
    uint16_t max_ad = 0;

    for (i = 0, j = st->tail; i < size; i++)
    {
        sum += st->data[(i + j) % size];
        min_ad = MIN(min_ad, st->data[(i + j) % size]);
        max_ad = MAX(max_ad, st->data[(i + j) % size]);
    }
    if (size >= 3)
    {
        size -= 2;
        sum -= (min_ad + max_ad);
    }
    sum /= size;
    st->mutex = false;
    return sum;
}

uint16_t sortqueue(RingBuffer *st)
{
    uint8_t size = sizequeue(st);
    if (size == 0)
    {
        st->mutex = false;
        return 0;
    }
    uint8_t i = 0, j = st->tail, jj = 0;
    uint8_t k = 0;

    uint32_t sum = 0;
    uint16_t temp = 0;
    uint16_t sort_data[32] = {0};

    for (i = 0, j = st->tail; i < size; i++)
    {
        sort_data[i] = st->data[(i + j) % size];
    }

    for (i = 0; i < size - 1; i++)
    {
        k = i;
        for (jj = i; jj < size; jj++)
        {
            if (sort_data[jj] > sort_data[k])
            {
                k = jj;
            }
        }
        if (k != i)
        {
            temp = sort_data[k];
            sort_data[k] = sort_data[i];
            sort_data[i] = temp;
        }
    }

    uint8_t sum_s = 0;
    uint8_t sum_e = size - 1;
    if (st->Size >= 5 && size == st->Size)
    {
        sum_s = st->Size / 3;
        sum_e = 2 * ((st->Size) / 3);
    }
    for (i = sum_s; i <= sum_e; ++i)
    {
        sum += sort_data[i];
    }
    sum /= (sum_e - sum_s + 1);
    st->mutex = false;
    return sum;
}
