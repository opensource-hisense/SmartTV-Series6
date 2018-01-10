// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_POLICY_ENGINE_H_
#define WVCDM_CORE_POLICY_ENGINE_H_

#include <string>

#include "license_protocol.pb.h"
#include "wv_cdm_types.h"

namespace wvcdm {

using video_widevine_server::sdk::LicenseIdentification;

class Clock;
class PolicyEngineTest;

// This acts as an oracle that basically says "Yes(true) you may still decrypt
// or no(false) you may not decrypt this data anymore."
class PolicyEngine {
 public:
  PolicyEngine();
  virtual ~PolicyEngine();

  // The value returned should be taken as a hint rather than an absolute
  // status. It is computed during the last call to either SetLicense/
  // UpdateLicense/OnTimerEvent/BeginDecryption and may be out of sync
  // depending on the amount of time elapsed. The current decryption
  // status is not calculated to avoid overhead in the decryption path.
  virtual bool can_decrypt() { return can_decrypt_; }

  // OnTimerEvent is called when a timer fires. It notifies the Policy Engine
  // that the timer has fired and that it should check whether any events have
  // occurred since the last timer event. If so, it sets event_occurred to true
  // and sets event to point to the event that occurred. If not, it sets
  // event_occurred to false.
  virtual void OnTimerEvent(bool* event_occurred, CdmEventType* event);

  // SetLicense is used in handling the initial license response. It stores
  // an exact copy of the policy information stored in the license.
  // The license state transitions to kLicenseStateCanPlay if the license
  // permits playback.
  virtual void SetLicense(const video_widevine_server::sdk::License& license);

  // Call this on first decrypt to set the start of playback.
  virtual void BeginDecryption(void);

  // UpdateLicense is used in handling a license response for a renewal request.
  // The response may only contain any policy fields that have changed. In this
  // case an exact copy is not what we want to happen. We also will receive an
  // updated license_start_time from the server. The license will transition to
  // kLicenseStateCanPlay if the license permits playback.
  virtual void UpdateLicense(
      const video_widevine_server::sdk::License& license);

  virtual CdmResponseType Query(CdmQueryMap* key_info);

  virtual const LicenseIdentification& license_id() { return license_id_; }

 private:
  typedef enum {
    kLicenseStateInitial,
    kLicenseStatePending,  // if license is issued for sometime in the future
    kLicenseStateCanPlay,
    kLicenseStateNeedRenewal,
    kLicenseStateWaitingLicenseUpdate,
    kLicenseStateExpired
  } LicenseState;

  void Init(Clock* clock);

  bool IsLicenseDurationExpired(int64_t current_time);
  int64_t GetLicenseDurationRemaining(int64_t current_time);
  bool IsPlaybackDurationExpired(int64_t current_time);
  int64_t GetPlaybackDurationRemaining(int64_t current_time);

  bool IsRenewalDelayExpired(int64_t current_time);
  bool IsRenewalRecoveryDurationExpired(int64_t current_time);
  bool IsRenewalRetryIntervalExpired(int64_t current_time);

  void UpdateRenewalRequest(int64_t current_time);

  LicenseState license_state_;
  bool can_decrypt_;

  // This is the current policy information for this license. This gets updated
  // as license renewals occur.
  video_widevine_server::sdk::License::Policy policy_;

  // This is the license id field from server response. This data gets passed
  // back to the server in each renewal request. When we get a renewal response
  // from the license server we will get an updated id field.
  video_widevine_server::sdk::LicenseIdentification license_id_;

  // The server returns the license start time in the license/license renewal
  // response based off the request time sent by the client in the
  // license request/renewal
  int64_t license_start_time_;
  int64_t playback_start_time_;

  // This is used as a reference point for policy management. This value
  // represents an offset from license_start_time_. This is used to
  // calculate the time where renewal retries should occur.
  int64_t next_renewal_time_;
  int64_t policy_max_duration_seconds_;

  Clock* clock_;

  // For testing
  friend class PolicyEngineTest;
  PolicyEngine(Clock* clock);

  CORE_DISALLOW_COPY_AND_ASSIGN(PolicyEngine);
};

}  // wvcdm

#endif  // WVCDM_CORE_POLICY_ENGINE_H_
