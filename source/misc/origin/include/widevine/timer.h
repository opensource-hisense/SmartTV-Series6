// Copyright 2013 Google Inc. All Rights Reserved.
//
// Timer - Platform independent interface for a Timer class
//
#ifndef WVCDM_CORE_TIMER_H_
#define WVCDM_CORE_TIMER_H_

#include "wv_cdm_types.h"

namespace wvcdm {

// Timer Handler class.
//
// Derive from this class if you wish to receive events when the timer
// expires. Provide the handler when setting up a new Timer.

class TimerHandler {
 public:
  TimerHandler() {};
  virtual ~TimerHandler() {};

  virtual void OnTimerEvent() = 0;
};

// Timer class. The implementation is platform dependent.
//
// This class provides a simple recurring timer API. The class receiving
// timer expiry events should derive from TimerHandler.
// Specify the receiver class and the periodicty of timer events when
// the timer is initiated by calling Start.

class Timer {
 public:
  class Impl;

  Timer();
  ~Timer();

  bool Start(TimerHandler *handler, uint32_t time_in_secs);
  void Stop();
  bool IsRunning();

 private:
  Impl *impl_;

  CORE_DISALLOW_COPY_AND_ASSIGN(Timer);
};

};  // namespace wvcdm

#endif  // WVCDM_CORE_TIMER_H_
