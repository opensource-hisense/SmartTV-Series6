// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_HOST_EVENT_LISTENER_H_
#define WVCDM_CDM_HOST_EVENT_LISTENER_H_

#include "cdm_engine.h"
#include "content_decryption_module.h"
#include "wv_cdm_common.h"
#include "wv_cdm_event_listener.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class HostEventListener : public WvCdmEventListener {
 public:
  HostEventListener(cdm::Host* host, CdmEngine* cdm_engine)
      : host_(host), cdm_engine_(cdm_engine) {}
  virtual ~HostEventListener() {}

  // wvcdm::WvCdmEventListener implementation.
  virtual void OnEvent(const CdmSessionId& session_id,
                       CdmEventType cdm_event) OVERRIDE;

 private:
  cdm::Host* const host_;
  CdmEngine* const cdm_engine_;

  CORE_DISALLOW_COPY_AND_ASSIGN(HostEventListener);
};

}  // namespace wvcdm

#endif  // WVCDM_CDM_HOST_EVENT_LISTENER_H_
