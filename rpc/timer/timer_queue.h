// Copyright (C) 2018 ichenq@outlook.com. All rights reserved.
// Distributed under the terms and conditions of the Apache License. 
// See accompanying files LICENSE.

#pragma once

#include <sys/timerfd.h>
#include <vector>
#include <unordered_map>
#include "rpc/timer/timer_queue_base.h"
#include "rpc/channel.h"

/* timerfd */
int CreateTimerfd();
int ResetTimerfd();
void ReadTimerfd();


// timer queue implemented with priority queue(min-heap)
//
// complexity:
//     AddTimer    CancelTimer   PerTick
//      O(log N)    O(log N)       O(1)
//
class TimerQueue : public TimerQueueBase, public Channel
{
    struct Timer;
public:
    TimerQueue(EventDispatcher *evd);
    ~TimerQueue();

    int AddTimer(uint32_t time, TimerCallback cb) override;

    bool CancelTimer(int id) override;

    void Update() override;

    int Size() const { return (int)heap_.size(); }

private:
    void clear();
    bool siftdown(int x, int n);
    void siftup(int j);

private:
    const int64_t twepoch; // custom epoch
    std::vector<Timer*> heap_;
};
