// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_CDM_HOST_CLOCK_H_
#define WVCDM_CDM_CDM_HOST_CLOCK_H_

namespace wvcdm {

class IClock {
 public:
  IClock(){}
  virtual ~IClock();
  virtual int64_t GetCurrentTimeInSeconds() = 0;
};

class HostClock {
  friend class Clock;
  friend class IClock;
 public:
  static void SetClockInterface(IClock* iclock);
  int64_t GetCurrentTimeInSeconds();
 private:
  static IClock* impl_;
};

} // namspace wvcdm

#endif // WVCDM_CDM_CDM_HOST_CLOCK_H_
