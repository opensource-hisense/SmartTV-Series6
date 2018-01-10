// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_CDM_HOST_TIMER_H_
#define WVCDM_CDM_CDM_HOST_TIMER_H_

#include <cstddef>
#include <string>
#include <vector>

#include "content_decryption_module.h"
#include "timer.h"

namespace wvcdm {
  class ITimerFactory {
   public:
    virtual Timer::Impl* NewTimerImpl() = 0;
  };

  class Timer::Impl {
    friend class wvcdm::Timer;
    typedef enum {kIdle, kRunning} TimerState;
   public:
    static void RegisterTimerFactory(ITimerFactory* factory);

    explicit Impl(cdm::Host* const host);
    virtual ~Impl(){}

    void Start(TimerHandler *handler, uint32_t time_in_secs);

    void Stop();

    bool IsRunning(){return state_ == kRunning;}

    void OnTimerEvent();

   private:
    static ITimerFactory* factory_;
    cdm::Host* const host_;
    TimerHandler* handler_;
    int64_t delay_ms_;
    TimerState state_;
  };
} // namespace wvcdm

#endif // WVCDM_CDM_CDM_HOST_TIMER_H_
