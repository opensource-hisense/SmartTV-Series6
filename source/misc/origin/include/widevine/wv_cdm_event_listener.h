// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_WV_CDM_EVENT_LISTENER_H_
#define WVCDM_CORE_WV_CDM_EVENT_LISTENER_H_

#include "wv_cdm_types.h"

namespace wvcdm {

// Listener for events from the Content Decryption Module.
// The caller of the CDM API must provide an implementation for OnEvent
// and signal its intent by using the Attach/DetachEventListener methods
// in the WvContentDecryptionModule class.
class WvCdmEventListener {
 public:
  WvCdmEventListener() {}
  virtual ~WvCdmEventListener() {}

  virtual void OnEvent(const CdmSessionId& session_id,
                       CdmEventType cdm_event) = 0;

 private:
  CORE_DISALLOW_COPY_AND_ASSIGN(WvCdmEventListener);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_WV_CDM_EVENT_LISTENER_H_
